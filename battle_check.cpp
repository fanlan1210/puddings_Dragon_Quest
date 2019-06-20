#include <iostream>
#include <thread>
#include <chrono>

#include "battle_check.h"
#include "render.h"
#include "misc.h"

using namespace std;

void dragon_death_check(int hp){
	if(hp<=0)
    {
        this_thread::sleep_for(chrono::milliseconds(700));
        cout<<endl<<red_text("勇者擊敗了惡龍!");
        this_thread::sleep_for(chrono::milliseconds(300));
        cout<<endl;
        pause();
        exit(0);
    }
}

void gain_hp_check(int* gain_hp,int* hp,int* max_hp){
	*hp += *gain_hp;
	if(*hp > *max_hp)
	{
		*gain_hp += *max_hp-*hp;
		*hp = *max_hp;
	}
}

void def_check(int* shielding,bool* defend,int* damage){
    if(*shielding==0&&*defend==true)
    {
        cout<<"勇者防禦住了 "<<int(*damage*0.6)<<" 點傷害"<<endl<<endl;
        *damage=*damage*0.4;
        *defend=false;
    }
    else if(*shielding>0&&*defend==false)
    {
        cout<<"(護盾吸收了 "<<*damage<<" 點傷害)"<<endl;
        *damage=0;
    }
    else if(*shielding>0&&*defend==true)
    {
        cout<<"勇者防禦住了 0 點傷害"<<endl<<endl;
        *defend=false;
        cout<<"(護盾吸收了 "<<*damage<<" 點傷害)"<<endl;
        *damage=0;
    }
}

void dragon_shield_check(int* shield,int* damage){
	*shield -= *damage;
	if(*shield<0){
		cout<<"(龍盾吸收了 "<<*shield + *damage<<" 點傷害)"<<endl;
		*damage = -*shield;
		*shield=0;
	}
	else {
		cout<<"(龍盾吸收了 "<<*damage<<" 點傷害)"<<endl;
		*damage=0;
	}
}

int reflect_damage(int* reflect,int damage)
{
    if(*reflect==2)
    {
        damage *= 0.4;
        cout<<endl<<"勇者受到 "<<damage<<" 點反彈傷害"<<endl;
        return damage;
    }
    else
    {
        damage *= 0.4*2;
        cout<<endl<<"勇者受到 "<<damage<<" 點反彈傷害"<<endl;
        return damage;
    }
}
