#include "FrameCore.h"
#pragma comment(lib, "WinMM.lib")

const int ReadCount = 1024;

void CFramework::UpdateList()
{
    while (g.g_Run)
    {
        std::vector<CEntity> ent_list;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        // Read EntityList
        auto list_addr = m.Read<uintptr_t>(m.m_gClientBaseAddr + offset::dwEntityList);

        if (list_addr == NULL)
            continue;

        // Local
        pLocal->address = m.Read<uintptr_t>(m.m_gClientBaseAddr + offset::dwLocalPlayerController);

        if (!pLocal->UpdateStatic(list_addr))
            continue;
        else if (!pLocal->Update())
            continue;

        for (int i = 0; i < ReadCount; i++)
        {
            uintptr_t entity_entry = m.Read<uintptr_t>(list_addr + (0x8 * (i & 0x7FFF) >> 9) + 0x10);

            if (entity_entry == NULL)
                continue;

            CEntity p = CEntity();
            p.address = m.Read<uintptr_t>(entity_entry + 120 * (i & 0x1FF));

            uintptr_t classNamePtr = m.Read<uintptr_t>(m.Read<uintptr_t>(p.address + 0x10) + 0x20);
            std::string class_name = m.ReadString_s(classNamePtr);

            if (class_name.size() > 0) {

                if (entity_entry == pLocal->address)
                    continue;

                // Player
                if (!class_name.compare("cs_player_controller")) 
                {
                    if (!p.UpdateStatic(list_addr))
                        continue;
                    else if (!p.Update())
                        continue;

                    p.m_nameClass = class_name;
                    ent_list.push_back(p);
                }
            }
        }

        EntityList = ent_list;
        ent_list.clear();
    }
}

void CFramework::MiscAll()
{
    // TriggerBot
    if (pLocal->m_iIDEntIndex < 15000) {
        auto list_addr = m.Read<uintptr_t>(m.m_gClientBaseAddr + offset::dwEntityList);
        CEntity ent;
        ent.address = m.Read<uintptr_t>(list_addr + 8 * (pLocal->m_iIDEntIndex >> 9) + 0x10);

        if (ent.TriggerAllow(list_addr, pLocal))
        {
            // Click
            if (g.g_ESP_Team && pLocal->m_iTeamNum == ent.m_iTeamNum || pLocal->m_iTeamNum != ent.m_iTeamNum) {
                /*
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);*/
            }
        }
    }
}