#pragma once 

#include <imgui.h>
#include <stdint.h>

class VRegistersViewer {
public:
	static void display(const uint8_t* V);
};