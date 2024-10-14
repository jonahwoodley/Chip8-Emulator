#pragma once

#include "chip8.hpp"

class MainMenu {
public:
	static void display(Chip8& chip8, bool& showMemoryViewer, bool& showStackViewer, bool& showVRegistersViewer, int& cpuCycles);
};