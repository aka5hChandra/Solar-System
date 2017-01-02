#version 430
#define M_PI 3.1415926535897932384626433832795

uniform mat4 mvp;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec3 lightPosition;

layout(triangles ) in;
layout(triangle_strip, max_vertices = 3	) out;





in vec3 tangent[3];



out GEO_OUT
{
vec2 texCords;
vec3 faceNormal;
vec3 position;
vec3 normal;
vec3 lightVector;
vec3 viewVector;
vec2 geoGenratedTexCords;
vec3 tangent;

} geo_out;




vec4 V[3];

//generate texcture coordinates based vectex position of sphere
void  getTexCords(vec3 Normal,vec3 Normal_2,int flag)
{
	if(flag==1)
	{
	float tx = atan(Normal.x, Normal.z) / (2. * M_PI) + 0.5;
	float ty = asin(Normal.y) / M_PI + 0.5;

	geo_out.geoGenratedTexCords= vec2(tx,ty);
	}
	else
	{
	float tx0 = atan(Normal.x, Normal.z) / (2. * M_PI) + 0.5;
	float ty0 = asin(Normal.y) / M_PI + 0.5;


	float tx = atan(Normal_2.x, Normal_2.z) / (2. * M_PI) + 0.5;
    float ty = asin(Normal.y) / M_PI + .5;
    if(tx < 0.75 && tx0 > 0.75)
    tx += 1.0;
    else if(tx > 0.75 && tx0 < 0.75)
    tx -= 1.0;
	geo_out.geoGenratedTexCords= vec2(tx,ty);
	
	}

}

void ProduceVertex( int v,vec3 faceNormal )
{
	
	//helper function to emit vertex and all of its attirbutes
		vec3 tempNormal=normalize(normalMatrix*vec3(V[v]));
		vec4 tempPosition=modelViewMatrix*vec4(V[v]);															
		geo_out.position=	tempPosition.xyz/tempPosition.w;																
		geo_out.faceNormal=normalize(faceNormal);
		geo_out.normal=tempNormal;
		geo_out.lightVector=normalize(lightPosition.xyz-tempPosition.xyz);
		geo_out.viewVector=normalize(-tempPosition.xyz);

		//get tengents
		vec3 tempTangent1=cross(tempNormal,vec3(0,0,1));
		vec3 tempTangent2=cross(tempNormal,vec3(0,1,0));
		length(tempTangent1)>length(tempTangent2)?(geo_out.tangent=tempTangent1):(geo_out.tangent=tempTangent2);

		//get tex cords for this vertex
		getTexCords(vec3(V[v]),vec3(0),1);
		
		/*			
		if(v==2)
		getTexCords(vec3(V[2]),vec3(V[v]),1);
		else
		getTexCords(vec3(V[v+1]),vec3(V[v]),2);
	*/				
	
    gl_Position = mvp*(V[v]);

	 EmitVertex();
}

void displayNormals(vec4 p,vec3 faceNormal)
{
	
	//helper function to display normals
	gl_Position = mvp *vec4(p.xyz, 1.0);
    EmitVertex();
    
    gl_Position = mvp *vec4(p.xyz+ faceNormal , 1.0);
    EmitVertex();
    
    EndPrimitive();

}




void main()
{

	V[0]  =   gl_in[0].gl_Position;
	V[1]  =   gl_in[1].gl_Position;
	V[2]  =   gl_in[2].gl_Position;



	//get face normal
    vec3 A = vec3(gl_in[2].gl_Position.xyz) - vec3(gl_in[0].gl_Position.xyz);
    vec3 B = vec3(gl_in[1].gl_Position.xyz) - vec3(gl_in[0].gl_Position.xyz);

	vec3 faceNormal=normalize(cross(A, B));
			
	//call helper function for each vetex
	ProduceVertex( 0, faceNormal );
	ProduceVertex( 1, faceNormal );
	ProduceVertex( 2, faceNormal );
	EndPrimitive();

	vec4 forFaceNormal=((V[0]+V[1]+V[2])/3);

	//displayNormals(forFaceNormal,faceNormal);

	displayNormals(V[0],V[0].xyz);
	displayNormals(V[1],V[1].xyz);
	displayNormals(V[2],V[2].xyz);

	
    
}


