#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main(){


	vec4 textureColor = texture(mySampler,  fragmentUV);
	
	//color = textureColor ;

     color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 0.1 + time) + 3.0) * 0.2,
						 fragmentColor.g * (cos(fragmentPosition.y * 0.1 + time) + 3.0) * 0.2,
						 fragmentColor.b * (sin(fragmentPosition.y * 0.1 + time) + 3.0) * 0.2, 
						 fragmentColor.a) * textureColor;


}