#version 430
layout(triangles, equal_spacing, cw) in;
in vec3 tcVertex[];

out vec3 tangent;

uniform mat4 mvp;
uniform mat4 Modelview;






void main()
{
   vec3 p0 = (gl_TessCoord.x * tcVertex[0]);
    vec3 p1 = (gl_TessCoord.y * tcVertex[1]);
    vec3 p2 = (gl_TessCoord.z * tcVertex[2]);

  vec3 tePosition = normalize
				(p0 + p1 + p2);
	
	//tagent

float  r = sqrt((tePosition.x*tePosition.x) +(tePosition. y*tePosition.y) + (tePosition.z*tePosition.z));
float theta = acos(tePosition.z/r);
float phi = atan(tePosition.y,tePosition.x);
 
//then add pi/2 to theta or phi
 
tangent.x = sin(theta)*cos(phi);
tangent.y = sin(theta)*sin(phi);
tangent.z = cos(theta);
////////////////
	
 gl_Position =  vec4(tePosition, 1);


 
	
}