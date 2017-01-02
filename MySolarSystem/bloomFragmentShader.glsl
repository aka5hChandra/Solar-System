#version 430

uniform layout(binding=0) sampler2D blurTexture;
uniform layout(binding=1) sampler2D texture;


uniform int width;
uniform int	height;
uniform int isVertical;
in vec2 vTecCoords;
out vec4 color;

subroutine vec4 RenderPassType(vec4);
subroutine uniform RenderPassType RenderPass;

//sub routine for blur effect
subroutine (RenderPassType)
vec4 gussianBlur(vec4 result)
{
float dx = 1.0 / float(width);
float dy = 1.0 / float(height);
float values[9];
	values[0]=0.05;
	values[1]=0.09;
	values[2]=0.11;
	values[3]=0.15;
	values[4]=0.2;
	values[5]=0.15;
	values[6]=0.11;
	values[7]=0.09;
	values[8]=0.05;
	if(isVertical==1)
	{
		vec2 curSamplePos=vec2(vTecCoords.x,vTecCoords.y-4.0*dy);
		for(int i=0;i<9;i++)
		{
			result+=texture2D(blurTexture,curSamplePos)*values[i];
			curSamplePos.y+=dy;
		}
	}else{
		vec2 curSamplePos=vec2(vTecCoords.x-4.0*dx,vTecCoords.y);
		for(int i=0;i<9;i++)
		{
			result+=texture2D(blurTexture,curSamplePos)*values[i];
			curSamplePos.x+=dx;
		}		
	}	
	return vec4(result.xyz,1);

}


//sub routine for bloom effect
subroutine (RenderPassType)
vec4 bloomEffect(vec4 result)
{
return //vec4(1);
vec4(texture2D(texture,vTecCoords.xy ).xyz + texture2D(blurTexture,vTecCoords.xy ).xyz,1);
}


subroutine (RenderPassType)
vec4 copy(vec4 result)
{
return //vec4(1);
vec4(texture2D(blurTexture,vTecCoords.xy ).xyz,1);
}

void main()
{
vec4 result;

result=RenderPass(result);

color=vec4(result.xyz,1);

}
