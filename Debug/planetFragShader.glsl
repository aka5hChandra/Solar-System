#version 430

in GEO_OUT
{
vec3 position;
vec3 faceNormal;
vec3 normal;
vec2 texCords;
vec3 lightVector;
vec3 viewVector;
vec2 geoGenratedTexCords;
vec3 tangent;
} frag_in;

in vec2 vTexCoord;



uniform vec3 lightPosition;
uniform vec3 diffuseMaterial; 
uniform vec3 ambientMaterial; 
uniform vec3 specularMaterial;
uniform vec3 diffuseComponent; 
uniform vec3 ambientComponent; 
uniform vec3 specularComponent;
uniform float shininess;
uniform bool lightCheck;
uniform bool nightLights;
uniform mat4 viewMatrix;

uniform vec3 rimColor;
uniform float rimPower;

uniform layout (binding=0) sampler2D texture;			   
uniform layout (binding=1) sampler2D nightLightTex;
 
out vec4 color;


void main() {
 
 
vec3 n = normalize( frag_in. normal );                                                                         
vec3 l =	normalize( vec3(lightPosition)- frag_in.position );				 
vec3 v = normalize(vec3(- frag_in.position));								 
 vec3 r = reflect(  n,-l );

vec3 diffuse = (max( dot(l, n), 0.0 ))*diffuseMaterial*diffuseComponent ;
vec3 specular = ( pow( max( dot(r,v), 0.0 ), shininess ))*specularMaterial*specularComponent;

//rim lighting
float f = 1.0 - dot(n, v);
// Constrain it to the range 0 to 1 using a smooth step function
f = smoothstep(0.0, 1.0, f);
// Raise it to the rim exponent
f = pow(f, rimPower);
// Finally, multiply it by the rim color
vec3 rim= f * rimColor;




vec4 light= vec4(rim+ambientMaterial*ambientComponent+diffuse +specular,1) ;



 


  ///
  if(lightCheck)
  {
if(nightLights)
color=mix(texture2D(nightLightTex,frag_in.geoGenratedTexCords.xy ),vec4(light)*texture2D(texture,frag_in.geoGenratedTexCords.xy ),light.y );
else
color= vec4(light)*texture2D(
//bumpTex,
texture,
frag_in.geoGenratedTexCords.xy );
}
else
color=texture2D(
//bumpTex,
texture,
frag_in.geoGenratedTexCords.xy );

}