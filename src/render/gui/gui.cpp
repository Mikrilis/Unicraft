#include "../imgui-docking/imgui.h"
#include "../imgui-docking/Backends/imgui_impl_glfw.h"
#include "../imgui-docking/Backends/imgui_impl_vulkan.h"
#include "../render.h"
#include "gui.h"
#include <vulkan/vulkan.h>

#include <cstdlib>

bool about = false;

bool tools = false;

float s = 0.001f;

float Seed = 0.001f;

float multiplier = 10.0f;

int tessLevel = 64;

float terrainSize = 10.0f;

float speed = 100.0f;

glm::vec3 lDir = { 1.0f, 1.0f, 0.8f };
float ambient = 0.05f;
glm::vec3 ambientColor = {1.0f, 1.0f, 1.0f};
glm::vec3 baseColor = {0.5f, 0.5f, 0.5f};

glm::vec3 LDir() {
    return lDir;
}

float Ambient() {
    return ambient;
}

glm::vec3 aCol() {
    return ambientColor;
}

glm::vec3 bCol() {
    return baseColor;
}

float size() {
    return s;
}

float seed() {
    return Seed;
}

float m() {
    return multiplier;
}

float tLevel() {
    return tessLevel;
}

float tSize() {
    return terrainSize;
}

float Speed() {
    return speed;
}

void gui() {

    ImGui::SetNextWindowSize(ImVec2(350, 255));
    ImGui::Begin("Welcome", nullptr, ImGuiWindowFlags_NoResize);
    
    ImGui::Text("Unicraft dev-1.2.0");

    if (ImGui::Button("About")) {
        about = true;
    }

    if (ImGui::Button("Tools")) {
        tools = true;
    }

    if (ImGui::Button("Exit"))
    {
        exit(0);
    }

    if (about)
    {
        ImGui::SetNextWindowSize(ImVec2(240, 115));
        ImGui::Begin("About", &about, ImGuiWindowFlags_NoResize);

        ImGui::Text("Developer: Mikrilis\n"
                    "Game: Unicraft\n\n"
                    "Report bugs on project's GitHub\n\n"
                    "Thanks for playing :D");

        ImGui::End();
    }

    if (tools) {
        ImGui::SetNextWindowSize(ImVec2(400, 300));
        ImGui::Begin("Tools", &tools, ImGuiWindowFlags_NoResize);

        if (ImGui::CollapsingHeader("Data")) {
            ImGui::Value("FpS", (int)FPS());
        }
        if (ImGui::CollapsingHeader("Light")) {
            if (ImGui::TreeNode("Direction")) {
                ImGui::SliderFloat("X", &lDir.x, -1.0f, 1.0f);
                ImGui::SliderFloat("Y", &lDir.y, -1.0f, 1.0f);
                ImGui::SliderFloat("Z", &lDir.z, -1.0f, 1.0f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Ambient")) {
                ImGui::SliderFloat("Strength", &ambient, 0.0f, 1.0f);
                ImGui::ColorEdit3("Color", (float*)&ambientColor);
                ImGui::TreePop();
            }
        }
        if (ImGui::CollapsingHeader("Terrain")) {
            if (ImGui::TreeNode("Appearance")) {
                ImGui::ColorEdit3("Color", (float*)&baseColor);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Noise")) {
                ImGui::SliderFloat("Size", &s, 0.001f, 0.1f);
                ImGui::SliderFloat("Seed", &Seed, 0.001, 999999.999);
                ImGui::SliderFloat("Multiplier", &multiplier, 1.0, 10.0);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Geometry")) {
                ImGui::SliderInt("Tess level", (int*)&tessLevel, 1, 64);
                ImGui::SliderFloat("Terrain size", &terrainSize, 1.0f, 64.0f);
                ImGui::TreePop();
            }
        }
        if (ImGui::CollapsingHeader("GamePlay")) {
            if (ImGui::TreeNode("Movement")) {
                ImGui::SliderFloat("Speed", &speed, 1.0f, 100.0f);
                ImGui::TreePop();
            }
        }

        ImGui::End();
    }

    ImGui::Text("\nControls:\n"
        "  WSAD: Movement\n"
        "  Spacebar/LShift: Up/Down\n"
        "  F11: Toggle fullscreen\n"
        "  F3: Toggle GUI\n"
        "  Escape: Free mouse\n\n"
        "GitHub: 'https://github.com/Mikrilis/Unicraft'\n"
        "Web: 'https://mikrilis.github.io/Unicraft/'");

    ImGui::End();
}

void guiRender(VkCommandBuffer cmd) {
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    gui();

    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmd);
}