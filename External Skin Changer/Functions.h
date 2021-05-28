#pragma once
#include "Includes.h"
#include <iostream>

using namespace std;

/* Memory Functions */
DWORD getModuleBaseAddress(DWORD pid, const char* name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(MODULEENTRY32);
    do
    {
        if (!strcmp(mEntry.szModule, name))
        {
            CloseHandle(snapshot);
            return (DWORD)mEntry.modBaseAddr;
        }
    } while (Module32Next(snapshot, &mEntry));
}

template <typename T>
T readMem(DWORD address)
{
    T buffer;
    ReadProcessMemory(pHandle, (LPVOID)address, &buffer, sizeof(buffer), 0);
    return buffer;
}

template <typename T>
void writeMem(DWORD address, T value)
{
    WriteProcessMemory(pHandle, (LPVOID)address, &value, sizeof(value), 0);
}

UINT GetModelIndex(const char* modelName)
{
    int ClientState = readMem<UINT>(engineBase + dwClientState);
    int m_pModelPrecacheTable = readMem<UINT>(ClientState + 0x52A4);
    int nsd = readMem<UINT>(m_pModelPrecacheTable + 0x40);
    int m_pItems = readMem<UINT>(nsd + 0xC);
    int xxxxx = m_pItems + 0xC;

    for (UINT i = 0; i < 1024; i++)
    {
        int nsdi_i = readMem<UINT>(xxxxx + (i * 0x34));
        char str[128] = { 0 };
        if (ReadProcessMemory(pHandle, (LPCVOID)nsdi_i, str, sizeof(str), NULL))
        {
            if (_stricmp(str, modelName) == 0)
            {
                return i;
            }
        }
    }
    return 0;
}

UINT GetModelIndexByID(const short knifeID)
{
    UINT modelIndex = 0;
    switch (knifeID)
    {
    case WEAPON_KNIFE:
        modelIndex = GetModelIndex("models/weapons/v_knife_default_ct.mdl");
        break;
    case WEAPON_KNIFE_T:
        modelIndex = GetModelIndex("models/weapons/v_knife_default_t.mdl");
        break;
    case WEAPON_KNIFE_BAYONET:
        modelIndex = GetModelIndex("models/weapons/v_knife_bayonet.mdl");
        break;
    case WEAPON_KNIFE_BUTTERFLY:
        modelIndex = GetModelIndex("models/weapons/v_knife_butterfly.mdl");
        break;
    case WEAPON_KNIFE_CANIS:
        modelIndex = GetModelIndex("models/weapons/v_knife_canis.mdl");
        break;
    case WEAPON_KNIFE_CORD:
        modelIndex = GetModelIndex("models/weapons/v_knife_cord.mdl");
        break;
    case WEAPON_KNIFE_CSS:
        modelIndex = GetModelIndex("models/weapons/v_knife_css.mdl");
        break;
    case WEAPON_KNIFE_FALCHION:
        modelIndex = GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
        break;
    case WEAPON_KNIFE_FLIP:
        modelIndex = GetModelIndex("models/weapons/v_knife_flip.mdl");
        break;
    case WEAPON_KNIFE_GUT:
        modelIndex = GetModelIndex("models/weapons/v_knife_gut.mdl");
        break;
    case WEAPON_KNIFE_GYPSY_JACKKNIFE:
        modelIndex = GetModelIndex("models/weapons/v_knife_gypsy_jackknife.mdl");
        break;
    case WEAPON_KNIFE_KARAMBIT:
        modelIndex = GetModelIndex("models/weapons/v_knife_karam.mdl");
        break;
    case WEAPON_KNIFE_M9_BAYONET:
        modelIndex = GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
        break;
    case WEAPON_KNIFE_OUTDOOR:
        modelIndex = GetModelIndex("models/weapons/v_knife_outdoor.mdl");
        break;
    case WEAPON_KNIFE_PUSH:
        modelIndex = GetModelIndex("models/weapons/v_knife_push.mdl");
        break;
    case WEAPON_KNIFE_SKELETON:
        modelIndex = GetModelIndex("models/weapons/v_knife_skeleton.mdl");
        break;
    case WEAPON_KNIFE_STILETTO:
        modelIndex = GetModelIndex("models/weapons/v_knife_stiletto.mdl");
        break;
    case WEAPON_KNIFE_SURVIVAL_BOWIE:
        modelIndex = GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
        break;
    case WEAPON_KNIFE_TACTICAL:
        modelIndex = GetModelIndex("models/weapons/v_knife_tactical.mdl");
        break;
    case WEAPON_KNIFE_URSUS:
        modelIndex = GetModelIndex("models/weapons/v_knife_ursus.mdl");
        break;
    case WEAPON_KNIFE_WIDOWMAKER:
        modelIndex = GetModelIndex("models/weapons/v_knife_widowmaker.mdl");
        break;
    default:
        break;
    }
    return modelIndex;
}

