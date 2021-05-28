# CSGO-External-Changer
This repository has a external skin and knife changer for Counter-Strike: Global Offensive game. It's fully open source

![](https://img.shields.io/badge/language-c++-e76089?style=plastic) ![](https://img.shields.io/badge/game-csgo-yellow?style=plastic) ![](https://img.shields.io/badge/license-GNU-green?style=plastic) ![](https://img.shields.io/badge/arch-x86-d9654f?style=plastic)

![Image of RequestX International Developer Group on Discord](https://github.com/Kruziikrel1/CSGO-External-Changer/blob/main/thumbnail.png)

## How to build CSGO External Changer Project files?
* First of all you should download project files on project page or clone this repository from GitBash or GitHub Desktop on your PC. [CSGO-External-Changer.rar](https://github.com/Kruziikrel1/CSGO-External-Changer/releases/)

* If you download project files with manual method you need extract zip file.

* Run .sln file on Visual Studio (2019+).

* Change build configuration to Debug | x86 and press Build button or press <kbd>CTRL+B</kbd> on your keyboard.

* Check out debug folder include that and start exe file for start cheat.

* Go to the bottom heading to add other weapons.

* That's all, enjoy it :)

## How to add other weapon skins?
* First go to "Functions.h" in Header Files.

* Then go to skinChanger below the "Weapons" comment line.

* Add this code and read comment lines in this code.
```c++
else if (weaponID == WEAPON_?)  //Change "WEAPON_?" to the weapon name with which you will change the skin. Sample; "WEAPON_P90"
{
    Paintkit = ?;               //Change "?" to your skin id
    Seed = 420;
    Statrak = ?;                //Change "?" to your Stattrak number
    Quality = 3;
    Wear = 0.0003f;
    strcpy(CustomName, "?");    //Change "?" to your Name Tag
}
```

## How to change knife and knife skin?
* First go to "Functions.h" in Header Files.

* Then go to skinChanger below the "Knife Name" comment line.

* Change this code instead.
```c++
 writeMem<short>(weaponEntity + m_iItemDefinitionIndex, WEAPON_KNIFE_KARAMBIT);
 to
 writeMem<short>(weaponEntity + m_iItemDefinitionIndex, WEAPON_KNIFE_?);    //Change "WEAPON_KNIFE_?" to the knife name with which you will change the skin. Sample; "WEAPON_KNIFE_CANIS"
```

* And go to skinChanger below the "Knife Changer" comment line.

* Change this code instead.
```c++
 knifeIndex = GetModelIndexByID(WEAPON_KNIFE_KARAMBIT);
 to
 knifeIndex = GetModelIndexByID(WEAPON_KNIFE_?);    //Change "WEAPON_KNIFE_?" to Replace with the one you just now replaced
```
