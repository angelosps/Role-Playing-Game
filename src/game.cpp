/* file: game.cpp */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

#include "../include/game.hpp"
#include "../include/rndGen.hpp"

enum buyType { item, spell };
enum spellType { ice, fire, lightning };

RndGen rnd3(0,2);
RndGen rnd5(0,4);
RndGen rnd10(0,9);
RndGen rndMAX(0,RAND_MAX-1);

/* ==================================== I T E M ==================================== */

Item::Item(std::string nam, double p, unsigned int lvl){
    name = nam;
    price = p;
    minLvlRequired = lvl;
}

Item::~Item(){}

void Item::display() {
    std::cout << "\n\t\t***** I T E M  D I S P L A Y *****\n";
    std::cout << "\t\t-------------------------------------\n";
    std::cout << "\t\tName:" << this->name << std::endl;
    std::cout << "\t\tPrice:" << this->price << std::endl;
    std::cout << "\t\tMin Level Required:" << this->minLvlRequired << std::endl;
}

/* ==================================== S P E L L ==================================== */

Spell::Spell(std::string nam, double p, unsigned int lvlReq, double dmg, unsigned int mglvl){
    name = nam;
    price = p;
    minLvlRequired = lvlReq;
    damage = dmg;
    magicLvlRequired = mglvl;
}

Spell::~Spell(){}

void Spell::display(){
    std::cout << "\n\t\t***** S P E L L  D I S P L A Y *****\n";
    std::cout << "\t\t-------------------------------------\n";
    std::cout << "\t\tName: " << this->name << std::endl;
    std::cout << "\t\tPrice: " << this->price << std::endl;
    std::cout << "\t\tMin Level Required: " << this->minLvlRequired << std::endl;
    std::cout << "\t\tDamage: " << this->damage << std::endl;
    std::cout << "\t\tMagic Level Required: " << this->magicLvlRequired << std::endl;
}

/* ==================================== I T E M  S U B C L A S S E S ==================================== */

Weapon::Weapon(std::string name, double price, int minLvlRequired, double damage, bool hands)
: Item(name, price, minLvlRequired) {
    this->name = name;
    this->price = price;
    this-> minLvlRequired = minLvlRequired;
    this-> damage = damage;
    this->hands = hands;
}

Weapon::~Weapon(){}


Armor::Armor(std::string name, double price, int minLvlRequired, double protectionLvl)
: Item(name, price, minLvlRequired) {
    this->name = name;
    this->price = price;
    this->minLvlRequired = minLvlRequired;
    this->protectionLvl = protectionLvl;
}

Armor::~Armor(){}


Potion::Potion(std::string name, double price, int minLvlRequired, double gain)
: Item(name, price, minLvlRequired) {
    this->name = name;
    this->price = price;
    this->minLvlRequired = minLvlRequired;
    this->gain = gain;
    this->used = false;
}

Potion::~Potion(){}


/* ==================================== S P E L L  S U B C L A S S E S ==================================== */


IceSpell::IceSpell(std::string name, double price, int minLvlRequired, double damage, int magicLvlRequired, double attackingWeakness) 
: Spell(name, price, minLvlRequired, damage, magicLvlRequired) {
    this->name = name;
    this->price = price;
    this->minLvlRequired = minLvlRequired;
    this->damage = damage;
    this->magicLvlRequired = magicLvlRequired;
    this->attackingWeakness = attackingWeakness;
}

IceSpell::~IceSpell(){}


FireSpell::FireSpell(std::string name, double price, int minLvlRequired, double damage, int magicLvlRequired, double defensiveWeakness) 
: Spell(name, price, minLvlRequired, damage, magicLvlRequired){
    this->name = name;
    this->price = price;
    this->minLvlRequired = minLvlRequired;
    this->damage = damage;
    this->magicLvlRequired = magicLvlRequired;
    this->defensiveWeakness = defensiveWeakness;
}

FireSpell::~FireSpell(){}


LightningSpell::LightningSpell(std::string name, double price, int minLvlRequired, double damage, int magicLvlRequired, double agilityWeakness)
: Spell(name, price, minLvlRequired, damage, magicLvlRequired){
    this->name = name;
    this->price = price;
    this->minLvlRequired = minLvlRequired;
    this->damage = damage;
    this->magicLvlRequired = magicLvlRequired;
    this->agilityWeakness = agilityWeakness;
}

