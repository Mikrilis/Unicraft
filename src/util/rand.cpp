#include "rand.h"

float Generator::rand(glm::vec2 co) {
	return glm::fract(glm::sin(glm::dot(co * glm::vec2(seed, seed * 256.155f) + glm::vec2(0.1f), glm::vec2(12.9898, 78.233))) * 43758.5453);
}

float Generator::rand(glm::vec2 co, float l) {
	return rand(glm::vec2(rand(co), l));
}

float Generator::rand(glm::vec2 co, float l, float t) {
	return rand(glm::vec2(rand(co, l), t));
}

float Generator::perlin(glm::vec2 p, float dim, float time) {
	glm::vec2 pos = glm::floor(p * dim);
	glm::vec2 posx = pos + glm::vec2(1.0f, 0.0f);
	glm::vec2 posy = pos + glm::vec2(0.0f, 1.0f);
	glm::vec2 posxy = pos + glm::vec2(1.0f);

	float c = rand(pos, dim, time);
	float cx = rand(posx, dim, time);
	float cy = rand(posy, dim, time);
	float cxy = rand(posxy, dim, time);

	glm::vec2 d = glm::fract(p * dim);
	d = -0.5f * glm::cos(d * M_PI) + 0.5f;

	float ccx = glm::mix(c, cx, d.x);
	float cycxy = glm::mix(cy, cxy, d.x);
	float center = glm::mix(ccx, cycxy, d.y);

	return center * 2.0f - 1.0f;
}

float Generator::perlin(glm::vec2 p, float dim) {
	return perlin(p, dim, 0.0f);
}

float Generator::fbm(glm::vec2 p) {
	float f = 0.0f;
	float amp = 1.0f;
	float freq = 1.0f;
	for (int i = 0; i < 7; i++) {
		f += amp * perlin(p, freq);
		freq *= 2.0f;
		amp *= 0.5f;
	}
	return f;
}

float Generator::th(glm::vec2 p) {
	return fbm(p * 5.0f) * 0.2f + fbm(p * 15.0f) * 0.05f;
}