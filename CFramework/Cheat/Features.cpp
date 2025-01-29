#include "FrameCore.h"
#pragma comment(lib, "WinMM.lib")

const int ReadCount = 64;

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

            if (entity_entry == pLocal->address)
                continue;

            // get CSPlayerPawn and some data
            if (!p.UpdateStatic(list_addr))
                continue;
            else if (!p.Update())
                continue;

            ent_list.push_back(p);
        }

        EntityList = ent_list;
        ent_list.clear();
    }
}