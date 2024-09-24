// Copyright, 2023, by NGD Studios AB. All rights reserved.

#include "ImGuiActor.h"

AImGuiActor::AImGuiActor()
: Var_Integer(1988)
, Var_Unsigned(255)
, Var_String("Hello World")
, Var_Real(12.13f)
{
}

void AImGuiActor::BeginPlay()
{
	Super::BeginPlay();

	IMPLEMENT_IMGUI_SCREEN
	(
		ImGui::InputScalar("Var_Double", ImGuiDataType_Double, &Var_Double);
		if(ImGui::Button("Holi"))
		{
			GLog->Log("Hooliii");
		}
		
		static float xs1[1001];
		static float ys1[1001];
		for (int i = 0; i < 1001; ++i) {
			xs1[i] = i * 0.001f;
			ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
		}
		static double xs2[20];
		static double ys2[20];
		for (int i = 0; i < 20; ++i) {
			xs2[i] = i * 1/19.0f;
			ys2[i] = xs2[i] * xs2[i];
		}
		if (ImPlot::BeginPlot("Line Plots"))
		{
			ImPlot::SetupAxes("x","y");
			ImPlot::PlotLine("f(x)", xs1, ys1, 1001);
			ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
			ImPlot::PlotLine("g(x)", xs2, ys2, 20,ImPlotLineFlags_Segments);
			ImPlot::EndPlot();
		}
	)	
}
