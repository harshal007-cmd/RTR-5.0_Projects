Steps to use Sphere files in WEBGL :
================================================================

01) Extract the archive and get the 2 files : Mesh-JS.txt and Sphere-JS.txt

02) Rename both files as follows :
		Rename Mesh-JS.txt to Mesh.js
		Rename Sphere-JS.txt to Sphere.js

03) Copy both files in your assignment's directory.

04) In Canvas.html file, add the following 2 lines after the 2 <script> lines of Canvas.js and gl-matrix-min.js :

		<script src="Mesh.js"></script>
		<script src="Sphere.js"></script>

05) Now make the following changes in Canvas.js.
    Declare following variable globally :

		var sphere = null;

06) In initialize(), where we usually declare vertices arrays, add the following code :

		sphere = new Mesh();
		makeSphere(sphere, 2.0, 30, 30);

    No need to add VAO and VBO related code, as it is already done inside the function prepareToDraw() in Mesh.js.

07) In display(), after the usual gl.useProgram() and matrix tranformation changes add following code to display the sphere :

		sphere.draw();

    VAO binding and unbinding is already done inside this draw() function.

08) In uninitialize(), clean up the sphere data :

		if (sphere)
		{
			sphere.deallocate();
			sphere = null;
		}

