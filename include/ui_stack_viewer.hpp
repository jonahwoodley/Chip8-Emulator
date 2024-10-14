#pragma once 

#include <imgui.h>
#include <cstdint>

class StackViewer {
public:
	static void display(const uint16_t* stack, size_t stackSize);
};