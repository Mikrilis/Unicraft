#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef RAND_H
#define RAND_H

class Generator {
public:
	float seed;

	float rand(glm::vec2);
	float rand(glm::vec2, float);
	float rand(glm::vec2, float, float);
	float perlin(glm::vec2, float, float);
	float perlin(glm::vec2, float);
	float fbm(glm::vec2);
	float th(glm::vec2);
private:
	const float M_PI = 3.14159265358979323846;
};

#endif // !RAND_H
