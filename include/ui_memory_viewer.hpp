#pragma once 

#include "imgui.h"
#include <cstdint>
#include <iostream>

class MemoryViewer {
public:
	static void display(const uint8_t* memory, size_t romSize);
};