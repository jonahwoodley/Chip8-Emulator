#include "input_manager.hpp"
#include "chip8.hpp"
#include "imgui_helper.hpp"
#include "render_window.hpp"
#include "ui_memory_viewer.hpp"
#include "ui_stack_viewer.hpp"
#include "ui_v_registers_viewer.hpp"
#include <ui_main_menu.hpp>


int main(int argc, char* argv[])
{
    InputManager inputManager;

    Chip8 chip8;
    chip8.init();

    RenderWindow window("Chip-8 Emulator", 1280, 640);
    ImGuiHelper::init(window);

    bool running = true;
    SDL_Event event;

    // Settings
    bool showMemoryViewer = false;
    bool showStackViewer = false;
    bool showVRegistersViewer = false;

    int cpuCycles = 2;


    while (running) {
        while (SDL_PollEvent(&event)) {
            inputManager.handleInput(chip8, event, running);
            ImGuiHelper::processEvent(&event);
        }

        if (chip8.romLoaded) {
            for (int i = 0; i < cpuCycles; i++) {
                chip8.emulateCycle();
            }
        }

        ImGuiHelper::beginFrame();
        MainMenu::display(chip8, showMemoryViewer, showStackViewer, showVRegistersViewer, cpuCycles);

        if (showMemoryViewer) {
            MemoryViewer::display(chip8.memory, chip8.romSize);
        }
        if (showStackViewer) {
            StackViewer::display(chip8.stack, chip8.sp);
        }
        if (showVRegistersViewer) {
            VRegistersViewer::display(chip8.V);
        }

        ImGuiHelper::endFrame(window);

        window.renderGameDisplay(chip8.gamePixels, 640, 320);

        SDL_Delay(16);
    }
 
    ImGuiHelper::cleanUp();
    chip8.cleanUp();

    return 0;
}
