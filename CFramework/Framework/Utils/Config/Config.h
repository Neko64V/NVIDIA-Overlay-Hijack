#pragma once
#include <ini.h>
#include <vector>
#include <Windows.h>
#include <filesystem>

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

class ConfigManager
{
private:
    mINI::INIStructure ini;
public:
    bool CheckDirectory(const char* path);
    std::vector<std::string> GetFileList(const std::string& path);
    void LoadConfig(const std::string& Name);
    void SaveConfig(const std::string& Name);
    void GenerateFile(const std::string& Name);

    void DeleteConfig(std::string filename)
    {
        std::string tmp = ".\\Config\\" + filename;

        std::filesystem::remove(tmp.c_str());
    }
};

extern Globals g;