#include "entity.h"
#include "skill.h"
Entity::Entity(){
    hp = 0;
    mp = 0;
    atk = 0;
    hp_max = hp;
    mp_max = mp;
}

Entity::Entity(int _hp,int _mp,int _atk){
    hp = _hp;
    mp = _mp;
    hp_max = hp;
    mp_max = mp;
    atk = _atk;
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
    }
    else{
        return false;
    }
    return true;
}

Dragon::Dragon() : Entity(){}
Dragon::Dragon(int _hp,int _mp,int _atk) : Entity(_hp,_mp,_atk){}