LightningSpell::~LightningSpell(){}

/* ==================================== L I V I N G ==================================== */

Living::Living(std::string nam, int L, double H){
    name = nam;
    lvl = L;
    healthPower = H;
    x = y = 0;
}

Living::~Living(){}

void Living::move(int dx, int dy) { 
    this->x += dx; 
    this->y += dy; 
}

void Living::incrLvl(){
    lvl++;
}

void Living::displayStats() const { 
    std::cout << "\t\t" << std::setw(12) << name << "\t\t " << lvl << "\t\t\t " << GREEN << healthPower << RESET <<"\n"; 
}

void Living::incrHealth(double hP) {
    healthPower = std::min(100.0, healthPower + hP);
}

/* ==================================== M O N S T E R ==================================== */

Monster::Monster(std::string nam, int L, double H, double dmg, double arm, double msP) : Living(nam, L, H){
    damage = dmg, armor = arm, missProb = msP;
}

Monster::~Monster(){}

void Monster::attack(Living* hero) const{
    ((Hero*)hero)->getAttacked(damage*1.8);
}

bool Monster::missed() const{
    return (1.0 * rndMAX.getNum() < missProb * (RAND_MAX + 1.0));
}

void Monster::getAttacked(double strength){
    if(missed() != true){
        double dmg = 3 * std::max(0.0, strength - armor);
        armor = std::max(0.0, armor - strength);
        healthPower = std::max(0.0, healthPower - dmg);
    }
}

void Monster::reduceArmor(double reduce){
    healthPower = std::max(0.0, healthPower - reduce);
}

void Monster::reduceDamage(double reduce){
    damage = std::max(0.0, damage - reduce);
}

void Monster::reduceMissProb(double reduce){
    missProb = std::max(0.0, missProb - reduce);
}

/* ==================================== M O N S T E R  S U B C L A S S E S ==================================== */

Dragon::Dragon(std::string nam, int L, double H, double dmg, double arm, double msP) : Monster(nam, L, H, dmg, arm, msP) {}

Dragon::~Dragon(){}


Exoskeleton::Exoskeleton(std::string nam, int L, double H, double dmg, double arm, double msP) : Monster(nam, L, H, dmg, arm, msP) {}

Exoskeleton::~Exoskeleton() {}


Spirit::Spirit(std::string nam, int L, double H, double dmg, double arm, double msP) : Monster(nam, L, H, dmg, arm, msP) {}

Spirit::~Spirit() {}

/* ==================================== H E R O ==================================== */

Hero::Hero(std::string nam, int L, double H, double mgP, double str, double dex, double ag, double mon, double exp) : Living(nam, L, H) {
    magicPower = mgP;
    strength = str;
    dexterity = dex;
    agility = ag;
    money = mon;
    experience = exp;
}

Hero::~Hero() {}

void Hero::levelUp(){ strength += rnd5.getNum(), dexterity += rnd5.getNum(), agility += rnd5.getNum(); }

double Hero::attack(Living* mon) const{
    ((Monster*)mon)->getAttacked(2.3*strength);
}

bool Hero::missed(double missProb) const{
    return (1.0 * rndMAX.getNum() < missProb * (RAND_MAX + 1.0));
}

void Hero::getAttacked(double damage){
    if(missed(agility) != true){
        healthPower = std::max(0.0, healthPower - 3 * damage);
    }
}

void Hero::buyItem(Item* item){
    int price = item->getPrice();
    if(price <= money && lvl >= item->getMinLvlRequired()){
        money -= price;
        Items.push_back(item);
    } else {
        std::cout << RED << "\t\tWARNING! " << RESET << "You can't buy that Item!\n\n";
    }
}

void Hero::buySpell(Spell* spell){
    int price = spell->getPrice();
    if(price <= money && lvl >= spell->getMinLvlRequired()){
        money -= price;
        Spells.push_back(spell);
    } else {
        std::cout << RED << "\t\tWARNING! " << RESET << "You can't buy that Spell!\n\n";
    }
}

