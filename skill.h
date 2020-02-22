#ifndef SKILL_H
#define SKILL_H

#include <string>

using std::string;

class Skill{
public:
    Skill();
    Skill(int);
    Skill(int,int);
    double getDamageRate();
    int beat();
    int beat_double();
    int defend();
    int fire();
    int freeze();
    int swipe();
    int dizzy();
private:
    string name;
    int damage;
    int atk_base;
    double damage_rate;
    int cost;
};
#endif
