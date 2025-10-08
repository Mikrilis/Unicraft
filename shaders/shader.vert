#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
    vec3 lightPos;
    float ambientStrength;
    vec3 aCol;
    vec3 bCol;
    float size;
    float seed;
    float multiplier;
	float tessLevel;
	float tSize;
	vec3 pPos;
	vec3 cDir;
} ubo;

layout(location = 0) in vec2 aPos;

layout(location = 0) out vec2 Coord;

void main() {
    vec2 offset;
    offset.x = round(ubo.pPos.x / ubo.tSize);
    offset.y = round(ubo.pPos.y / ubo.tSize);

	Coord = (aPos + offset) * ubo.tSize;
}