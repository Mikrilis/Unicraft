#version 450

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
	vec3 lightPos;
    float ambientStrength;
    vec3 aCol;
    vec3 bCol;
    float size;
} ubo;

layout(location = 0) in vec3 vPos;

void main() {
    vec3 dx = dFdx(vPos);
    vec3 dy = dFdy(vPos);
    vec3 normal = normalize(cross(dy, dx));

    vec3 lightDir = normalize(ubo.lightPos - vPos);

    float diff = max(dot(normal, lightDir), 0.0);

    outColor = vec4(ubo.bCol * (diff + ubo.aCol*ubo.ambientStrength), 1.0);
}