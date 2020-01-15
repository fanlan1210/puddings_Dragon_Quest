#ifndef ENTITY_H
#define ENTITY_H
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
private:
    int hp;
    int hp_max;
    int mp;
    int mp_max;
    int atk;
    double damage_rate;
};

class Hero : public Entity{
public:
    Hero();
    Hero(int,int,int,int = 0);
    int getAp();
    void setAp(int);
    void adjAp(int);
private:
    int ap;
};

class Dragon : public Entity{
public:
    Dragon();
    Dragon(int,int,int);
private:
    ;
};
#endif
