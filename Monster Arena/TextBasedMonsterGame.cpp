#include <iostream>
#include <string>
#include <vector>
using namespace std;
enum MonsterType { goblin, troll, orc, max};
class Monster
{
protected:
    int health = 20;
    int damage = 5;
    MonsterType type = MonsterType::max;
public:
        Monster(int in_health, int in_damage)
        { 
            health = in_health;
            damage = in_damage;
        }
        MonsterType getType() {
            return type;
        }
        void setType(MonsterType in_type) {
            type = in_type;
        }
        void showType() {
            switch (type)
            {
            case goblin:
                cout << "Goblin";
                break;
            case troll:
                cout << "Troll";
                break;
            case orc:
                cout << "Orc";
                break;
            default:
                cout << "*****";
                break;
            }
        }
        void setHealth(int in_health) {
            health = in_health;
        }
        void setDamage(int in_damage) {
            damage = in_damage;
        }
        void showHealthAndDamage() {
            cout << "(HP: " << health << " DMG: " << damage << ")";
        }
        void showHealth() {
            cout <<"("<< health<<")";
        }
        int getHealth() {
            return health;
        }
        int getDamage() {
            return damage;
        }
};

class Goblin : public Monster {
    int NumberOfAttacks = 3;
    public:
        Goblin()
        : Monster(13, 5),
        NumberOfAttacks(3){
            setType(goblin);
        }

        Goblin(int in_health, int in_damage, int in_numAttacks) : Monster(in_health, in_damage) {
            NumberOfAttacks = in_numAttacks;
            setType(goblin);
        }
        void ShowAttacksLeft() {
            cout << "Goblin has " << NumberOfAttacks << " attacks remaining" << endl;
        }
        int getAttacksLeft() {
            return NumberOfAttacks;
        }
        void setAttacksLeft(int in_numAttacks) {
            NumberOfAttacks = in_numAttacks;
        }
};

class Troll : public Monster {
    int Regeneration = 5;
public:
    int startingHealth;
    Troll()
    : Monster(20, 6),
    Regeneration(3)
    {
        startingHealth = getHealth();
        setType(troll);
    }

    Troll(int in_health, int in_damage, int in_regen) : Monster(in_health, in_damage) {
        startingHealth = in_health;
        Regeneration = in_regen;
        setType(troll);
    }

    void ShowRegen() {
        cout << "Troll has " << Regeneration << " regen" << endl;
    }

    int getRegen() {
        return Regeneration;
    }

    void regenerate() {
        if (health < startingHealth) {
            setHealth(std::min(health + Regeneration, startingHealth));
        }
    }
};

