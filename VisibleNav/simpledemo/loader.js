'use strict';
var BASEDIR = "..";
var JSG_HOME = BASEDIR + "/lib";
var JSG_LIB = "jsg.js";


function onAppLoaded() {
	JSG.init(JSG_HOME);
	onWindowLoaded();
}

function loadDemo() {
	Loader.addScript(JSG_LIB, JSG_HOME);
    Loader.addScript("index.js", undefined, onAppLoaded);
    Loader.load();
}
