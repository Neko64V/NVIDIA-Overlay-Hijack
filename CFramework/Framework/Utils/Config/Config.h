#pragma once
#include <Windows.h>

struct Globals
{
    // System
    bool g_Run = true;
    bool g_ShowMenu = false;

    // GameData
    HWND g_GameHwnd;
    RECT g_GameRect{};
    POINT g_GamePoint{};

    // Visual
    bool g_ESP      = true;
    bool g_ESP_Team = false;
    bool g_ESP_C4   = true;
    bool g_ESP_Weapon = false;

    bool g_ESP_Box  = true;
    bool g_ESP_BoxFilled = false;
    bool g_ESP_Line      = false;
    bool g_ESP_Skeleton  = true;
    bool g_ESP_HealthBar = true;
    bool g_ESP_Name      = true;
    bool g_ESP_Distance  = true;
    bool g_ESP_CurrentWeapon = true;
    int g_ESP_BoxType    = 1;
    float g_ESP_MaxDistance = 100.f;

    // System
    bool g_Crosshair = false;
    int g_CrosshairSize = 3;
    int g_CrosshairType = 0;
    int g_MaxFramerate = 165;

    // Key
    int g_MenuKey = VK_INSERT;
};

extern Globals g;