class Orc : public Monster {
    int AmountBlocked = 2;
    int DamageReflected = 1;
public:
    Orc():
        Monster(9, 5),
        AmountBlocked(4),
        DamageReflected(1){
        setType(orc);
    }
    Orc(int in_health, int in_damage, int in_blocked, int in_reflected) : Monster(in_health, in_damage) {
        AmountBlocked = in_blocked;
        DamageReflected = in_reflected;
        setType(orc);
    }
    void ShowBlockAndReflect() {
        cout << "Orc can block for " << AmountBlocked << " and reflect " << DamageReflected << " damage" << endl;
    }
    int getBlock() {
        return AmountBlocked;
    }
    int getDamageReflected() {
        return DamageReflected;
    }
};
void showTeamComposition(vector<Monster*>& RedMonsters, vector<Monster*>& BlueMonsters) {

    cout << "[ Red | ";
    for (int i = 0; i < RedMonsters.size(); ++i) {
        RedMonsters[i]->showType();
        RedMonsters[i]->showHealth();
        if (i < RedMonsters.size() - 1) {
            cout << ", "; 
        }
        
    }
    cout << " ] ... [ ";
    for (int i = BlueMonsters.size() - 1; i >= 0; --i) {
        BlueMonsters[i]->showType();
        BlueMonsters[i]->showHealth();
        if (i > 0) {
            cout << ", ";
        }
    }

    cout << " | Blue ]" << endl;
}
void doBattle(vector<Monster*>& RedMonsters, vector<Monster*>& BlueMonsters, int &battleNum) {
    Monster* redMonsterPtr;
    Goblin* redGoblinPtr;
    Troll* redTrollPtr;
    Orc* redOrcPtr;
    Monster* blueMonsterPtr;
    Goblin* blueGoblinPtr;
    Troll* blueTrollPtr;
    Orc* blueOrcPtr;
    int turn = 1;

    cout << endl << "Battle " << battleNum << " starting... " << endl;
    showTeamComposition(RedMonsters, BlueMonsters);
    //battle commences as long as one of the arrays have monsters in them
    while (!RedMonsters.empty() && !BlueMonsters.empty() && (turn < 100)) {
        // check the last element of each array these are the monsters that have to fight each other
        // use back function for vector or something similar use !empty check again
        //attack enemy monster if health is above zero
        // need to create separate pointers for blue monsters instead of reusing
        // need to delete the ptr that is about to get popped 
        redMonsterPtr = RedMonsters.back();
        blueMonsterPtr = BlueMonsters.back();
        cout << endl << "Turn " << turn << endl << endl;
        showTeamComposition(RedMonsters, BlueMonsters);

        //red logic
        switch (redMonsterPtr->getType())
        {
        case goblin:
        {
            redGoblinPtr = static_cast<Goblin*> (redMonsterPtr);
            int attacks = redGoblinPtr->getAttacksLeft();
            while (attacks > 0) {
                if (blueMonsterPtr->getType() == orc) {
                    blueOrcPtr = static_cast<Orc*> (blueMonsterPtr);
                    blueOrcPtr->setHealth(blueOrcPtr->getHealth() + blueOrcPtr->getBlock() - redGoblinPtr->getDamage());
                    cout << "Red Goblin attacks Blue ";
                    blueMonsterPtr->showType();
                    cout << " for " << redGoblinPtr->getDamage() << " damage" << endl;
                    cout << "Blue Orc blocks for " << blueOrcPtr->getBlock() << " damage" << endl;
                    redGoblinPtr->setHealth(redGoblinPtr->getHealth() - blueOrcPtr->getDamageReflected());
                    cout << "Blue Orc reflected back " << blueOrcPtr->getDamageReflected() << " damage" << endl;
                }
                else {
                    blueMonsterPtr->setHealth(blueMonsterPtr->getHealth() - redGoblinPtr->getDamage());
                    cout << "Red Goblin attacks Blue ";
                    blueMonsterPtr->showType();
                    cout << " for " << redGoblinPtr->getDamage() << " damage" << endl;
                }
                attacks--;
            }
            break;
        }
        case troll:
            redTrollPtr = static_cast<Troll*> (redMonsterPtr);
            if (blueMonsterPtr->getType() == orc) {
                blueOrcPtr = static_cast<Orc*> (blueMonsterPtr);
                blueOrcPtr->setHealth(blueOrcPtr->getHealth() + blueOrcPtr->getBlock() - redTrollPtr->getDamage());
                cout << "Red Troll attacks Blue ";
                blueMonsterPtr->showType();
                cout << " for " << redTrollPtr->getDamage() << " damage" << endl;
                cout << "Blue Orc blocks for " << blueOrcPtr->getBlock() << " damage" << endl;
                redTrollPtr->setHealth(redTrollPtr->getHealth() - blueOrcPtr->getDamageReflected());
                cout << "Blue Orc reflected back " << blueOrcPtr->getDamageReflected() << " damage" << endl;
            }
            else {
                blueMonsterPtr->setHealth(blueMonsterPtr->getHealth() - redTrollPtr->getDamage());
                cout << "Red Troll attacks Blue ";
                blueMonsterPtr->showType();
                cout << " for " << redTrollPtr->getDamage() << " damage" << endl;
            }
            break;
        case orc:
            redOrcPtr = static_cast<Orc*> (redMonsterPtr);
            if (blueMonsterPtr->getType() == orc) {
                blueOrcPtr = static_cast<Orc*> (blueMonsterPtr);
                blueOrcPtr->setHealth(blueOrcPtr->getHealth() + blueOrcPtr->getBlock() - redOrcPtr->getDamage());
                cout << "Red Orc attacks Blue ";
                blueMonsterPtr->showType();
                cout << " for " << redOrcPtr->getDamage() << " damage" << endl;
                cout << "Blue Orc blocks for " << blueOrcPtr->getBlock() << " damage" << endl;
                redOrcPtr->setHealth(redOrcPtr->getHealth() - blueOrcPtr->getDamageReflected());
                cout << "Blue Orc reflected back " << blueOrcPtr->getDamageReflected() << " damage" << endl;
            }
            else {
                blueMonsterPtr->setHealth(blueMonsterPtr->getHealth() - redOrcPtr->getDamage());
                cout << "Red Orc attacks Blue ";
                blueMonsterPtr->showType();
                cout << " for " << redOrcPtr->getDamage() << " damage" << endl;
            }
            break;
        default:
            break;
        }

        //blue logic
        switch (blueMonsterPtr->getType())
        {
        case goblin:
        {
            blueGoblinPtr = static_cast<Goblin*> (blueMonsterPtr);
            int attacks = blueGoblinPtr->getAttacksLeft();
            while (attacks > 0) {
                if (redMonsterPtr->getType() == orc) {
                    redOrcPtr = static_cast<Orc*> (redMonsterPtr);
                    redOrcPtr->setHealth(redOrcPtr->getHealth() + redOrcPtr->getBlock() - blueGoblinPtr->getDamage());
                    cout << "Blue Goblin attacks Red ";
                    redMonsterPtr->showType();
                    cout << " for " << blueGoblinPtr->getDamage() << " damage" << endl;
                    cout << "Red Orc blocks for " << redOrcPtr->getBlock() << " damage" << endl;
                    blueGoblinPtr->setHealth(blueGoblinPtr->getHealth() - redOrcPtr->getDamageReflected());
                    cout << "Red Orc reflected back " << redOrcPtr->getDamageReflected() << " damage" << endl;
                }
                else {
                    redMonsterPtr->setHealth(redMonsterPtr->getHealth() - blueGoblinPtr->getDamage());
                    cout << "Blue Goblin attacks Red ";
                    redMonsterPtr->showType();
                    cout << " for " << blueGoblinPtr->getDamage() << " damage" << endl;
                }
                attacks--;
            }
            break;
        }
        case troll:
            blueTrollPtr = static_cast<Troll*> (blueMonsterPtr);
            if (redMonsterPtr->getType() == orc) {
                redOrcPtr = static_cast<Orc*> (redMonsterPtr);
                redOrcPtr->setHealth(redOrcPtr->getHealth() + redOrcPtr->getBlock() - blueTrollPtr->getDamage());
                cout << "Blue Troll attacks Red ";
                redMonsterPtr->showType();
                cout << " for " << blueTrollPtr->getDamage() << " damage" << endl;
                cout << "Red Orc blocks for " << redOrcPtr->getBlock() << " damage" << endl;
                blueTrollPtr->setHealth(blueTrollPtr->getHealth() - redOrcPtr->getDamageReflected());
                cout << "Red Orc reflected back " << redOrcPtr->getDamageReflected() << " damage" << endl;
            }
            else {
                redMonsterPtr->setHealth(redMonsterPtr->getHealth() - blueTrollPtr->getDamage());
                cout << "Blue Troll attacks Red ";
                redMonsterPtr->showType();
                cout << " for " << blueTrollPtr->getDamage() << " damage" << endl;
            }
            break;
        case orc:
            blueOrcPtr = static_cast<Orc*> (blueMonsterPtr);
            if (redMonsterPtr->getType() == orc) {
                redOrcPtr = static_cast<Orc*> (redMonsterPtr);
                redOrcPtr->setHealth(redOrcPtr->getHealth() + redOrcPtr->getBlock() - blueOrcPtr->getDamage());
                cout << "Blue Orc attacks Red ";
                redMonsterPtr->showType();
                cout << " for " << blueOrcPtr->getDamage() << " damage" << endl;
                cout << "Red Orc blocks for " << redOrcPtr->getBlock() << " damage" << endl;
                blueOrcPtr->setHealth(blueOrcPtr->getHealth() - redOrcPtr->getDamageReflected());
                cout << "Red Orc reflected back " << redOrcPtr->getDamageReflected() << " damage" << endl;
            }
            else {
                redMonsterPtr->setHealth(redMonsterPtr->getHealth() - blueOrcPtr->getDamage());
                cout << "Blue Orc attacks Red ";
                redMonsterPtr->showType();
                cout << " for " << blueOrcPtr->getDamage() << " damage" << endl;
            }
            break;
        default:
            break;
        }
        if (redMonsterPtr->getHealth() <= 0) {
            cout << "Red ";
            redMonsterPtr->showType();
            cout << " dies " << endl;
            delete RedMonsters.back();
            RedMonsters.pop_back();
        }
        else if (redMonsterPtr->getType() == troll && redMonsterPtr->getHealth() > 0) {
            redTrollPtr = static_cast<Troll*>(redMonsterPtr);
            redTrollPtr->regenerate();
            cout << "Red troll regenerates " << redTrollPtr->getRegen() << " health" << endl;
        }
        if (blueMonsterPtr->getHealth() <= 0) {
            cout << "Blue ";
            blueMonsterPtr->showType();
            cout << " dies " << endl;
            delete BlueMonsters.back();
            BlueMonsters.pop_back();
        }
        else if (blueMonsterPtr->getType() == troll && blueMonsterPtr->getHealth() > 0) {
            blueTrollPtr = static_cast<Troll*>(blueMonsterPtr);
            blueTrollPtr->regenerate();
            cout << "Blue troll regenerates " << blueTrollPtr->getRegen() << " health" << endl;
        }
        cout << "Red team has " << RedMonsters.size() << " monster(s) left " << endl;
        cout << "Blue team has " << BlueMonsters.size() << " monster(s) left " << endl;
        turn++;
    }
    if (RedMonsters.empty() && BlueMonsters.empty()) {
        cout << "Battle over. It's a tie!!" << endl;
    }
    else if (RedMonsters.empty()) {
        cout << "Battle over. Blue team wins!" << endl;
    }
    else if (BlueMonsters.empty()) {
        cout << "Battle over. Red team wins!" << endl;
    }
    showTeamComposition(RedMonsters, BlueMonsters);
    battleNum++;
}
void cleanupTeams(vector<Monster*>& RedMonsters, vector<Monster*>& BlueMonsters) {
    //delete heap stuff
    for (int i = 0; i < RedMonsters.size(); ++i) {
        delete RedMonsters[i];
    }
    for (int i = 0; i < BlueMonsters.size(); ++i) {
        delete BlueMonsters[i];
    }
    RedMonsters.clear();
    BlueMonsters.clear();
}

