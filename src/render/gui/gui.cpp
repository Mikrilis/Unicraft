#include "../imgui-docking/imgui.h"
#include "../imgui-docking/Backends/imgui_impl_glfw.h"
#include "../imgui-docking/Backends/imgui_impl_vulkan.h"
#include "../render.h"
#include "gui.h"
#include <vulkan/vulkan.h>

#include <cstdlib>

bool about = false;

void gui() {

    ImGui::SetNextWindowSize(ImVec2(350, 230));
    ImGui::Begin("Welcome", nullptr, ImGuiWindowFlags_NoResize);
    
    ImGui::Text("Unicraft dev-1.0.0");

    if (ImGui::Button("About")) {
        about = true;
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