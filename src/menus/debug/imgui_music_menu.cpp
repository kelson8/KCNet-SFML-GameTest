#include "imgui_music_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "util/music_util.h"

void ImGuiMusicMenu::Draw()
{
	MusicUtil& musicUtil = MusicUtil::getInstance();
	if (ImGui::CollapsingHeader("Music Info"))
	{
		ImGui::Text("Run tests for the game music");
		if (ImGui::Button("Game music test"))
		{
			fmt::println("Music volume: {}", musicUtil.GetMusicInfo()->getVolume());
			// fmt cannot display this value.
			//fmt::println("Music status: {}", musicUtil.GetMusicInfo()->getStatus());

			fmt::println("Is the track looping: {}", musicUtil.GetMusicInfo()->isLooping());
		}

		if (ImGui::Button("Start game music"))
		{
			musicUtil.SetMusicInfo(true, false, true);
		}

		if (ImGui::Button("Stop game music"))
		{
			musicUtil.SetMusicInfo(false, true, false);
		}
	}
}

#endif // _IMGUI_TEST
