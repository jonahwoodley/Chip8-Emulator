#include "imgui_helper.hpp"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

void ImGuiHelper::init(RenderWindow& window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForSDLRenderer(window.getWindow(), window.getRenderer());
	ImGui_ImplSDLRenderer2_Init(window.getRenderer());
}

void ImGuiHelper::beginFrame() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ImGuiHelper::endFrame(RenderWindow& window) {
    ImGui::Render();
}

void ImGuiHelper::processEvent(SDL_Event* event) {
    ImGui_ImplSDL2_ProcessEvent(event);
}

void ImGuiHelper::cleanUp() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}