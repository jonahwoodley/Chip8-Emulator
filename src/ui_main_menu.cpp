#include "ui_main_menu.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <ImGuiFileDialog.h>
#include <iostream>
#include <fstream>
#include <string>

void MainMenu::display(Chip8& chip8, bool& showMemoryViewer, bool& showStackViewer, bool& showVRegistersViewer, int& cpuCycles) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Load ROM")) {
            	IGFD::FileDialogConfig config;
					config.path = ".";
                ImGuiFileDialog::Instance()->OpenDialog("ChooseROM", "Choose ROM", ".ch8", config);

            }

            if (ImGui::MenuItem("Exit")) {
                exit(0);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Memory Viewer", NULL, &showMemoryViewer);
            ImGui::MenuItem("Stack Viewer", NULL, &showStackViewer);
            ImGui::MenuItem("V Registers Viewer", NULL, &showVRegistersViewer);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings")) {
            ImGui::SliderInt("CPU Cycles per Frame", &cpuCycles, 1, 50);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseROM")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            chip8.init();
            chip8.loadRom(filePath.c_str()); 
        }

        ImGuiFileDialog::Instance()->Close();
    }
}