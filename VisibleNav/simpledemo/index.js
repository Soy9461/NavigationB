var graphEditor;

/**
 * Handler, when page is loaded.
 * 
 * @method onWindowLoaded
 */
function onWindowLoaded() {

    /**
     * Resize browser element on window resize.
     * 
     * @method resize
     */
    function resize() {
        var canvas = document.getElementById("canvas1");
        var graphDIV = document.getElementById("graph");
        if (graphDIV === null) {
            graphDIV = document.getElementById("graphinline");
        }
        var toolsDIV = document.getElementById("tools");

        canvas.width = graphDIV.clientWidth;
        canvas.height = graphDIV.clientHeight;
        graphEditor.resizeContent(canvas.width, canvas.height);
    }

    /**
     * Converts a number to a hex value.
     * 
     * @method byte2Hex
     * @param {Number} n Number to convert.
     * @return {String} Hexadecimal result string.
     */
    function byte2Hex(n) {
        var nybHexString = "0123456789ABCDEF";
        return String(nybHexString.substr((n >> 4) & 0x0F, 1)) + nybHexString.substr(n & 0x0F, 1);
    }

    /**
     * Convert the given RGB Values to a Hex color string.
     * 
     * @method rgb2Color
     * @param {Number} r Red value.
     * @param {Number} g Green value.
     * @param {Number} b Blue value.
     * @return {String} Hex color value.
     */
    function rgb2Color(r,g,b) {
        return '#' + byte2Hex(r) + byte2Hex(g) + byte2Hex(b);
    }

    /**
     * Convert a number to a hex value.
     * 
     * @method hex
     * @param {Number} x Number.
     * @return {String} Hexadecimal value.
     */
    function hex(x) {
        return ("0" + parseInt(x, 10).toString(16)).slice(-2);
    }

    /**
     * Converts a given RGB String to a Hex color string.
     * 
     * @method rgb2hex
     * @param {String} rgb RGB String to convert.
     * @return {String} Resulting Hex color value.
     */
    function rgb2hex(rgb) {
        if (/^#[0-9A-F]{6}$/i.test(rgb)) { 
            return rgb;
        }
    
        rgb = rgb.match(/^rgb\((\d+),\s*(\d+),\s*(\d+)\)$/);
        return "#" + hex(rgb[1]) + hex(rgb[2]) + hex(rgb[3]);
    }
    
    /**
     * Assigns the color given by the background style of the div to the selected GraphItems as a fillcolor.
     * 
     * @method assignFillColor
     */
    function assignFillColor(ev) {
        var formatmap = new JSG.commons.Map();
        formatmap.put(JSG.graph.attr.FormatAttributes.FILLCOLOR, rgb2hex(ev.target.style.backgroundColor));
        graphEditor.getInteractionHandler().applyFormatMap(formatmap);
    }
    
    /**
     * Create a color palette at the bottom of the window and assign a handler to each color entry.
     * 
     * @method createColorPalette
     * @param {String} label Label before palette.
     * @param {Function} clickHandler Handler to call, if a color div is clicked.
     */
    function createColorPalette(label, clickHandler) {
        var frequency1 = 0.1, 
            frequency2 = 0.2, 
            frequency3 = 0.3, 
            center = 128, 
            width = 127, 
            len = 60;
        var i;

        var palette = document.getElementById("palette");

        for (i = 0; i < len; ++i) {
            var red = Math.sin(frequency1 * i) * width + center;
            var grn = Math.sin(frequency2 * i) * width + center;
            var blu = Math.sin(frequency3 * i) * width + center;

            var divColor = document.createElement("div");
            divColor.style.width = "20px";
            divColor.style.height = "20px";
            divColor.style.cssFloat = "left";
            divColor.style.background = rgb2Color(red, grn, blu);
            divColor.addEventListener("click", clickHandler);

            palette.appendChild(divColor);
        }
    }

    // create a graph editor and attach it to the canvas element
    graphEditor = new JSG.ui.GraphEditor("canvas1");
    // create a graph and attach it to the graph editor
    graphEditor.setGraph(new JSG.graph.model.Graph());
    // create color palette for fill operation
    createColorPalette("Fill Color:", assignFillColor);
    // initial resize
    setTimeout(resize, 1);

    window.onload = window.onresize = resize;
}

