#version 450

layout(vertices = 4) out;

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

layout(location = 0) in vec2 Coord[];

layout(location = 0) out vec2 coord[];

void main(){
    coord[gl_InvocationID] = Coord[gl_InvocationID];

    if(gl_InvocationID == 0){
        gl_TessLevelOuter[0] = ubo.tessLevel;
        gl_TessLevelOuter[1] = ubo.tessLevel;
        gl_TessLevelOuter[2] = ubo.tessLevel;
        gl_TessLevelOuter[3] = ubo.tessLevel;
        gl_TessLevelInner[0] = ubo.tessLevel;
        gl_TessLevelInner[1] = ubo.tessLevel;
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}