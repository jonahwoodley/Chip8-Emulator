#include "ui_v_registers_viewer.hpp"

void VRegistersViewer::display(const uint8_t* V) {
    ImGui::Begin("V Registers");

    for (int i = 0; i < 16; i++) {
        ImGui::Text("V[%X]: %02X", i, V[i]);  // display V0-VF registers in hexadecimal
    }

    ImGui::End();
}