void Hero::sellItem(std::string name){
    for(int i=0; i<Items.size(); ++i){
        if(Items[i]->getName() == name){
            money += Items[i]->getPrice() / 2;
            Items.erase(Items.begin() + i);
            std::cout<< RED << "\n\t\tMessage from Market: " << RESET << "Item sold successfully!\n";
            break;
        }
    }
}

void Hero::sellSpell(std::string name){
    for(int i=0; i<Spells.size(); ++i){
        if(Spells[i]->getName() == name){
            money += Spells[i]->getPrice() / 2;
            Spells.erase(Spells.begin() + i);
            std::cout<< RED << "\n\t\tMessage from Market: " << RESET << "Spell sold successfully!\n";
            break;
        }
    }
}

bool Hero::potionExist(){
    for(int i=0; i<Items.size(); ++i){
        if(allPotions.find(Items[i]->getName()) != allPotions.end()) return true;
    }
    return false;
}

void Hero::checkInventory(){
    if (Items.size() == 0)
        std::cerr << RED << "\t\tWARNING! " << RESET << "You don't have any Items!\n\n";
    else for(int i=0; i<Items.size(); ++i) Items[i]->display();
    if (Spells.size() == 0)
        std::cerr << RED << "\t\tWARNING! " << RESET << "You don't have any Spells!\n\n";
    for(int i=0; i<Spells.size(); ++i) Spells[i]->display();
}

void Hero::equip(Armor* arm){
    if(lvl >= arm->getMinLvlRequired()){
        healthPower += arm->getProtectionLvl();
        for(int i=0; i<Items.size(); ++i)
            if(Items[i]->getName() == arm->getName()){
                Items.erase(Items.begin() + i);
                break;
            }
    }
}

void Hero::equip(Weapon* wep){
    if(lvl >= wep->getMinLvlRequired()){
        strength += wep->getDamage();
        for(int i=0; i<Items.size(); ++i)
            if(Items[i]->getName() == wep->getName()){
                Items.erase(Items.begin() + i);
                break;
            }
    }
}

void Hero::use(Potion* potion){
    double gain = potion->getGain();
    std::string name = potion->getName();
    if(lvl >= potion->getMinLvlRequired()){
        if(name[0] == 'H') incrHealth(gain);
        else if(name[0] == 'S') incrStrength(gain);
        else if(name[0] == 'M') incrMagic(gain);
        else if(name[0] == 'A'){
            incrHealth(gain);
            incrStrength(gain);
            incrMagic(gain);
        }
    }
    for(int i=0; i<Items.size(); ++i)
        if(Items[i]->getName() == name){
            Items.erase(Items.begin() + i);
            break;
        }
}

void Hero::castSpell(Monster* monster){
    if(Spells.empty()) {
        std::cerr << RED << "\t\tWARNING! " << RESET << "You don't have any Spells!\n\n";
        return;
    }
    int idx = rand() % Spells.size();
    Spell* spell = Spells[idx];
    double dmg = spell->getDamage();
    std::string name = spell->getName();

    if(lvl >= spell->getMinLvlRequired()) {
        monster->getAttacked(dmg);
        if(allIceSpells.find(name) != allIceSpells.end())
            monster->reduceArmor(((IceSpell*)spell)->attackingWeakness);
        else if(allFireSpells.find(name) != allFireSpells.end())
            monster->reduceDamage(((FireSpell*)spell)->defensiveWeakness);
        else
            monster->reduceMissProb(((LightningSpell*)spell)->agilityWeakness);
    }

}

void Hero::incrMoney(double mon) {
    this->money += mon;
}

void Hero::decrMoney(double mon) {
    this->money -= mon;
}

void Hero::incrStrength(double gain){
    strength += gain;
}

void Hero::incrExp(double exp){
    experience += exp;
    if(experience >= 5){
        experience -= 5;
        lvl++; // incrLvl
        this->levelUp(); // levelUp 
        std::cout << "\n\t\t" << this->getName() << " has just " << BOLDCYAN <<  " L E V E L E D  U P  ! ! !" << RESET << "\n\n";
    }
}
void Hero::addItem(Item* item) {
    Items.push_back(item);
}
        
void Hero::addItem(Spell* spell) {
    Spells.push_back(spell);
}

