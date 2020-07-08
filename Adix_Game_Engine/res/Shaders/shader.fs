#version 330 core

out vec4 FragColor;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform vec3 color;
uniform int isTex;

in vec2 TexCoords;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 -1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
	if(isTex == 0) {
		FragColor = vec4(color, 1.0);
	}
	else if(isTex == 1) {
		//float depth = LinearizeDepth(gl_FragCoord.z) / far;
		FragColor = vec4(vec3(texture(tex2, TexCoords)), 1.0);//vec4(vec3(depth), 1.0);
	}
	else {
		FragColor = vec4(vec3(texture(tex, TexCoords)), 1.0);
	}
}