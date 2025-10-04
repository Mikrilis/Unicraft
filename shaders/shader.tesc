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

void main(){
    if(gl_InvocationID == 0){
        float m = 1.0;

        vec3 pos;
        pos.x = round(ubo.pPos.x / ubo.tSize);
        pos.y = round(ubo.pPos.y / ubo.tSize);
        pos.z = round(ubo.pPos.z / ubo.tSize);

        vec3 cPos = vec3(pos.x - 500, pos.y - 500, 0.0);
        cPos.y += mod(floor(gl_PrimitiveID / 1000.0), 1000.0);
	    cPos.x += mod(gl_PrimitiveID, 1000.0);

        float d = floor(distance(pos, cPos));

        vec3 dir = normalize(cPos - pos);

        float angle = dot(dir, ubo.cDir);

        m *= d > 6 ?  2.0 : 1.0;
        m *= d > 12 ? 2.0 : 1.0;
        m *= d > 30 ? 2.0 : 1.0;
        m *= d > 42 ? 2.0 : 1.0;
        m *= d > 54 ? 2.0 : 1.0;
        m *= d > 66 ? 2.0 : 1.0;

        if(angle > cos(radians(45)/2.0)){
            m = 64;
        }

        
        gl_TessLevelOuter[0] = ubo.tessLevel / m;
        gl_TessLevelOuter[1] = ubo.tessLevel / m;
        gl_TessLevelOuter[2] = ubo.tessLevel / m;
        gl_TessLevelOuter[3] = ubo.tessLevel / m;
        gl_TessLevelInner[0] = ubo.tessLevel / m;
        gl_TessLevelInner[1] = ubo.tessLevel / m;
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}