/**
 * Handler for copy button. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method copySelection
 */
function copySelection() {
    graphEditor.getInteractionHandler().copySelection();
}

/**
 * Handler for cut button. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method cutSelection
 */
function cutSelection() {
    graphEditor.getInteractionHandler().cutSelection();
}

/**
 * Handler for paste button. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method paste
 */
function paste() {
    graphEditor.getInteractionHandler().paste();
}

/**
 * Handler for delete button. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method deleteSelection
 */
function deleteSelection() {
    graphEditor.getInteractionHandler().deleteSelection();
}

/**
 * Handler for undo button. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method undo
 */
function undo() {
    graphEditor.getInteractionHandler().undo();
}

/**
 * Handler for redo button. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method redo
 */
function redo() {
    graphEditor.getInteractionHandler().redo();
}

/**
 * Handler for create line button. Activates an interaction to enable the drawing mode.
 * 
 * @method createLine
 */
function createLine() {
    graphEditor.getInteractionHandler().setActiveInteraction(new JSG.graph.interaction.CreateEdgeInteraction(new JSG.graph.model.Edge()));
}

/**
 * Handler for create rect button. Activates an interaction to enable the drawing mode.
 * 
 * @method createRect
 */
function createRect() {
    graphEditor.getInteractionHandler().setActiveInteraction(new JSG.graph.interaction.CreateNodeInteraction(new JSG.graph.model.shapes.RectangleShape()));
}

/**
 * Handler for create text button. Activates an interaction to enable the drawing mode.
 * 
 * @method createText
 */
function createText() {
    graphEditor.getInteractionHandler().setActiveInteraction(new JSG.graph.interaction.CreateNodeInteraction(new JSG.graph.model.shapes.RectangleShape(), "Label"));
}

/**
 * Handler for create rect button. Activates an interaction to enable the drawing mode.
 * 
 * @method createRect
 */
function createEllipse() {
    graphEditor.getInteractionHandler().setActiveInteraction(new JSG.graph.interaction.CreateNodeInteraction(new JSG.graph.model.shapes.EllipseShape()));
}

/**
 * Handler for create polyline or polygon button. Activates an interaction to enable the drawing mode.
 * 
 * @method createPolyline
 * @param {boolean} closed True to create a polygon, otherwise a polyline.
 */
function createPolyline(closed) {
    var polynode = new JSG.graph.model.Node(new JSG.graph.model.shapes.PolygonShape());
    polynode.setItemAttribute(JSG.graph.attr.ItemAttributes.CLOSED, closed);
    graphEditor.getInteractionHandler().setActiveInteraction(new JSG.graph.interaction.CreatePolyLineInteraction(polynode));
}

/**
 * Handler for create polyline or polygon button. Activates an interaction to enable the drawing mode.
 * 
 * @method createBezier
 * @param {boolean} closed True to create a closed bezier shape, otherwise a bezier curve.
 */
function createBezier(closed) {
    var polynode = new JSG.graph.model.Node(new JSG.graph.model.shapes.BezierShape());
    polynode.setItemAttribute(JSG.graph.attr.ItemAttributes.CLOSED, closed);
    graphEditor.getInteractionHandler().setActiveInteraction(new JSG.graph.interaction.CreateBezierInteraction(polynode));
}

/**
 * Handler for edit button. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method edit
 */
function edit() {
    graphEditor.getInteractionHandler().editSelection();
}

/**
 * Handler for alignemnt buttons. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method align
 * @param {JSG.graph.command.Alignment} flag Alignment type to execute.
 */
function align(flag) {
    graphEditor.getInteractionHandler().alignSelection(flag);
}

/**
 * Handler for order buttons. Simply calls appropriate utility function of the 
 * interaction handler
 * 
 * @method order
 * @param {JSG.graph.command.ChangeItemOrder} flag Order type to execute.
 */
function order(flag) {
    graphEditor.getInteractionHandler().changeDrawingOrderSelection(flag);
}

