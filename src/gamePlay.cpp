/* file: gamePlay.cpp */

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>

#include "../include/gamePlay.hpp"

void gamePlay(Market *market){
    Grid grid;  
    int no_of_players = myHeroes.size();

    grid.displayMap();

    // game loop
    while(true){
    bool wrongIn = true;
    bool accessible = true;
    bool readOnly = false;

    do{
        int dx, dy, idx;
        int x = myHeroes[0]->getX(), y = myHeroes[0]->getY();
        
        char dir;
        std::cout << "\t\t"; std::cin >> dir;
        
        switch(dir) {
            case 'A': {
                dx = 0, dy = -1;
                wrongIn = false;
                break;
            }
            case 'W': {
                dx = -1, dy = 0;
                wrongIn = false;
                break;
            }
            case 'S': {
                dx = 1, dy = 0;
                wrongIn = false;
                break;
            }
            case 'D': {
                dx = 0, dy = 1;
                wrongIn = false;
                break;
            }
            case 'I': {                
                for(int i=0; i<no_of_players; i++){
                    if (myHeroes[i]->getszI() + myHeroes[i]->getszS() == 0) {
                        std::cerr << RED << "\n\t\tWARNING! " << RESET << myHeroes[i]->getName() << "'s inventory is empty!\n\n";
                        continue;
                    }
                    std::cout << "\n\t\t" << BOLDCYAN << myHeroes[i]->getName() << "'s Inventory" << RESET << "\n";
                    myHeroes[i]->checkInventory();
                }
                
                char c;
                for(int i=0; i<no_of_players; ++i){
                    if (myHeroes[i]->getszI() + myHeroes[i]->getszS() == 0) continue;
                    bool wrong = true;
                    do{
                        std::string name;
                        std::cout << "\n\t\tFor " << myHeroes[i]->getName() << " choose from below:\n";
                        std::cout << "\t\t[E]: Equip \t [U]:Use \t [N]: Close inventory\n";
                        std::cout << "\t\t"; std::cin>>c;
                        int idx;
                        if(c == 'E'){
                            std::cout << "\n\t\tChoose from the items (Weapon/Armor) above, for equip.\n\t\t";
                            do{
                                std::cin>>name;
                                if(allArmors.find(name) != allArmors.end()){
                                    myHeroes[i]->equip(allArmors[name]);
                                    std::cout << CYAN << "\n\t\t" << myHeroes[i]->getName() << " is equiping the " << name << " . . .\n" << RESET;
                                    break;
                                }
                                else if(allWeapons.find(name) != allWeapons.end()){
                                    myHeroes[i]->equip(allWeapons[name]);
                                    std::cout << CYAN << "\n\t\t" << myHeroes[i]->getName() << " is equiping the " << name << " . . .\n" << RESET;
                                    break;
                                }
                                std::cout << RED << "\t\tWARNING! " << RESET << "No such Armor/Weapon! Try again.\n\t\t";
                            } while(true);
                            wrong = false;
                        }
                        else if(c == 'U'){
                            if(myHeroes[i]->potionExist() == false){
                                std::cout<<"\t\tNo potions available\n";
                                break;
                            }

                            std::cout << "\n\t\tChoose from the potions above, for use.\n\t\t";
                            do{
                                std::cin>>name;
                                if(allPotions.find(name) != allPotions.end()){
                                    myHeroes[i]->use(allPotions[name]);
                                    std::cout << CYAN << "\n\t\t" << myHeroes[i]->getName() << " is using the " << name << " . . .\n" << RESET;
                                    break;
                                }
                                std::cout << RED << "\t\tWARNING! " << RESET << "No such Potion! Try again.\n\t\t";
                            } while(true);
                            wrong = false;
                        }
                        else if(c == 'N'){
                            break;
                        }
                    } while(wrong); 
                }
                wrongIn = false;
                readOnly = true;
                break;
            }
            case 'T': {
                std::cout << BOLDBLUE << "\n\t\t******************** H E R O E S  S T A T S ********************\n\n" << RESET;
                std::cout << CYAN << "\t\tName\t\t\t Level\t\t\t " << GREEN << "Health Power\t\t" << RESET << "\n"; 
                std::cout << "\t\t----------------------------------------------------------------\n";
                for(int i=0; i<no_of_players; ++i) myHeroes[i]->displayStats();
                std::cout<<"\n\n";
                wrongIn = false;
                readOnly = true;
                break;
            }
            case 'Q': {
                std::cout<<"\n\t\tExiting. . . Goodbye!\n\n";
                return;
            }
            default:
                wrongIn = true;
        } // END SWITCH

        // checking the input
        if(!wrongIn && !readOnly){
            x += dx, y += dy;
            if (x < 0 || x >= N || y < 0 || y >= M || grid.getCell(x, y) == 'X') {
                accessible = false;
                std::cout << RED << "\n\t\tWARNING" << RESET <<": Can't go there!\n";
                grid.displayMap();
                break;
            } // END IF
            if(accessible && grid.getCell(x,y) == '.'){
                for (int i=0; i<no_of_players; i++)
                    myHeroes[i]->move(dx,dy);    
                    
                grid.moveInGrid(x - dx, y - dy, x, y);
                // fight with monsters based on some probability
                double fightProb = 1/(double)N;

                if (1.0 * rndMAX.getNum() < fightProb * (RAND_MAX + 1.0)) {
                    std::cout << BOLDRED << "\n\t\t ⚔ F I G H T  W I T H  M O N S T E R S ⚔ \n" << RESET;
                    bool endFight = false;
                    int round = 0;
                    // pick up random monsters for the fight
                    std::vector<Monster*> fightMonsters, tmpMonsters;
                    for (int i=0; i<no_of_players; i++){
                        int rndIdx = rndMon.getNum();
                        fightMonsters.push_back(availableMonsters[rndIdx]);
                        tmpMonsters.push_back(fightMonsters[rndIdx]);
                        availableMonsters.erase(availableMonsters.begin() + rndIdx); // no same monster selected from random
                        std::cout << "\n\t\t" << myHeroes[i]->getName() << RED << "  f i g h t s  w i t h  " << RESET << fightMonsters[i]->getName() << "\n";
                    }
                    while (!tmpMonsters.empty()) {
                        availableMonsters.push_back(tmpMonsters.back());
                        tmpMonsters.pop_back();
                    }
                    int no_of_monsters = fightMonsters.size();

                    std::cout << "\n\t\tHeroes start the fight!\n";

                    do{
                        std::cout << BOLDBLUE << "\n\t\t******************** H E R O E S  S T A T S ********************\n\n" << RESET;
                        std::cout << CYAN << "\t\tName\t\t\t Level\t\t\t " << GREEN << "Health Power\t\t" << RESET << "\n"; 
                        std::cout << "\t\t----------------------------------------------------------------\n";
                        for(int i=0; i<no_of_players; ++i) myHeroes[i]->displayStats();
                        std::cout<<"\n\n";
                        std::cout << BOLDBLUE << "\n\t\t******************* M O N S T E R S  S T A T S ******************\n\n" << RESET;
                        std::cout << CYAN << "\t\tName\t\t\t Level\t\t\t " << GREEN << "Health Power\t\t" << RESET << "\n"; 
                        std::cout << "\t\t----------------------------------------------------------------\n";
                        for(int i=0; i<no_of_monsters; ++i) fightMonsters[i]->displayStats();
                        std::cout<<std::endl;

                        bool heroesDied = true;
                        bool monstersDied = true;
                        
                        std::cout << BOLDRED << "\n\t\tROUND: "<< ++round << RESET << "\n";
                        for (int i=0; i<no_of_players; i++)
                            if (myHeroes[i]->getHealthPower() > 0)
                                heroesDied = false;
                        
                        for (int i=0; i<no_of_monsters; i++)
                            if (fightMonsters[i]->getHealthPower() > 0)
                                monstersDied = false;
                            
                        if (heroesDied) {
                            std::cout << "\n\t\tAll heroes died!\n";
                            std::cout << BOLDRED << "\n\t\tD E F E A T ! ! !\n\n" << RESET; 
                            std::cout << BOLDRED << "\n\t\tE N D  O F  F I G H T ! ! !\n\n" << RESET;
                            endFight = true;
                            for (int i=0; i<no_of_players; i++)
                                myHeroes[i]->decrMoney(myHeroes[i]->getMoney()/2);
                            break;
                        } 
                        if (monstersDied){
                            std::cout << "\n\t\tAll monsters died!\n";
                            std::cout << BOLDGREEN << "\n\n\t\tV I C T O R Y ! ! !\n\n" << RESET;
                            std::cout << BOLDRED << "\n\t\tE N D  O F  F I G H T ! ! !\n\n" << RESET;
                            endFight = true;  
                            int lvl = myHeroes[0]->getLvl();
                            for(int i=0; i<no_of_players; ++i) myHeroes[i]->incrMoney(lvl + no_of_monsters);
                            for(int i=0; i<no_of_players; ++i) myHeroes[i]->incrExp(lvl + no_of_monsters);
                            break;
                        }

                        // heroes attack
                        std::cout << "\n\t\tHeroes are attacking...\n";
                        
                        char attackChoice;
                        bool wrongAttackIn = true;
                        
                        for(int i=0; i<no_of_players; ++i){
                            std::cout<<"\n\t\t"<<myHeroes[i]->getName()<< RED << "  f i g h t s  w i t h  " << RESET << fightMonsters[i]->getName() << "\n\n";
                            do {
                                wrongAttackIn = true;
                                std::cout << "\t\tChoose from the following:\n";
                                std::cout << "\n\t\t[A]: Attack \t [C]: Cast Spell \t [U]: Use\n\t\t";
                                std::cin >> attackChoice;
                                
                                switch(attackChoice){
                                    case 'A': {
                                        std::cout<<"\n\t\t"<< CYAN << myHeroes[i]->getName() << " is attacking " << fightMonsters[i]->getName() << RESET;
                                        for(int i=0; i<3; i++) {
                                            std::cout << CYAN << " ." << RESET; fflush(stdout);
                                            usleep(600000);
                                        } std::cout << "\n\n";
                                        myHeroes[i]->attack(fightMonsters[i]);
                                        wrongAttackIn = false;
                                        break;
                                    }
                                    case 'C': {
                                        if(myHeroes[i]->getszS() == false){
                                            std::cout<< RED << "\n\t\tWARNING! " << RESET << "You have no Spells!\n\n";
                                            break;
                                        }
                                        std::cout<<"\n\t\t"<< CYAN << myHeroes[i]->getName() << " is casting a Spell to " << fightMonsters[i]->getName() << RESET;
                                        for(int i=0; i<3; i++) {
                                            std::cout << CYAN << " ." << RESET; fflush(stdout);
                                            usleep(600000);
                                        } std::cout << "\n\n";
                                        myHeroes[i]->castSpell(fightMonsters[i]);
                                        wrongAttackIn = false;
                                        break;
                                    }
                                    case 'U': {
                                        if(myHeroes[i]->potionExist() == false){
                                            std::cout<< RED << "\n\t\tWARNING! " << RESET << "You have no Potions!\n\n";
                                            break;
                                        }
                                        std::cout << "\n\t\t" << BOLDCYAN << myHeroes[i]->getName() << "'s Inventory" << RESET << "\n";
                                        myHeroes[i]->checkInventory();
                                        do{
                                            std::cout << "\t\tChoose from the potions above, for use.\n\t\t";
                                            std::string name;
                                            std::cin>>name;
                                            if(allPotions.find(name) != allPotions.end()){
                                                std::cout<<"\n\t\t"<< CYAN << myHeroes[i]->getName() << " is using a Potion" << RESET;
                                                for(int i=0; i<3; i++) {
                                                    std::cout << CYAN << " ." << RESET; fflush(stdout);
                                                    usleep(600000);
                                                } std::cout << "\n\n";
                                                myHeroes[i]->use(allPotions[name]);
                                                break;
                                            }
                                        } while(true);
                                        wrongAttackIn = false;
                                        break;
                                    }
                                    default:
                                        std::cout << RED << "\n\t\tWARNING! " << RESET << "Wrong input!\n";
                                        wrongAttackIn = true;
                                }
                            } while(wrongAttackIn); // END DO
                        }
                        // monsters attack
                        std::cout << "\t\tMonsters are attacking back";
                        for(int i=0; i<3; i++) {
                            std::cout << " ."; fflush(stdout);
                            usleep(600000);
                        } std::cout << "\n\n";
                        for (int i=0; i<no_of_monsters; i++) 
                            fightMonsters[i]->attack(myHeroes[i]);

                        std::cout << "\n\t\tE N D  O F  R O U N D!\n";

                        if (!endFight){
                            for (int i=0; i<no_of_players; i++) {
                                myHeroes[i]->incrHealth(myHeroes[i]->getHealthPower()*0.01);
                                myHeroes[i]->incrMagic(myHeroes[i]->getMagicPower()*0.01);
                                myHeroes[i]->incrExp(rnd3.getNum());
                            }
                            
                            for (int i=0; i<no_of_monsters; i++){
                                fightMonsters[i]->incrHealth(fightMonsters[i]->getHealthPower()*0.01);
                            }
                        }
                    } while (!endFight); // END WHILE
                }
                // if any player has zero health after the fight, restore to it's half
                for (int i=0; i<no_of_players; i++) {
                    if (myHeroes[i]->getHealthPower() == 0)
                        myHeroes[i]->incrHealth(50);
                    else
                        myHeroes[i]->incrHealth(100);
                }
            }
            else if(accessible && grid.getCell(x, y) == 'M') {
                for (int i=0; i<no_of_players; i++)
                    myHeroes[i]->move(dx,dy);    

                grid.moveInGrid(x - dx, y - dy, x, y);
                                
                std::cout << RED << "\n\t\tWARNING: " << RESET << "You have reached a Market! Do you want to enter it? Type YES/NO\n\t\t";
                std::string choice;
                std::cin >> choice;

                while(choice!="NO" && choice!="YES") {
                    std::cout << "\t\tWrong input! Type YES/NO.\n\n\t\t";
                    std::cin >> choice;
                }
                
                if(choice == "NO") {
                    grid.displayMap();
                    continue;
                }
                
                market->displayMenu();
                // display my Team
                for(int i=0; i<no_of_players; ++i){
                    std::cout << "\n\t\t"<< RED << "WARNING! " << RESET << myHeroes[i]->getName() << " has " << myHeroes[i]->getMoney() << " $. Spend it wisely!\n";
                    bool wrong = true;
                    do{
                        std::cout << "\n\t\tChoose from below for " << myHeroes[i]->getName() << "!";
                        std::cout<<"\n\t\t[B]: Buy, [L]: Sell, [N]: Exit Market\n\t\t";
                    
                        std::cin>>dir;
                        int szi, szs;
                        std::string name;
                        switch(dir){
                            case 'B': {
                                do{
                                    std::cout<<"\t\tName of item: ";
                                    std::cin>>name;
                                } while (!market->buy(myHeroes[i], name));
                                std::cout << RED << "\t\tMessage from Market: " << RESET << myHeroes[i]->getName() << ", do you want anything else from the Market? Type YES/NO\n\t\t";
                                std::string marketChoice; std::cin >> marketChoice;
                                while (marketChoice!="YES" && marketChoice!="NO"){
                                    std::cout << RED << "\n\t\tWARNING! " << RESET << "Wrong input. Please choose between YES/NO.\n";
                                }
                                if (marketChoice == "NO") {
                                    std::cout << "\n\t\t" << myHeroes[i]->getName() << RED << "  i s  e x i t i n g  t h e  M a r k e t  . . ." << RESET << "\n\n";
                                    wrong = false;
                                }
                                break;
                            }
                            case 'L': {
                                myHeroes[i]->checkInventory();
                                if (myHeroes[i]->getszI() + myHeroes[i]->getszS() == 0) {
                                    std::cerr << RED << "\t\tWARNING! " << RESET << myHeroes[i]->getName() << "'s inventory is empty! Sell denied.\n\n";
                                    break;
                                }
                                std::cout<<"\t\tName of item: ";
                                std::cin>>name;
                                market->sell(myHeroes[i], name);
                                std::cout << RED << "\n\t\tMessage from Market: " << RESET << myHeroes[i]->getName() << ", do you want anything else from the Market? Type YES/NO\n\t\t";
                                std::string marketChoice; std::cin >> marketChoice;
                                while (marketChoice!="YES" && marketChoice!="NO"){
                                    std::cout << RED << "\n\t\tWARNING! " << RESET << "Wrong input. Please choose between YES/NO.\n";
                                }
                                if (marketChoice == "NO") {
                                    std::cout << "\n\t\t" << myHeroes[i]->getName() << RED << " i s  e x i t i n g  t h e  M a r k e t  . . ." << RESET << "\n\n"; 
                                    wrong = false;
                                }
                                break;
                            }
                            case 'N': {
                                std::cout << "\n\t\t" << myHeroes[i]->getName() << RED << " i s  e x i t i n g  t h e  M a r k e t  . . ." << RESET << "\n\n";
                                wrong = false;
                                break;
                            }
                            default:
                                std::cout << "\t\tWrong input! Try again.\n";
                                break;
                        } // END SWITCH
                    } while(wrong); // END DO WHILE
                }
                grid.displayMap();
                continue;
            } // END ELSE IF OF MARKET
            
        } // END IF
        else if (wrongIn){
            // wrong input
            std::cout<<"\n\t\tWrong key given! Check the menu controls.\n";
        } // END ELSE IF       
        grid.displayMap();  
    } while(wrongIn || !accessible);
    }
} 
