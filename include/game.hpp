/* file: game.hpp */

#pragma once

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

const unsigned int N = 10, M = 10;  // grid dimensions
enum gridSquare { nonAccessible, market, common };

/* ============================== Item ============================= */

class Item {
    protected:
        std::string name;
        double price;
        unsigned int minLvlRequired;
    public:
        Item(std::string, double, unsigned int);
        ~Item();
        std::string getName() const { return name; }
        double getPrice() const { return price; }
        unsigned int getMinLvlRequired() const { return minLvlRequired; } 
        void display();
};

/* ============================== Spell ============================= */

class Spell {
    protected:
        std::string name;
        double price;
        unsigned int minLvlRequired;
        double damage;
        unsigned int magicLvlRequired;
    public:
        Spell(std::string, double, unsigned int, double, unsigned int);
        ~Spell();
        std::string getName() const { return name; }
        double getPrice() const { return price; }
        unsigned int getMinLvlRequired() const { return minLvlRequired; } 
        double getDamage() const { return damage; }
        unsigned int getMagicLvlRequired() const { return magicLvlRequired; }
        void display();
};

/* ============================== Item Subclasses ============================= */

class Weapon : public Item {
    double damage;
    bool hands; // 1 or 2 hands required to use it. 
    public:
        Weapon(std::string, double, int, double, bool);
        ~Weapon();
        double getDamage() const { return damage; }
        bool getHands() const { return hands; }
};

class Armor : public Item {
    double protectionLvl;
    public:
        Armor(std::string, double, int, double);
        ~Armor();
        double getProtectionLvl() const { return protectionLvl; }
};

class Potion : public Item {
    double gain;
    bool used;  // one time use for the Potions so, when it is used, "used = true"
    public:
        Potion(std::string, double, int, double);
        ~Potion();
        int getGain() const { return gain; }
        bool getUsed() const { return used; }
};

/* ============================== Spell Subclasses ============================= */

class IceSpell : public Spell {
    public:
        IceSpell(std::string, double, int, double, int, double);
        ~IceSpell();
        double attackingWeakness; // decrease in opponent's attacking damage for some rounds. it "weakens" the opponent's attacking power for some rounds
};

class FireSpell : public Spell {
    public:
        FireSpell(std::string, double, int, double, int, double);
        ~FireSpell();
        double defensiveWeakness; // it "weakens" the opponent's defensive power for some rounds
};

class LightningSpell : public Spell {
    public:
        LightningSpell(std::string, double, int, double, int, double);
        ~LightningSpell();
        double agilityWeakness; // it "weakens" the opponent's agility power for some rounds
};

/* ============================== Grid ============================= */

class Grid {
    char Map[N][M];  // the actual Map
    char OriginalMap[N][M]; 
    public:
        Grid();
        ~Grid();
        void displayMap();
        void setMarket(int,int);
        void setNonAccessible(int,int);
        char getCell(int, int);
        void moveInGrid(int, int, int, int);
};

class Hero;

/* ============================== Market ============================= */

class Market { 
    std::vector<Weapon*> weapons;
    std::vector<Armor*> armors;
    std::vector<Potion*> potions;
    std::vector<IceSpell*> iceSpells; 
    std::vector<FireSpell*> fireSpells;
    std::vector<LightningSpell*> lightningSpells;
    
    public:
        Market();
        ~Market();

        void fillTheMarket();
        void insertWeapon(Weapon*);
        void insertArmor(Armor*);
        void insertPotion(Potion*);
        void insertIceSpell(IceSpell*);
        void insertFireSpell(FireSpell*);
        void insertLightningSpell(LightningSpell*);

        void displayMenu();
        void displayItems();
        void displaySpells();

        bool buy(Hero*, std::string);
        void sell(Hero*, std::string);
};

/* ============================== Living ============================= */


class Living{
    protected:
        std::string name;
        int lvl;
        double healthPower;
        int x, y;

    public:
        Living(std::string, int, double);
        ~Living();

        std::string getName() const { return name; }
        int getLvl() const { return lvl; }
        double getHealthPower() const { return healthPower; }
        int getX() const { return x; }
        int getY() const { return y; }
        
        void incrHealth(double);
        void incrLvl();
        void move(int, int);
        void displayStats() const; 
};

/* ============================== Living Subclasses ============================= */

/* ============================== Monster ============================= */

class Monster : public Living{
    protected:
        double damage;      // damage that causes to the opponent
        double armor;
        double missProb;    // probability to avoid an attack
//        int roundsLeft;     
    public:
        Monster(std::string, int, double, double, double, double);
        ~Monster();

        double getDamage() const { return damage; }
        double getArmor() const { return armor; }
        double getMissProb() const { return missProb; }

        void attack(Living*) const;

        bool missed() const;
        void getAttacked(double);
        void reduceDamage(double);
        void reduceArmor(double);
        void reduceMissProb(double);
};

/* ============================== Hero ============================= */

class Hero : public Living{
    protected:
        double magicPower;
        double strength;
        double dexterity;
        double agility;
        double money;
        double experience;
        std::vector<Item*> Items;
        std::vector<Spell*> Spells;
        int szI, szS;

    public:
        Hero(std::string, int, double, double mgP, double str, double dex, double ag, double mon, double exp);
        ~Hero();

        double getMagicPower() const { return magicPower; }
        double getStrength() const { return strength; }
        double getDexterity() const { return dexterity; }
        double getAgility() const { return agility; }
        double getMoney() const { return money; }
        double getExperience() const {return experience; }

        void levelUp();
        double attack(Living*) const;

        bool missed(double) const;    // if monster avoided an attack (based on missProb)
        void getAttacked(double);

        void buyItem(Item*);
        void buySpell(Spell*);
        void sellItem(std::string);
        void sellSpell(std::string);

        void checkInventory();
        void equip(Armor*);
        void equip(Weapon*);
        void use(Potion*);
        void castSpell(Monster*);

        void incrMoney(double);
        void decrMoney(double);
        void incrExp(double);
        void incrMagic(double);
        void incrStrength(double);
        void addItem(Item*);
        void addItem(Spell*);
        bool potionExist();

        int getszI() const;
        int getszS() const;
};

/* ================================ Hero Subclasses ================================= */

class Warrior : public Hero{
    public:
        Warrior(std::string nam, int L, double H, double mgP, double str, double dex, double ag, double mon, double exp);
        ~Warrior();
};

class Sorcerer : public Hero{
    public:
        Sorcerer(std::string nam, int L, double H, double mgP, double str, double dex, double ag, double mon, double exp);
        ~Sorcerer();
};

class Paladin : public Hero{
    public:
        Paladin(std::string nam, int L, double H, double mgP, double str, double dex, double ag, double mon, double exp);
        ~Paladin();
};

/* ============================== Monster Subclasses ================================= */

class Dragon : public Monster{
    public:
        Dragon(std::string, int, double, double, double, double);
        ~Dragon();
};

class Exoskeleton : public Monster{
    public:
        Exoskeleton(std::string, int, double, double, double, double);
        ~Exoskeleton();
};

class Spirit : public Monster{
    public:
        Spirit(std::string nam, int L, double H, double dmg, double arm, double msP);
        ~Spirit();
};


extern std::map<std::string, Weapon*> allWeapons;
extern std::map<std::string, Armor*> allArmors;
extern std::map<std::string, Potion*> allPotions;
extern std::map<std::string, IceSpell*> allIceSpells;
extern std::map<std::string, FireSpell*> allFireSpells;
extern std::map<std::string, LightningSpell*> allLightningSpells;

/* =================================== End of file =================================== */
