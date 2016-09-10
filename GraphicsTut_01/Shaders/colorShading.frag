#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main(){
	color = vec4(
				fragmentColor.r * (cos(fragmentPosition.x * 2.0 + time) + 1.0) * 0.3,
                fragmentColor.g * (cos(fragmentPosition.y * 2.0 + time) + 1.0) * 0.3,
                fragmentColor.b * (sin(fragmentPosition.y * 2.0 - time) + 1.0) * 0.3, 
				fragmentColor.a);


}