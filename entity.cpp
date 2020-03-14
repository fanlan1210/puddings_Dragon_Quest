#include "entity.h"
#include "skill.h"
#include <iostream>

using std::cout;

Entity::Entity(){
    hp = 0;
    mp = 0;
    atk = 0;
    hp_max = hp;
    mp_max = mp;
    name = "勇者";
}

Entity::Entity(int _hp,int _mp,int _atk){
    hp = _hp;
    mp = _mp;
    hp_max = hp;
    mp_max = mp;
    atk = _atk;
    name = "勇者";
}
int Entity::getHp(){
    return hp;
}
int Entity::getHpMax(){
    return hp_max;
}
int Entity::getMp(){
    return mp;
}
int Entity::getMpMax(){
    return mp_max;
}
int Entity::getAtk(){
    return atk;
}
void Entity::setHp(int _hp){
    hp = _hp;
}
void Entity::setHpMax(int _hp_max){
    hp_max = _hp_max;
}
void Entity::setMp(int _mp){
    mp = _mp;
}
void Entity::setMpMax(int _mp_max){
    mp_max = _mp_max;
}
void Entity::setAtk(int _atk){
    atk = _atk;
}
void Entity::adjHp(int _hp){
    hp += _hp;
}
void Entity::adjMp(int _mp){
    mp += _mp;
}

string Entity::getName(){
    return name;
}

void Entity::naming(string new_name){
    name = new_name;
}

Hero::Hero() : Entity(),Skill(){
    ap = 0;
}
Hero::Hero(int _hp,int _mp,int _atk,int _ap) : Entity(_hp,_mp,_atk),Skill(_atk){
    ap = _ap;
}
void Hero::adjAp(int _ap){
    ap += _ap;
}

bool Hero::attack(string cmd,Entity &target) {
    if (cmd == "+"){
        target.adjHp(-beat());
        cout<<getName()<<"對惡龍造成了 "<<getDamage()<<"點傷害\n";
    }
    else if(cmd == "++"){
        target.adjHp(-beat()/2);
        cout<<getName()<<"對惡龍造成了 "<<getDamage()/2<<"點傷害\n";
        target.adjHp(-beat()/2);
        cout<<getName()<<"對惡龍造成了 "<<getDamage()/2<<"點傷害\n";
    }
    else{
        return false;
    }
    return true;
}

Dragon::Dragon() : Entity(),Skill(){}
Dragon::Dragon(int _hp,int _mp,int _atk) : Entity(_hp,_mp,_atk),Skill(_atk){}

void Dragon::attack(Entity &target){
    target.adjHp(-beat());
}
