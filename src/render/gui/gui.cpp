#include "../imgui-docking/imgui.h"
#include "../imgui-docking/Backends/imgui_impl_glfw.h"
#include "../imgui-docking/Backends/imgui_impl_vulkan.h"
#include "../render.h"
#include "gui.h"
#include <vulkan/vulkan.h>

#include <cstdlib>

bool about = false;

bool tools = false;

float s = 0.007f;

float Seed = 0.001;

float multiplier = 7.0f;

glm::vec3 lPos = { 0.0f, 0.0f, 15.0f };
float ambient = 0.05f;
glm::vec3 ambientColor = {1.0f, 1.0f, 1.0f};
glm::vec3 baseColor = {0.5f, 0.5f, 0.5f};

glm::vec3 LPos() {
    return lPos;
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

void gui() {

    ImGui::SetNextWindowSize(ImVec2(350, 255));
    ImGui::Begin("Welcome", nullptr, ImGuiWindowFlags_NoResize);
    
    ImGui::Text("Unicraft dev-1.1.0");

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
        ImGui::SetNextWindowSize(ImVec2(300, 200));
        ImGui::Begin("Tools", &tools);

        if (ImGui::CollapsingHeader("Light")) {
            if (ImGui::TreeNode("Position")) {
                ImGui::SliderFloat("X", &lPos.x, -50.0f, 50.f);
                ImGui::SliderFloat("Y", &lPos.y, -50.0f, 50.f);
                ImGui::SliderFloat("Z", &lPos.z, -50.0f, 50.f);
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