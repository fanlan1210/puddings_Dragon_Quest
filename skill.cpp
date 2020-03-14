#include "skill.h"
#include <random>

std::random_device rand_dev;
std::default_random_engine gen_rand(rand_dev());

Skill::Skill(){
    atk_base = 1;
    damage_rate = 1;
}

Skill::Skill(int _atk_base){
    atk_base = _atk_base;
    damage_rate = 1;
}

Skill::Skill(int _atk_base,int _damage_rate){
    atk_base = _atk_base;
    damage_rate = _damage_rate;
}

double Skill::getDamageRate(){
    random_num=gen_rand()%14;
    damage_rate=1;
    if(random_num==0||random_num==1) {damage_rate=0.9;}
    if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
    if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
    if(random_num==8||random_num==9) {damage_rate=1.1;}
    if(random_num==10) {damage_rate=1.8;}
    return damage_rate;
}

int Skill::getDamage(){
    return damage;
}

int Skill::beat(){
  damage = atk_base * getDamageRate();
  return damage;
}
