#include "ui_stack_viewer.hpp"

void StackViewer::display(const uint16_t* stack, size_t stackSize) {
	ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    ImGui::Begin("Stack Viewer");

    ImGui::Text("Stack Contents:");

    for (size_t i = 0; i < stackSize; ++i) {
        ImGui::Text("Stack[%02zu]: %04X", i, stack[i]);
    }

    ImGui::End();
}