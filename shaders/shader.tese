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

layout(quads, equal_spacing, ccw) in;

layout(location = 0) out vec3 vPos;
layout(location = 1) out float disc;

#define M_PI 3.14159265358979323846

float rand(vec2 co) {
    return fract(sin(dot(co.xy * vec2(ubo.seed, ubo.seed * 256.155) + vec2(0.1), vec2(12.9898, 78.233))) * 43758.5453);
}

float rand(vec2 co, float l) {
    return rand(vec2(rand(co), l));
}

float rand(vec2 co, float l, float t) {
    return rand(vec2(rand(co, l), t));
}

float perlin(vec2 p, float dim, float time) {
	vec2 pos = floor(p * dim);
	vec2 posx = pos + vec2(1.0, 0.0);
	vec2 posy = pos + vec2(0.0, 1.0);
	vec2 posxy = pos + vec2(1.0);
	
	float c = rand(pos, dim, time);
	float cx = rand(posx, dim, time);
	float cy = rand(posy, dim, time);
	float cxy = rand(posxy, dim, time);
	
	vec2 d = fract(p * dim);
	d = -0.5 * cos(d * M_PI) + 0.5;
	
	float ccx = mix(c, cx, d.x);
	float cycxy = mix(cy, cxy, d.x);
	float center = mix(ccx, cycxy, d.y);
	
	return center * 2.0 - 1.0;
}

// p must be normalized!
float perlin(vec2 p, float dim) {
	return perlin(p, dim, 0.0);
}

float fbm(vec2 p) {
    float f = 0.0;
    float amp = 1.0;
    float freq = 1.0;
    for (int i = 0; i < 7; i++) {
        f += amp * perlin(p, freq);
        freq *= 2.0;
        amp *= 0.5;
    }
    return f;
}

float th(vec2 p){
	return fbm(p * 5.0) * 0.2 + fbm(p * 15.0) * 0.05;
}

void main(){
	vec3 PPos;
    PPos.x = round(ubo.pPos.x / ubo.tSize);
    PPos.y = round(ubo.pPos.y / ubo.tSize);
    PPos.z = round(ubo.pPos.z / ubo.tSize);

    vec3 cPos = vec3(PPos.x - 500, PPos.y - 500, 0.0);
    cPos.y += mod(floor(gl_PrimitiveID / 1000.0), 1000.0);
	cPos.x += mod(gl_PrimitiveID, 1000.0);

    float d = floor(distance(PPos, cPos));

    vec3 dir = normalize(cPos - PPos);

    float angle = dot(dir, ubo.cDir);

    if(angle <= cos(radians(45)/2.0)){
        vec2 offset = vec2((PPos.x - 500) * ubo.tSize, (PPos.y - 500) * ubo.tSize);
		offset.y += mod(floor(gl_PrimitiveID / 1000.0), 1000.0) * ubo.tSize;
		offset.x += mod(gl_PrimitiveID, 1000.0) * ubo.tSize;
	

		vec2 gPos = gl_TessCoord.xy * ubo.tSize;
		vec3 pos = vec3(gPos + offset, 0.0);

		float h = th(pos.xy * ubo.size);
		h = (h + 1.0) * 0.5;
		pos.z = pow(2.0, h * ubo.multiplier);

		vPos = pos;
		gl_Position = ubo.proj * ubo.view * vec4(pos, 1.0);
		disc = 0.0;
    }
	else {gl_Position = vec4(0.0);disc = 1.0;}
}