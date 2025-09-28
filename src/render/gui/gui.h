#pragma once

#include <glm/glm.hpp>

#ifndef GUI_H
#define GUI_H
void guiRender(VkCommandBuffer);
glm::vec3 LPos();
float Ambient();
glm::vec3 aCol();
glm::vec3 bCol();
float size();
float seed();
float m();

#endif // !GUI_H