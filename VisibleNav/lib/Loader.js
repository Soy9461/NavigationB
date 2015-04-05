var scripts = [];

var Loader = (function() {
	"use strict";
    var files = [];
    var currStep = 0;
    var allSteps = 1;
    var showSource = true;
    var monitor;


	//percent: 0-1
    var monitorSubstep = function (percent) {
		var percentPerStep = 100/allSteps;
		var totalStepPercent = Math.min(currStep * percentPerStep, 100);
		var totalSubstepPercent = Math.min(percent * percentPerStep, percentPerStep);
		percent = Math.min(totalStepPercent + totalSubstepPercent, 100);
		
        if (monitor && monitor.loaded) {
            monitor.loaded(percent);
        }
    };
	var monitorStep = function(index) {
		monitorSubstep(1);
		currStep = Math.min(allSteps, index);
		if (monitor) {
			if (index >= allSteps && monitor.done) {
				monitor.done();
			} else if (monitor.loadNext) {
				monitor.loadNext();
			}
		}
	};
    var monitorError = function(err) {
        if (monitor && monitor.error) {
            monitor.error(err);
        }
    };


    var newEntry = function(type, file, basedir, callback, cbscope) {
        return {
            type: type,
            file: file,
            basedir: basedir,
            callback: callback,
            scope: cbscope,
            url: function() {
                var basedir = "";
                if(this.basedir) {
                    basedir = this.basedir;
                    var endswithSlash = basedir.substring(basedir.length - 1, basedir.length) === "/";
                    basedir = endswithSlash ? basedir : basedir + "/";
                }
                return basedir + this.file;
            }
        };
    };

    var addScript = function (url, jssrc) {
        if (jssrc) {
            var script = document.createElement("script");
            script.language = "javascript";
            script.type = "text/javascript";
            script.charset = "UTF-8";
            script.defer = false; //true;
            script.text = jssrc;
            document.head.appendChild(script);
            script.src = showSource ? url : undefined;
        }
    };

	var loadScriptStatic = function(entry, callback, scope) {
		var script = document.createElement("script");
		script.src = entry.url();
		script.type = "application/javascript";
		script.charset = 'UTF-8';
		scope = scope || callback;
		if (script.readyState) {// IE
			script.onreadystatechange = function() {
				if (script.readyState === "loaded" || script.readyState === "complete") {
					script.onreadystatechange = null;
					callback.call(scope);
				}
			};
		} else {// Others
			script.onload = function() {
				callback.call(scope);
			};
		}
		document.head.appendChild(script);		
	};
	var loadScriptDynamic = function(entry, callback, scope) {
        var url = entry.url(),
		xhr = new XMLHttpRequest();
        xhr.open("GET", url, true);
		// xhr.responseType = "text";
        //MONITOR:
        xhr.onprogress = function(ev) {
            var percent = 0;
            if(ev.lengthComputable) {
                percent = (ev.loaded/ev.total); //*100;
                monitorSubstep(percent);
            }
        };
        xhr.onload = function(ev) {
            addScript(url, xhr.responseText);
            scope = scope || callback;
            callback.call(scope);
        };
        xhr.onerror = function(ev) {
            monitorError({cause: "failed", url:url, event:ev});
        };
        xhr.onabort = function(ev) {
			monitorError({cause: "aborted", url: url, event:ev});
        };
        xhr.send();		
	};
	var loadCSS = function(entry, callback, scope) {
		var css = document.createElement("link");
		css.href=entry.url();
		css.rel = "stylesheet";
		css.type = "text/css";
		scope = scope || callback;
		if (css.readyState) {// IE
			css.onreadystatechange = function() {
				if (css.readyState === "loaded" || css.readyState === "complete") {
					css.onreadystatechange = null;
					callback.call(scope);
				}
			};
		} else {// Others
			css.onload = function() {
				callback.call(scope);
			};
		}
		document.head.appendChild(css);
	};
	var loadStatic = function(entry, callback, scope) {
		switch(entry.type) {
			case "css": loadCSS(entry, callback, scope); break;
			case "script": loadScriptStatic(entry, callback, scope); break;
		}
	};
    var loadDynamic = function (entry, callback, scope) {
		switch(entry.type) {
			case "css": loadCSS(entry, callback, scope); break;
			case "script": loadScriptDynamic(entry, callback, scope); break;
		}
    };

	var loadAll = function(dynamic, mon) {
		var i,
			index = 0,	
			//need to track subscripts separatly, because we need a percentage value between 0-1, due to onprogress...
			currSubstep = 0,
			subscripts = []; 
        function loadNext() {
            var prevEntry = (index - 1 >= 0) ? files[index - 1] : undefined;
            //any scripts to load, e.g. from includes.js...
            if(scripts.length > 0 && prevEntry) {
                var basedir = prevEntry.basedir;
				for (i = 0; i < scripts.length; i++) {
                    subscripts.push(newEntry("script", scripts[i], basedir));
                }
                scripts.length = 0; //clear scripts...
            }
			//update monitor...
			if (currSubstep < subscripts.length) {
				monitorSubstep(currSubstep / subscripts.length);
			} else {
				monitorStep(index);
				currSubstep = 0;
				//reset substeps:
				subscripts.length = 0;
			}
            
            //call any callback from previous script, if no subscript to be load...
            if(subscripts.length === 0 && prevEntry) {
                if(prevEntry.callback) {
                    prevEntry.callback.call((prevEntry.scope || prevEntry.callback));   
                }
            }            
            
            //load next script...
            var entry = (currSubstep < subscripts.length) ? subscripts[currSubstep++] : (index < files.length) ? files[index++] : undefined;
			if (entry) {
				var loader = dynamic ? loadDynamic : loadStatic;
				//loader(entry.url(), loadNext);
				loader(entry, loadNext);
			}
        }
        
        monitor = mon;
        allSteps = files.length || 1;
        loadNext();
    };


    return {
        /**
         * Adds a javascript file reference to load.
         * 
         * @method addScript
         * @param {String} filename The name of the javascript file.
         * @param {String} basedir The (relative) path to the javascript file.
         * @param {Function} [callback]	The function to call after file was loaded.
         * @param {Object} [cbscope] The context object to use for the callback.
         */
        addScript: function(filename, basedir, callback, cbscope) {
            files.push(newEntry("script", filename, basedir, callback, cbscope));
        },
        /**
         * Adds a stylesheet reference to load.
         * 
         * @method addStylesheet
         * @param {String} filename The name of the stylesheet file.
         * @param {String} basedir The (relative) path to the stylesheet file.
         * @param {Function} [callback]	The function to call after file was loaded.
         * @param {Object} [cbscope] The context object to use for the callback.
         */
        addStylesheet: function(filename, basedir, callback, cbscope) { //TODO :-)
            files.push(newEntry("css", filename, basedir, callback, cbscope));
        },
        /**
         * Loads all registered files.<br/>
         * The dynamic 
         * 
         * @method load
         * @param {Boolean} [dynamic] The name of the stylesheet file.
         * @param {Load.Monitor} [monitor] A monitor object to get notified about loading progress.
         */
        load: function(dynamic, monitor) {
            loadAll(dynamic, monitor);
        }
    };
}());


/**
 * Defines only a template of a Monitor object used by Loader.<br/>
 * It is not required to use this as a load monitor. However, a custom monitor object must provide the methods
 * and public fields as defined here.
 * 
 * @class Monitor
 * @constructor
 */
Loader.Monitor = function() {
	"use strict";
	this.scripts = 0;
	/**
	 * Called to signal the next item is loaded.<br/>
	 * Subclass can overwrite. Default implementation does nothing.
	 * 
	 * @method loadNext
	 */
	this.loadNext = function() {};
	/**
	 * Called to notify that a certain amount of files were loaded.<br/>
	 * Subclass can overwrite. Default implementation does nothing.
	 * 
	 * @method error
	 * @param {Number} percent The amount of files loaded in percent (0-100).
	 */
	this.loaded = function(percent) {};
	/**
	 * Called to signal that an error occurred during loading.<br/>
	 * Subclass can overwrite. Default implementation does nothing.
	 * 
	 * @method error
	 * @param {Object} err An error object with detailed information.
	 */
	this.error = function(err) {};
	/**
	 * Called to signal that all files where loaded.<br/>
	 * Subclass can overwrite. Default implementation does nothing.
	 * 
	 * @method done
	 */
	this.done = function() {};
};
