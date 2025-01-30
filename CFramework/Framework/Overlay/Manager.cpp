#include "Overlay.h"

bool Overlay::InitOverlay(const char* targetName, int InitMode)
{
    if (InitMode == WINDOW_TITLE || InitMode == WINDOW_CLASS)
    {
        g.g_GameHwnd = InitMode == WINDOW_TITLE ? FindWindowA(NULL, targetName) : FindWindowA(targetName, NULL);

        if (!g.g_GameHwnd) {
            MessageBoxA(nullptr, "target window not found", "Initialize Failed", MB_TOPMOST | MB_ICONERROR | MB_OK);
            return false;
        }
    }
    else if (InitMode == PROCESS)
    {
        g.g_GameHwnd = GetTargetWindow(targetName);

        if (!g.g_GameHwnd) {
           MessageBoxA(nullptr, "target process not found", "Initialize Failed", MB_TOPMOST | MB_ICONERROR | MB_OK);
            return false;
        }
    }
    else
    {
        MessageBoxA(nullptr, "Invalid init option", "Initialize Failed", MB_TOPMOST | MB_ICONERROR | MB_OK);
        return false;
    }

    GetWindowTextA(g.g_GameHwnd, m_TargetTitle, sizeof(m_TargetTitle));

    return CreateOverlay();
}

void Overlay::OverlayManager()
{
    // Window Check
    HWND targetHwnd = FindWindowA(nullptr, m_TargetTitle);
    if (!targetHwnd) {
        g.g_Run = false;
        return;
    }

    // ShowMenu Toggle
    if (GetKeyState(g.g_MenuKey) && !g.g_ShowMenu) {
        g.g_ShowMenu = true;
    }
    else if (!GetKeyState(g.g_MenuKey) && g.g_ShowMenu) {
        g.g_ShowMenu = false;
    }

    // サイズを取得
    RECT TmpRect{};
    POINT TmpPoint{};
    GetClientRect(targetHwnd, &TmpRect);
    ClientToScreen(targetHwnd, &TmpPoint);

    // ImGuiにマウス入力を渡す
    POINT MousePos{};
    GetCursorPos(&MousePos);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.MousePos = ImVec2(MousePos.x, MousePos.y);
    io.MouseDown[0] = IsKeyDown(VK_LBUTTON);
    
    g.g_GameRect = TmpRect;
    g.g_GamePoint = TmpPoint;
}

HWND Overlay::GetTargetWindow(const std::string processName)
{
    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(PROCESSENTRY32);
    const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    while (Process32Next(snapShot, &entry))
    {
        if (!processName.compare(entry.szExeFile))
            break;
    }

    CloseHandle(snapShot);

    HWND hwnd = GetTopWindow(NULL);
    do {
        if (GetWindowLong(hwnd, 8) != 0 || !IsWindowVisible(hwnd))
            continue;
        DWORD ProcessID;
        GetWindowThreadProcessId(hwnd, &ProcessID);
        if (entry.th32ProcessID == ProcessID)
            return hwnd;
    } while ((hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) != NULL);

    return NULL;
}
