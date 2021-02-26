/* file: main.cpp */

#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <fstream>
#include <map>
#include <sstream>

#include "../include/game.hpp"
#include "../include/rndGen.hpp"
#include "../include/gamePlay.hpp"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define FILE_ERROR -1

std::vector<Hero*> myHeroes;
std::vector<Monster*> availableMonsters;
std::map<std::string, Weapon*> allWeapons;
std::map<std::string, Armor*> allArmors;
std::map<std::string, Potion*> allPotions;
std::map<std::string, IceSpell*> allIceSpells;
std::map<std::string, FireSpell*> allFireSpells;
std::map<std::string, LightningSpell*> allLightningSpells;

int main(void){
    std::string name;
    int minLvlRequired, magicLvlRequired, Lvl;
    double H, mgP, str, dex, ag, mon, exp, dmg, arm, msP, price, 
    protectionLvl, gain, attackingWeakness, defensiveWeakness, agilityWeakness;
    bool hands; 

    Market *market = new Market();

    std::cout << std::endl << std::endl;
    
    std::cout << MAGENTA << R"(  
                    __        _______ _     ____ ___  __  __ _____  
                    \ \      / / ____| |   / ___/ _ \|  \/  | ____| 
                     \ \ /\ / /|  _| | |  | |  | | | | |\/| |  _|   
                      \ V  V / | |___| |__| |__| |_| | |  | | |___  
                       \_/\_/  |_____|_____\____\___/|_|  |_|_____| 
                )" << RESET << '\n';
                                                
    std::cout << CYAN <<R"(  
                     __                                           __
                    (**)                                         (**)
                    IIII                                         IIII
                    ####                                         ####
                    HHHH     Madness comes, and madness goes     HHHH
                    HHHH    An insane place, with insane moves   HHHH
                    ####   Battles without, for battles within   ####
                 ___IIII___        Where evil lives,          ___IIII___
              .-`_._"**"_._`-.      and evil rules         .-`_._"**"_._`-.
             |/``  .`\/`.  ``\|    Breaking them up,      |/``  .`\/`.  ``\|
               `   }    {     '  just breaking them in    `     }    {     '
                   ) () (  Quickest way out, quickest way wins  ) () (
                   ( :: )      Never disclose, never betray     ( :: )
                   | :: |   Cease to speak or cease to breath   | :: |
                   | )( |        And when you kill a man,       | )( |
                   | || |          you're a murderer            | || |
                   | || |             Kill many                 | || |
                   | || |        and you're a conqueror         | || |
                   | || |        Kill them all ... Ooh..        | || |
                   | || |           Oh you're a God!            | || |
                   ( () )                       -Megadeth       ( () )
                    \  /                                         \  /
                     \/                                           \/                     
            )" << RESET << "\n\n";    

    std::cout << YELLOW << "\t\t  Basic Information  " << RESET << "\n";
    std::cout << CYAN   << "\t\t=====================" << RESET << "\n";
    std::cout << "\n\t\tMovement Controls: " << YELLOW << "     W " << RESET << " - move forward\n";
    std::cout << YELLOW << "\t\t\t\t\tS " << RESET << " - move backward\n";
    std::cout << YELLOW << "\t\t\t\t\tA " << RESET << " - move left\n";
    std::cout << YELLOW << "\t\t\t\t\tD " << RESET << " - move right\n";
    
    std::cout << "\n\n\t\tYou cannot move diagonally!\n\n";
    std::cout << "\t\tWhen the game starts, you are allowed to choose up to three heroes for your adventure!\n";
    std::cout << "\t\t" << RED << "Beware! " << RESET <<  "While you are moving into the world, you might face some monsters.\n";
    std::cout << "\t\tIf that time comes, you have to fight for the lives of your Heroes in order to survive!\n";
    std::cout << "\t\tA mini menu will always appear during the game to help you. Good luck!\n\n\n";
    
    do{
        std::cout << "\t\tPress any key to continue . . .\n\t\t";
    } while(!std::cin.get());
    
    std::cout <<"\n\n";

    /* ==========================================| O P E N  F I L E S |======================================== */

    std::ifstream Warriors("input/Warriors.txt");
    if(!Warriors){
        std::cerr << "Cannot open 'Warriors.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream Sorcerers("input/Sorcerers.txt");
    if(!Sorcerers){
        std::cerr << "Cannot open 'Sorcerers.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream Paladins("input/Paladins.txt");
    if(!Paladins){
        std::cerr << "Cannot open 'Paladins.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream Dragons("input/Dragons.txt");
    if(!Dragons){
        std::cerr << "Cannot open 'Dragons.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream Spirits("input/Spirits.txt");
    if(!Spirits){
        std::cerr << "Cannot open 'Spirits.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream Exoskeletons("input/Exoskeletons.txt");
    if(!Exoskeletons){
        std::cerr << "Cannot open 'Exoskeletons.txt'\n";
        return FILE_ERROR;
    }    

    std::ifstream Weapons("input/Weapons.txt");
    if(!Weapons){
        std::cerr << "Cannot open 'Weapons.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream Armors("input/Armors.txt");
    if(!Armors){
        std::cerr << "Cannot open 'Armors.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream Potions("input/Potions.txt");
    if(!Potions){
        std::cerr << "Cannot open 'Potions.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream FireSpells("input/FireSpells.txt");
    if(!FireSpells){
        std::cerr << "Cannot open 'FireSpells.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream IceSpells("input/IceSpells.txt");
    if(!IceSpells){
        std::cerr << "Cannot open 'IceSpells.txt'\n";
        return FILE_ERROR;
    }

    std::ifstream LightningSpells("input/LightningSpells.txt");
    if(!LightningSpells){
        std::cerr << "Cannot open 'LightningSpells.txt'\n";
        return FILE_ERROR;
    }

    /* ==========================================| D I S P L A Y  A V A I L A B L E  H E R O E S |======================================== */

    std::cout << "\t\t Available Warriors\n";
    std::cout << "\t\t********************\n\n"; 
    std::cout << "\t\tName" << "\t\t " << "Health Power" << "\t  " << "Magic Power" << "\t  " << "Strength" << "\t  " << 
    "Dexterity" << "\t  " << "Agility"  << "\t  " << "Money" << "\t\t" << "Experience\n";
    std::cout << "\t\t---------------------------------------------------------------------------------------------------------------------------\n";
    std::map<std::string, std::tuple<int, double, double, double, double, double, double, double> > warriors;

    while(Warriors >> name >> Lvl >> H >> mgP >> str >> dex >> ag >> mon >> exp){
        warriors[name] = std::make_tuple(Lvl, H, mgP, str, dex, ag, mon, exp);
        std::stringstream moneyStr;
        moneyStr << std::fixed << std::setprecision(2) << mon;
        std::string mStr = moneyStr.str();
        std::cout << "\t\t" << std::left << std::setw(15-name.length()) << name << "\t  " << H << "\t\t   " <<
        mgP << "\t\t   " << str << "\t\t   " << dex << "\t\t   " << ag << "\t\t  " << std::left << std::setw(5) << mStr+" $" << "\t " << exp << "\n";
    } Warriors.close();


    std::cout << "\n\n\t\t Available Sorcerers\n";
    std::cout << "\t\t*********************\n\n";
    std::cout << "\t\tName" << "\t\t " << "Health Power" << "\t  " << "Magic Power" << "\t  " << "Strength" << "\t  " << 
    "Dexterity" << "\t  " << "Agility"  << "\t  " << "Money" << "\t\t" << "Experience\n";
    std::cout << "\t\t-------------------------------------------------------------------------------------------------------------------------\n";

    std::map<std::string, std::tuple<int, double, double, double, double, double, double, double> > sorcerers;
    while(Sorcerers >> name >> Lvl >> H >> mgP >> str >> dex >> ag >> mon >> exp){
        sorcerers[name] = std::make_tuple(Lvl, H, mgP, str, dex, ag, mon, exp);
        std::stringstream moneyStr;
        moneyStr << std::fixed << std::setprecision(2) << mon;
        std::string mStr = moneyStr.str();
        std::cout << "\t\t" << std::left << std::setw(15-name.length()) << name << "\t  " << H << "\t\t   " <<
        mgP << "\t\t   " << str << "\t\t   " << dex << "\t\t   " << ag << "\t\t  " << std::left << std::setw(5) << mStr+" $" << "\t " << exp << "\n";
    } Sorcerers.close();
    

    std::cout << "\n\n\t\t Available Paladins\n";
    std::cout << "\t\t********************\n\n";
    std::cout << "\t\tName" << "\t\t " << "Health Power" << "\t  " << "Magic Power" << "\t  " << "Strength" << "\t  " << 
    "Dexterity" << "\t  " << "Agility"  << "\t  " << "Money" << "\t\t" << "Experience\n";
    std::cout << "\t\t---------------------------------------------------------------------------------------------------------------------------\n";
    std::map<std::string, std::tuple<int, double, double, double, double, double, double, double> > paladins;
    while(Paladins >> name >> Lvl >> H >> mgP >> str >> dex >> ag >> mon >> exp){
        paladins[name] = std::make_tuple(Lvl, H, mgP, str, dex, ag, mon, exp);
        std::stringstream moneyStr;
        moneyStr << std::fixed << std::setprecision(2) << mon;
        std::string mStr = moneyStr.str();
        std::cout << "\t\t" << std::left << std::setw(15-name.length()) << name << "\t  " << H << "\t\t   " <<
        mgP << "\t\t   " << str << "\t\t   " << dex << "\t\t   " << ag << "\t\t  " << std::left << std::setw(5) << mStr+" $" << "\t " << exp << "\n";
    } Paladins.close();

    /* ==========================================| C H O O S E  H E R O E S  F O R  T H E  G A M E |======================================== */

    short int numberOfHeroes = 0;
    std::string choice; 

    std::cout << BOLDBLUE << "\n\n\t\tYou can choose up to 3 Heroes!\n" << RESET;
    
    while(true) {
        std::string hName;
        std::cout << "\t\tName of Hero: "; std::cin >> hName;

        while (!warriors.count(hName) && !sorcerers.count(hName) && !paladins.count(hName)) {
        std::cout << "\t\t" << RED << "WARNING! " << RESET << "No such Hero! Please select a name from above.\n\n";
        std::cout << "\t\tName of Hero: "; std::cin >> hName;
        }
        
        if (warriors.count(hName)) {
            std::cout << "\t\tYou have selected a Warrior! A choice of Strength and Agility!\n";
            Lvl = std::get<0>(warriors[hName]);
            H = std::get<1>(warriors[hName]);
            mgP = std::get<2>(warriors[hName]);
            str = std::get<3>(warriors[hName]);
            dex = std::get<4>(warriors[hName]);
            ag = std::get<5>(warriors[hName]);
            mon = std::get<6>(warriors[hName]);
            exp = std::get<7>(warriors[hName]);
        } else
        if (sorcerers.count(hName)) {
            std::cout << "\t\tYou have selected a Sorcerer! A choice of Dexterity and Agility!\n";
            Lvl = std::get<0>(sorcerers[hName]);
            H = std::get<1>(sorcerers[hName]);
            mgP = std::get<2>(sorcerers[hName]);
            str = std::get<3>(sorcerers[hName]);
            dex = std::get<4>(sorcerers[hName]);
            ag = std::get<5>(sorcerers[hName]);
            mon = std::get<6>(sorcerers[hName]);
            exp = std::get<7>(sorcerers[hName]);
        } else if (paladins.count(hName)) {
            std::cout << "\t\tYou have selected a Paladin! A choice of Strength and Dexterity!\n";
            Lvl = std::get<0>(paladins[hName]);
            H = std::get<1>(paladins[hName]);
            mgP = std::get<2>(paladins[hName]);
            str = std::get<3>(paladins[hName]);
            dex = std::get<4>(paladins[hName]);
            ag = std::get<5>(paladins[hName]);
            mon = std::get<6>(paladins[hName]);
            exp = std::get<7>(paladins[hName]);
        }
        Hero * chosenH = new Hero(hName, Lvl, H, mgP, str, dex, ag, mon, exp);
        myHeroes.push_back(chosenH);
        
        if (++numberOfHeroes == 3) break; 

        std::cout << "\n\t\tDo you want to get another Hero? Type YES/NO\n\t\t";
        do {
            std::cin>>choice;
            if (choice != "YES" && choice != "NO")
                std::cout << "\t\tWrong choice. Please choose between YES/NO.\n\t\t";
        } while (choice != "YES" && choice != "NO");
        if (choice == "NO") break;
    }

    /* ==========================================| I M P O R T  A L L  M O N S T E R S |======================================== */

    while(Dragons >> name >> Lvl >> H >> dmg >> arm >> msP){
        availableMonsters.push_back(new Dragon(name, Lvl, H, dmg, arm, msP));
    } Dragons.close();

    while(Spirits >> name >> Lvl >> H >> dmg >> arm >> msP){
        availableMonsters.push_back(new Spirit(name, Lvl, H, dmg, arm, msP));
    } Spirits.close();

    while(Exoskeletons >> name >> Lvl >> H >> dmg >> arm >> msP){
        availableMonsters.push_back(new Exoskeleton(name, Lvl, H, dmg, arm, msP));
    } Exoskeletons.close();
    
    while(Weapons >> name >> price >> minLvlRequired >> dmg >> hands){
        Weapon * tmp = new Weapon(name, price, minLvlRequired, dmg, hands);
        market->insertWeapon(tmp);
        allWeapons[name] = tmp;
    } Weapons.close();

    while(Armors >> name >> price >> minLvlRequired >> protectionLvl){
        Armor * tmp = new Armor(name, price, minLvlRequired, protectionLvl);
        market->insertArmor(tmp);
        allArmors[name] = tmp;
    } Armors.close();

    while(Potions >> name >> price >> minLvlRequired >> gain){
        Potion * tmp = new Potion(name, price, minLvlRequired, gain);
        market->insertPotion(tmp);
        allPotions[name] = tmp;
    } Potions.close();

    while(IceSpells >> name >> price >> minLvlRequired >> dmg >> magicLvlRequired >> attackingWeakness){
        IceSpell* tmp = new IceSpell(name, price, minLvlRequired, dmg, magicLvlRequired, attackingWeakness);
        market->insertIceSpell(tmp);
        allIceSpells[name] = tmp;
    } IceSpells.close();

    while(FireSpells >> name >> price >> minLvlRequired >> dmg >> magicLvlRequired >> defensiveWeakness){
        FireSpell *tmp = new FireSpell(name, price, minLvlRequired, dmg, magicLvlRequired, defensiveWeakness);
        market->insertFireSpell(tmp);
        allFireSpells[name] = tmp;
    } FireSpells.close();

    while(LightningSpells >> name >> price >> minLvlRequired >> dmg >> magicLvlRequired >> agilityWeakness){
        LightningSpell * tmp = new LightningSpell(name, price, minLvlRequired, dmg, magicLvlRequired, attackingWeakness);
        market->insertLightningSpell(tmp);
        allLightningSpells[name] = tmp;
    } LightningSpells.close();

    gamePlay(market);   // start the game

    return 0;
}