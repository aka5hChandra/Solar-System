#version 430
in layout(location=0) vec3 vertex;
in layout(location=1) vec2 texCoord;


uniform mat4 mvp;



out vec2 vTecCoords;

void main()
{
	//pass through tex cords and vertex positions.
	vTecCoords=texCoord;
   gl_Position=mvp* vec4(vertex.xyz,1);

   

}