int Hero::getszI() const{
    return Items.size();
}

int Hero::getszS() const{
    return Spells.size();
}

void Hero::incrMagic(double mP) {
    this->magicPower += mP;
}

/* ==================================== H E R O  S U B C L A S S E S ==================================== */

Warrior::Warrior(std::string nam, int L, double H, double mgP, double str, double dex, double ag, double mon, double exp) 
: Hero(nam, L, H, mgP, str, dex, ag, mon, exp) {}

Warrior::~Warrior() {}


Sorcerer::Sorcerer(std::string nam, int L, double H, double mgP, double str, double dex, double ag, double mon, double exp) 
: Hero(nam, L, H, mgP, str, dex, ag, mon, exp) {}

Sorcerer::~Sorcerer() {}


Paladin::Paladin(std::string nam, int L, double H, double mgP, double str, double dex, double ag, double mon, double exp) 
: Hero(nam, L, H, mgP, str, dex, ag, mon, exp) {}

Paladin::~Paladin(){}

/* ==================================== M A R K E T ==================================== */

Market::Market(){}

Market::~Market(){}

void Market::insertWeapon(Weapon* wp){
    this->weapons.push_back(wp);
}

void Market::insertArmor(Armor* arm) {
    this->armors.push_back(arm);
}
        
void Market::insertPotion(Potion* pt){
    this->potions.push_back(pt);
}
        
void Market::insertIceSpell(IceSpell* iS){
    this->iceSpells.push_back(iS);
}
    
void Market::insertFireSpell(FireSpell* fS){
    this->fireSpells.push_back(fS);
}

void Market::insertLightningSpell(LightningSpell* lS){
    this->lightningSpells.push_back(lS);
}

void Market::displayItems(){
    std::cout << "\n\n\n";
    std::cout << "\t\t Available Weapons\n";
    std::cout << "\t\t********************\n";
    std::cout << "\t\tName" << "\t\t" << "Price" << "\t   " << "Unlock Level" << "\t       " << "Damage\n";
    std::cout << "\t\t------------------------------------------------------\n";

    for(std::vector<Weapon*>::iterator it = weapons.begin(); it!=weapons.end(); ++it)
        std::cout << "\t\t" << (*it)->getName() << "\t\t" << (*it)->getPrice() << "\t\t" << (*it)->getMinLvlRequired() << "\t\t" << (*it)->getDamage() << std::endl;
    std::cout << "\n\n";

    std::cout << "\t\t Available Armors\n";
    std::cout << "\t\t********************\n";
    std::cout << "\t\tName" << "\t\t\t" << "Price" << "\t   " << "Unlock Level" << "\t       " << "Protection Level\n";
    std::cout << "\t\t-----------------------------------------------------------------------\n";
    for(std::vector<Armor*>::iterator it = armors.begin(); it!=armors.end(); ++it)
        std::cout << "\t\t" << (*it)->getName() << "\t\t" << (*it)->getPrice() << "\t\t" << (*it)->getMinLvlRequired() << "\t\t" << (*it)->getProtectionLvl() << std::endl;
    std::cout <<"\n\n";

    std::cout << "\t\t Available Potions\n";
    std::cout << "\t\t********************\n";
    std::cout << "\t\tName" << "\t\t\t" << "Price" << "\t   " << "Unlock Level" << "\t       " << "Agility Gain\n";
    std::cout << "\t\t-------------------------------------------------------------------------------\n";
    for(std::vector<Potion*>::iterator it = potions.begin(); it!=potions.end(); ++it)
    std::cout << "\t\t" << (*it)->getName() << "\t\t" << (*it)->getPrice() << "\t\t" << (*it)->getMinLvlRequired() << "\t\t" << (*it)->getGain() << std::endl;
    std::cout <<"\n\n";

}

