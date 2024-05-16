// JavaScript source code

var VSHADER_SOURCE =
	'void main() {\n' +
	' gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n' +
	' gl_PointSize = 10.0;\n' +
	'}\n';

var FSHADER_SOURCE =
	'void main() {\n' +
	' gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' +
	'}\n';
function main() {
	//retrive canvas element
	var canvas = document.getElementById('HVS');
	if (!canvas) {
		console.log("Getting canvas failed !\n");
		return;
	}
	else {
		console.log("Getting canvas sucessful\n");
	}

	var gl = canvas.getContext("webgl2");
	if (!gl) {
		console.log("Failed to get rendering context for webgl");
		return;

	}

	//init shader
	if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
		console.log('Failed to initialize shader');
		return;
	}

	//set color for clearing canvas
	gl.clearColor(0.0, 0.0, 0.0, 1.0);

	//clear
	gl.clear(gl.COLOR_BUFFER_BIT);

	//draw a point
	gl.drawArrays(gl.POINTS, 0, 1);
	

}
	