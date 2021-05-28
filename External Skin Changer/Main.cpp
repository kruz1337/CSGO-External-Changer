#include "Includes.h"
#include "Functions.h"

using namespace std;

void createAscii()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

    std::cout << R"(
                               ____                             __ _  __    ____                  
                              / __ \___  ____ ___  _____  _____/ /| |/ /   / __ \___ _   __  
                             / /_/ / _ \/ __ `/ / / / _ \/ ___/ __|   /   / / / / _ | | / /  
                            / _, _/  __/ /_/ / /_/ /  __(__  / /_/   |   / /_/ /  __| |/ _    
                           /_/ |_|\___/\__, /\__,_/\___/____/\__/_/|_|  /_____/\___/|___(_)         
)" << '\n';
}

void consoleMsg(string msg)
{
    system("CLS");
    createAscii();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 94);
    cout << msg;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
}

int main()
{
    /* 
       If you open csgo with Sandboxie use "[#] Counter-Strike: Global Offensive [#]" , If you open csgo with MIGI use "CS:GO MIGI".
       In shortly if you open csgo in third party software get CSGO's window name and change 'windowName' Variable..    The cheat will not be injected if you change it to the wrong window name.
    */
    const char windowName[] = "Counter-Strike: Global Offensive";
    HWND hwnd = FindWindowA(NULL, windowName);
    DWORD processID;
    GetWindowThreadProcessId(hwnd, &processID);
    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

    //Get Csgo Window
    consoleMsg("Waiting for CS:GO to open...");
    while (true)
    {
        if (hwnd != 0)
        {
            Sleep(500);
            break;
        }
        else
        {
            hwnd = FindWindowA(NULL, windowName);
        }
    }

    //Get Client Base
    consoleMsg("Getting client.dll module adress..");
    do {
        if (clientBase == 0)
        {
            GetWindowThreadProcessId(hwnd, &processID);
        }
        clientBase = getModuleBaseAddress(processID, "client.dll");
        Sleep(500);
    } while (!clientBase);

    //Get Engine Base
    consoleMsg("Getting engine.dll module adress..");
    do {
        if (engineBase == 0)
        {
            GetWindowThreadProcessId(hwnd, &processID);
        }
        engineBase = getModuleBaseAddress(processID, "engine.dll");
        Sleep(500);
    } while (!engineBase);

    if (hwnd && processID)
    {
        consoleMsg("Succesfully Injected... You can press the home button to update skins.");
    }

    auto EnginePointer = readMem<DWORD>(engineBase + dwClientState);
    auto GameState = readMem<int>(EnginePointer + 0x108);
    DWORD localPlayer = readMem<DWORD>(clientBase + dwLocalPlayer);

    thread otherThreads(otherThreads);
    skinChanger();
}