#include "ui_memory_viewer.hpp"

void MemoryViewer::display(const uint8_t* memory, size_t romSize) {
    ImGui::SetNextWindowSize(ImVec2(400, 150), ImGuiCond_FirstUseEver);

    ImGui::Begin("Memory Viewer - 4KB Total RAM");

    for (int i = 0; i < 4096; i += 8) {
        ImGui::Text("%03X: ", i);
        ImGui::SameLine();

        for (int j = 0; j < 8; j++) {
            uint8_t value = memory[i + j];

            if (i + j < 80) { // Fontset region (0x000 to 0x04F)
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
            } else if (i >= 0x200 && i < (0x200 + romSize)) { // ROM region (0x200 to however big the rom is!!!)
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(128, 0, 128, 255)); 
            } else if (value != 0) { 
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
            }

            ImGui::Text("%02X ", value);
            ImGui::SameLine();

            if (i + j < 80 || (i >= 0x200 && i < (0x200 + romSize)) || value != 0) {
                ImGui::PopStyleColor();
            }
        }
        ImGui::NewLine(); 
    }

    ImGui::End(); 
}