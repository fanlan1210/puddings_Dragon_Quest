#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "skill.h"
using std::string;
class Entity{
public:
    Entity();
    Entity(int,int,int);
    void setHpMax(int);
    int getHpMax();
    void setHp(int);
    void adjHp(int);
    int getHp();
    void setMpMax(int);
    int getMpMax();
    void setMp(int);
    void adjMp(int);
    int getMp();
    void setAtk(int);
    int getAtk();
    double getDamageRate();
    string getName();
    void naming(string);
private:
    int hp;
    int hp_max;
    int mp;
    int mp_max;
    int atk;
    double damage_rate;
    string name;
};

class Hero : public Entity,public Skill{
public:
    Hero();
    Hero(int,int,int,int = 0);
    int getAp();
    void setAp(int);
    void adjAp(int);
    bool attack(string cmd,Entity &target);
private:
    int ap;
};

class Dragon : public Entity,public Skill{
public:
    Dragon();
    Dragon(int,int,int);
    void attack(Entity &target);
private:
    ;
};
#endif
