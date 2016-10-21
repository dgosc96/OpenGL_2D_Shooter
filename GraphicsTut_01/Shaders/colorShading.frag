#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

//uniform float time;
uniform sampler2D mySampler;



void main(){


	vec4 textureColor = texture(mySampler,  fragmentUV);
	
	color = fragmentColor * textureColor;

     /*color = vec4(fragmentColor.r * (cos(fragmentUV.x * 5.0 + time *5) + 3.0) * 0.2,
						 fragmentColor.g * (cos(fragmentUV.y * 5.0 + time *5) + 3.0) * 0.2,
						 fragmentColor.b * (sin(fragmentUV.y * 5.0 + time *5) + 3.0) * 0.2, 
						 fragmentColor.a) * textureColor;*/
						 
						 


}