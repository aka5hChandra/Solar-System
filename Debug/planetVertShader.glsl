#version 430
in layout(location=0) vec3 vertex;
layout (location = 1) in vec2 texCoord;

out vec3 vVertex;
out vec2 vTexCoord;



void main()
{
      vVertex = vertex.xyz;


}