void ForceUpdate()
{
    DWORD _dwClientState = readMem<DWORD>(engineBase + dwClientState);
    writeMem<int>(_dwClientState + 0x174, -1);
}

void skinChanger()
{
    while (true)
    {
        auto EnginePointer = readMem<DWORD>(engineBase + dwClientState);
        auto GameState = readMem<int>(EnginePointer + 0x108);
        DWORD localPlayer = readMem<DWORD>(clientBase + dwLocalPlayer);

        if (GameState == clientState.ingame)
        {
            /* Skin Changer */
            for (int i = 0; i < 8; i++)
            {
                DWORD weaponEntity = readMem<DWORD>(localPlayer + m_hMyWeapons + i * 0x4) & 0xfff;
                weaponEntity = readMem<DWORD>(clientBase + dwEntityList + (weaponEntity - 1) * 0x10);
                int accountID = readMem<int>(weaponEntity + m_OriginalOwnerXuidLow);
                if (weaponEntity == 0) { continue; }

                short weaponID = readMem<int>(weaponEntity + m_iItemDefinitionIndex);

                DWORD Paintkit = 0;
                DWORD Seed = 0;
                DWORD Statrak = 0;
                DWORD Quality = 0;
                float Wear = 0;
                char CustomName[20] = "";

                if (weaponID == 0) { continue; } //Weapons
                else if (weaponID == WEAPON_AK47)
                {
                    Paintkit = 600;
                    Seed = 420;
                    Statrak = 999;
                    Quality = 3;
                    Wear = 0.0003f;
                    strcpy(CustomName, "This is Ak47");
                }
                else if (weaponID == WEAPON_DEAGLE)
                {
                    Paintkit = 603;
                    Seed = 420;
                    Statrak = 999;
                    Quality = 3;
                    Wear = 0.0003f;
                    strcpy(CustomName, "This is Deagle");
                }
                else if (weaponID == WEAPON_GLOCK)
                {
                    Paintkit = 532;
                    Seed = 420;
                    Statrak = 999;
                    Quality = 3;
                    Wear = 0.0003f;
                    strcpy(CustomName, "This is glock18");
                }
                else if (weaponID != WEAPON_KNIFE && weaponID != WEAPON_KNIFE_T && weaponID != WEAPON_KNIFE_KARAMBIT) { continue; }
                else
                {
                    Paintkit = 59;
                    Seed = 420;
                    Statrak = 999;
                    Quality = 3;
                    Wear = 0.0003f;
                    strcpy(CustomName, "This is knife");

                    writeMem<short>(weaponEntity + m_iItemDefinitionIndex, WEAPON_KNIFE_KARAMBIT); //Knife Name
                    writeMem<int>(weaponEntity + m_nModelIndex, knifeIndex);
                }
                if (readMem<int>(weaponEntity + m_iItemIDHigh) != -1)
                {
                    writeMem<int>(weaponEntity + m_iItemIDHigh, -1);
                }
                writeMem<int>(weaponEntity + m_iAccountID, accountID);
                writeMem<DWORD>(weaponEntity + m_nFallbackPaintKit, Paintkit);
                writeMem<int>(weaponEntity + m_nFallbackSeed, Seed);
                writeMem<float>(weaponEntity + m_flFallbackWear, Wear);
                writeMem<int>(weaponEntity + m_nFallbackStatTrak, Statrak);
                writeMem<int>(weaponEntity + m_iEntityQuality, Quality);

                if (CustomName != "")
                {
                    WriteProcessMemory(pHandle, (LPVOID)(weaponEntity + m_szCustomName), CustomName, sizeof(char[20]), NULL);
                }
            }

            /* Knife Changer */
            /* Getting knife model index in other gamestate. */
            if (isGetted == false)
            {
                knifeIndex = GetModelIndexByID(WEAPON_KNIFE_KARAMBIT); //Knife Model
                isGetted = true;
            }

            UINT iCurWeaponAdress = readMem<UINT>(localPlayer + m_hActiveWeapon) & 0xFFF;
            UINT m_iBase = readMem<UINT>(clientBase + dwEntityList + (iCurWeaponAdress - 1) * 0x10);
            short curwpnID = readMem<short>(m_iBase + m_iItemDefinitionIndex);

            if (curwpnID == WEAPON_KNIFE || curwpnID == WEAPON_KNIFE_T || curwpnID == WEAPON_KNIFE_KARAMBIT)
            {
                DWORD knifeViewModel = readMem<DWORD>(localPlayer + m_hViewModel) & 0xfff;
                knifeViewModel = readMem<DWORD>(clientBase + dwEntityList + (knifeViewModel - 1) * 0x10);

                if (knifeViewModel == 0) { continue; }

                writeMem<DWORD>(knifeViewModel + m_nModelIndex, knifeIndex);
            }
        }
        else
        {
            isGetted = !isGetted;
        }
    }

}

void otherThreads() 
{
    while (true)
    {
        /* Press HOME Key to Calling update Engine function */
        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            ForceUpdate();
        }
    }
}