void Market::displaySpells(){
    std::cout << "\n\n\n";
    std::cout << "\t\t Available Ice Spells\n";
    std::cout << "\t\t**********************\n";
    std::cout << "\t\tName" << "\t\t\t" << "Price" << "\t   " << "Unlock Level" << "\t\t" << "Damage" << "\t\t" << "Minimum Magic Power" << "\t\t" << "Enemy's Attack Decrease %\n";
    std::cout << "\t\t-----------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    for(std::vector<IceSpell*>::iterator it = iceSpells.begin(); it!=iceSpells.end(); ++it)
        std::cout << "\t\t" << (*it)->getName() << "\t\t" << (*it)->getPrice() << "\t\t" << (*it)->getMagicLvlRequired() << "\t\t" << (*it)->getDamage() << "\t\t\t" << (*it)->getMagicLvlRequired() << "\t\t\t\t" << (*it)->attackingWeakness << std::endl;
    std::cout <<"\n";

    std::cout << "\t\t Available Fire Spells\n";
    std::cout << "\t\t************************\n";
    std::cout << "\t\tName" << "\t\t\t" << "Price" << "\t   " << "Unlock Level" << "\t\t" << "Damage" << "\t\t" << "Minimum Magic Power" << "\t\t" << "Enemy's Defence Decrease %\n";
    std::cout << "\t\t------------------------------------------------------------------------------------------------------------------------------------\n";
    for(std::vector<FireSpell*>::iterator it = fireSpells.begin(); it!=fireSpells.end(); ++it)
        std::cout << "\t\t" << (*it)->getName() << "\t\t" << (*it)->getPrice() << "\t\t" << (*it)->getMinLvlRequired() << "\t\t" << (*it)->getDamage() << "\t\t\t" << (*it)->getMagicLvlRequired() << "\t\t\t\t" << (*it)->defensiveWeakness << std::endl;
    std::cout <<"\n";

    std::cout << "\t\t Available Lightning Spells" << std::endl;
    std::cout << "\t\t****************************" << std::endl;
    std::cout << "\t\tName" << "\t\t\t" << "Price" << "\t   " << "Unlock Level" << "\t\t" << "Damage" << "\t\t" << "Minimum Magic Power" << "\t\t" << "Enemy's Poss. of Avoiding Attack Decrease %" << std::endl;
    std::cout << "\t\t--------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    for(std::vector<LightningSpell*>::iterator it = lightningSpells.begin(); it!=lightningSpells.end(); ++it)
        std::cout << "\t\t" << (*it)->getName() << "\t\t" << (*it)->getPrice() << "\t\t" << (*it)->getMinLvlRequired() << "\t\t" << (*it)->getDamage() << "\t\t\t" << (*it)->getMagicLvlRequired() << "\t\t\t\t" << (*it)->agilityWeakness << std::endl;
    std::cout <<"\n";
}

void Market::displayMenu(){
    std::cout << BOLDRED << "\n\t\t\t*************** W E L C O M E   T O   T H E   M A R K E T ! ***************\n" << RESET;  
    displayItems();
    displaySpells();
    std::cout<<"\n\n";
}

bool Market::buy(Hero *hero, std::string name){
    for(int i=0; i<weapons.size(); ++i){
        if(weapons[i]->getName() == name){
            hero->buyItem(weapons[i]);
            std::cout<< RED << "\t\tMessage from Market: " << RESET << "Weapon bought successfully!\n\n";
            //weapons.erase(weapons.begin() + i); // 
            return true;
        }
    }
    for(int i=0; i<armors.size(); ++i){
        if(armors[i]->getName() == name){
            hero->buyItem(armors[i]);
            std::cout<< RED << "\t\tMessage from Market: " << RESET << "Armor bought successfully!\n\n";
            //armors.erase(armors.begin() + i);
            return true;
        }
    }
    for(int i=0; i<potions.size(); ++i){
        if(potions[i]->getName() == name){
            hero->buyItem(potions[i]);
            std::cout<< RED << "\t\tMessage from Market: " << RESET << "Potion bought successfully!\n\n";
            //potions.erase(potions.begin() + i);
            return true;
        }
    }
    for(int i=0; i<iceSpells.size(); ++i){
        if(iceSpells[i]->getName() == name){
            hero->buySpell(iceSpells[i]);
            std::cout<< RED << "\t\tMessage from Market: " << RESET << "IceSpell bought successfully!\n\n";
            //iceSpells.erase(iceSpells.begin() + i);
            return true;
        }
    }
    for(int i=0; i<fireSpells.size(); ++i){
        if(fireSpells[i]->getName() == name){
            hero->buySpell(fireSpells[i]);
            std::cout<< RED << "\t\tMessage from Market: " << RESET << "FireSpell bought successfully!\n\n";
            //fireSpells.erase(fireSpells.begin() + i);
            return true;
        }
    }
    for(int i=0; i<lightningSpells.size(); ++i){
        if(lightningSpells[i]->getName() == name){
            hero->buySpell(lightningSpells[i]);
            std::cout<< RED << "\t\tMessage from Market: " << RESET << "LightningSpell bought successfully!\n\n";
            //lightningSpells.erase(lightningSpells.begin() + i);
            return true;
        }
    }
    std::cout << RED << "\t\tWARNING! " << RESET << "No such Item/Spell! Please select from the list above.\n\n";
    return false;
}

