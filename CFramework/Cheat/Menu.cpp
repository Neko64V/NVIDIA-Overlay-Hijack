#include "FrameCore.h"

// ImGui::Combo/ImGui::List等で使う文字列群
const char* BoxTypeList[] = { "Simple", "Cornered" };
const char* CrosshairList[] = { "Cross", "Circle" };
std::vector<const char*> MenuStringList = { "AimBot", "Visual", "Misc", "Setting" };
std::vector<const char*> MenuIconList = { ICON_FA_CROSSHAIRS, ICON_FA_EYE, ICON_FA_BARS, ICON_FA_GEAR };

// チートのメニュー
void CFramework::RenderMenu()
{
    // Setup
    static int Index = 0;
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    
    //ImGui::SetNextWindowBgAlpha(0.975f);
    ImGui::SetNextWindowSize(ImVec2(725.f, 450.f));
    ImGui::Begin("Counter-Strike 2 [ EXTERNAL ]", &g.g_ShowMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    //---// Clild 0 //-----------------------------------//
    ImGui::BeginChild("##SelectChild", ImVec2(150.f, ImGui::GetContentRegionAvail().y), false);

    static float size = ImGui::GetContentRegionAvail().x;

    ImGui::BeginChild("##IMG", ImVec2(size, size), true);



    ImGui::EndChild();

    ImGui::Spacing();

    ImGui::PushFont(icon);

    for (int i = 0; i < MenuIconList.size(); i++)
    {
        if (ImGui::CustomButton(MenuIconList[i], MenuStringList[i], ImVec2(ImGui::GetContentRegionAvail().x, 35.f), Index == i ? true : false))
            Index = i;
    }

    ImGui::PopFont();

    ImGui::EndChild();
    //---// Clild 0 End //-------------------------------//

    ImGui::SameLine();

    //---// Clild 1 //-----------------------------------//
    ImGui::BeginChild("##MainChild", ImVec2(ImGui::GetContentRegionAvail()), false);

    //---// Left //--------------------------------------//
    ImGui::BeginChild("##LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - (style.WindowPadding.x * 2), ImGui::GetContentRegionAvail().y), false);

    switch (Index)
    {
    case 0: // visual
        ImGui::BeginChild("##C010", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 3.f), true);
        ImGui::Text("Visual");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("ESP", &g.g_ESP);
        ImGui::Checkbox("Team ESP", &g.g_ESP_Team);

        ImGui::EndChild();
        ImGui::BeginChild("##C011", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text("ESP Options");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Box", &g.g_ESP_Box);
        ImGui::Checkbox("BoxFilled", &g.g_ESP_BoxFilled);
        ImGui::Checkbox("Line", &g.g_ESP_Line);
        ImGui::Checkbox("Skeleton", &g.g_ESP_Skeleton);
        ImGui::Checkbox("HealthBar", &g.g_ESP_HealthBar);
        ImGui::Checkbox("Name", &g.g_ESP_Name);
        ImGui::Checkbox("Distance", &g.g_ESP_Distance);
       
        ImGui::EndChild();
        break;
    case 1: { // misc
        ImGui::BeginChild("##C020", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 3.f), true);

        ImGui::EndChild();
    } break;
    case 2: // system
        ImGui::BeginChild("##C030", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 1.75f), true);

        ImGui::Text("System");
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Checkbox("Crosshair", &g.g_Crosshair);

        ImGui::CustomSliderInt("MaxFramerate", "##MaxFrame", &g.g_MaxFramerate, 30, 500);

        ImGui::EndChild();
        ImGui::BeginChild("##C031", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text("Crosshair");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Crosshair", &g.g_Crosshair);
        ImGui::CustomSliderInt("CrosshairSize", "##SizeCH", &g.g_CrosshairSize, 1, 10);
        ImGui::ColorEdit4("Color##C", &CrosshairColor.Value.x);
        ImGui::Combo("Type##C", &g.g_CrosshairType, CrosshairList, IM_ARRAYSIZE(CrosshairList));

        ImGui::EndChild();
        break;
    default:
        break;
    }

    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::SameLine();

    //---// Right //--------------------------------------//
    ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail()), false);

    switch (Index)
    {
    case 0: // visual
        ImGui::BeginChild("##C110", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 2.75f), true);

        ImGui::Text("ESP Setting");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::CustomSliderFloat("Distance", "##Distance", &g.g_ESP_MaxDistance, 10.f, 100.f);

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Combo("BoxType", &g.g_ESP_BoxType, BoxTypeList, IM_ARRAYSIZE(BoxTypeList));

        ImGui::EndChild();
        ImGui::BeginChild("##C111", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text("ESP Colors");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::ColorEdit3("Default", &ESP_Default.Value.x);
        ImGui::ColorEdit3("Visible", &ESP_Visible.Value.x);
        ImGui::ColorEdit3("Team", &ESP_Team.Value.x);
        ImGui::ColorEdit3("Shadow", &ESP_Shadow.Value.x, ImGuiColorEditFlags_DisplayRGB);

        ImGui::NewLine();

        ImGui::SeparatorText("Alpha");
        ImGui::CustomSliderFloat("Global", "##GlobalA", &m_flGlobalAlpha, 0.3f, 1.0f, "%.2f");
        ImGui::CustomSliderFloat("Shadow", "##ShadowA", &m_flShadowAlpha, 0.1f, 0.3f, "%.2f");

        ImGui::EndChild();
        break;
    case 1: // misc
        ImGui::BeginChild("##120", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::EndChild();
        break;
    case 2: // system
        ImGui::BeginChild("##130", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text("Exit");
        ImGui::Separator();
        ImGui::Spacing();
        if (ImGui::Button("Exit", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
            g.g_Run = false;

        ImGui::EndChild();
        break;
    default:
        break;
    }

    ImGui::EndChild();
    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::End();
}