int main()
{

    vector<Monster*> RedMonsters = { new Goblin()};
    vector<Monster*> BlueMonsters = { new Troll()};
    int battleNumber = 1;
    doBattle(RedMonsters, BlueMonsters, battleNumber);
    cleanupTeams(RedMonsters, BlueMonsters);

    RedMonsters = { new Goblin() };
    BlueMonsters = { new Troll(), new Troll() };
    doBattle(RedMonsters, BlueMonsters, battleNumber);
    cleanupTeams(RedMonsters, BlueMonsters);

    RedMonsters = { new Troll()};
    BlueMonsters = { new Orc()};
    doBattle(RedMonsters, BlueMonsters, battleNumber);
    cleanupTeams(RedMonsters, BlueMonsters);

    RedMonsters = { new Troll()};
    BlueMonsters = { new Orc(), new Orc() };
    doBattle(RedMonsters, BlueMonsters, battleNumber);
    cleanupTeams(RedMonsters, BlueMonsters);

    RedMonsters = { new Orc()};
    BlueMonsters = { new Goblin()};
    doBattle(RedMonsters, BlueMonsters, battleNumber);
    cleanupTeams(RedMonsters, BlueMonsters);

    RedMonsters = { new Orc() };
    BlueMonsters = { new Goblin(), new Goblin()};
    doBattle(RedMonsters, BlueMonsters, battleNumber);
    cleanupTeams(RedMonsters, BlueMonsters);

    srand(time(NULL));
    int randIndex = rand() % (int)MonsterType::max;
    //4 random monsters pushed into team red
    for (int i = 0; i < 4; ++i) {
        randIndex = rand() % (int)MonsterType::max;
        switch (randIndex)
        {
        case 0:
            RedMonsters.push_back(new Goblin());
            break;
        case 1:
            RedMonsters.push_back(new Troll());
            break;
        case 2:
            RedMonsters.push_back(new Orc());
            break;
        default:
            break;
        }
    }

    //4 random monsters pushed into team blue
    for (int i = 0; i < 4; ++i) {
        randIndex = rand() % (int)MonsterType::max;
        switch (randIndex)
        {
        case 0:
            BlueMonsters.push_back(new Goblin());
            break;
        case 1:
            BlueMonsters.push_back(new Troll());
            break;
        case 2:
            BlueMonsters.push_back(new Orc());
            break;
        default:
            break;
        }
    }
    doBattle(RedMonsters, BlueMonsters, battleNumber);
    cleanupTeams(RedMonsters, BlueMonsters);

}