void Market::sell(Hero *hero, std::string name){
    hero->sellItem(name);
    hero->sellSpell(name);
}

/* ==================================== G R I D ==================================== */

Grid::Grid(){
    for (int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            this->Map[i][j]='.';

    int k = rnd10.getNum() + 1;
    int l = rnd5.getNum() + 1;
    while (k--) setNonAccessible(rnd10.getNum(), rnd10.getNum()); 
    while (l--) setMarket(rnd10.getNum(), rnd10.getNum());

    Map[0][0] = 'H'; // heroes

    for (int i = 0; i<N; i++)
        for(int j=0; j<M; j++)
            OriginalMap[i][j] = Map[i][j];

    OriginalMap[0][0] = '.';
}

Grid::~Grid() {}

void Grid::displayMap(){
    std::cout << "\n\n";
    std::cout << YELLOW << "\t\t------------------------------" << RESET << std::endl;
    for (int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if (j == 0) std::cout << YELLOW << "\t\t|" << RESET;
            switch (this->Map[i][j]) {
                case '.' : std::cout << this->Map[i][j]; break;
                case 'X' : std::cout << BOLDWHITE << this->Map[i][j] << RESET; break;
                case 'H' : std::cout << BOLDGREEN << this->Map[i][j] << RESET; break;
                case 'M' : std::cout << BOLDRED << this->Map[i][j] << RESET; break;
            }
            if (j < N-1) std::cout << "  ";
            if (j == N-1) std::cout << YELLOW << "|" << RESET;
        }
        
        if (i==0) std::cout << YELLOW << "\t\t" << RESET << BOLDYELLOW << " =====  M I N I  M E N U  ===== " << RESET;
        if (i==2) std::cout << YELLOW << "\t\t - " << RESET << "Move with W-S-A-D" << YELLOW << RESET;
        if (i==3) std::cout << YELLOW << "\t\t - " << RESET << "[ T ] : Player Stats" << YELLOW << RESET; // heroes and monsters
        if (i==4) std::cout << YELLOW << "\t\t - " << RESET << "[ I ] : Inventory" << YELLOW << RESET; // heroes
        if (i==5) std::cout << YELLOW << "\t\t - " << RESET << "[ " << RED << "Q" << RESET << " ] : " << RED << "Quit" << RESET;
        if (i==7) {
            std::cout << "\t\t [ . ] : Common tile\t";
            std::cout << " [ " << RED << "M" << RESET << " ]" << RESET << " : Market" << RESET;
        }
        if (i==8){
            std::cout << "\t\t [ " << GREEN << "H" << RESET << " ] : " << RESET  << "Heroes\t\t" << RESET;
            std::cout << " [ " << BOLDWHITE << "X" << RESET << " ]" << RESET << " : Non Accessible tile" << RESET;
        }
        
        if (i<N-1) std::cout << "\n";
    }

    std::cout << YELLOW << "\n\t\t------------------------------" << RESET << std::endl;

}

void Grid::setMarket(int x, int y){
    Map[x][y] = 'M'; 
}

void Grid::setNonAccessible(int x, int y){
    Map[x][y] = 'X';
}

char Grid::getCell(int x, int y){
    return Map[x][y];
}

void Grid::moveInGrid(int x1, int y1, int x2, int y2){
    Map[x1][y1] = OriginalMap[x1][y1];
    Map[x2][y2] = 'H';
}

/* ==================================== E O F ==================================== */
