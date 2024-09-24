// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#ifdef WITH_IMGUI
	#include <ImGuiUnrealDraws.h>
#else
	#define DEFINE_IMGUI_SCREEN(Name)
	#define IMPLEMENT_IMGUI_SCREEN(Code)
#endif
