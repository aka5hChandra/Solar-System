#version 430

layout(vertices = 3) out;
in vec3 vVertex[];
out vec3 tcVertex[];
uniform float TessLevelInner=20;
uniform float TessLevelOuter=20;

#define ID gl_InvocationID



void main()
{
	//set inner and outter tesslation levels
   tcVertex[ID] = vVertex[ID];
    if (ID == 0) {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
    }
}