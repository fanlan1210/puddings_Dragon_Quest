#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
#include <map>

/* load custom headers */
#include "render.h"
#include "battle_check.h"
#include "misc.h"
#include "entity.h"

using namespace std;
//版本資訊
inline string version(){return "Beta 6.99.1_DEV";}

void pause();

struct entity{
	int maxhp=0;
	int hp=0;
	int atk=0;
	int ap=0;
};

int main(int argc, char *argv[])
{
	/* 初始化 */
	entity hero,dragon;
	Hero player;
	Dragon enemy;

	/*Entity test(100,0,1);
	cout<<test.getHp()<<'\n';
	test.setAtk(5);
	cout<<test.getAtk()<<'\n';*/

	//勇者數值
	int /*dragon_hp,dragon_atk,dragon_maxhp,*/dragon_shield=0; //惡龍數值
	int round,random_num,damage,gain_hp,lost_hp; // 計算用數值

	//勇者技能開關
	bool pow=false;
	map<string,bool> skillSwitch;
	skillSwitch["defend"]=false;
	skillSwitch["freeze"]=true;
	skillSwitch["fire"]=true;
	skillSwitch["swipe"]=true;
	skillSwitch["dizzy"]=true;
	skillSwitch["blood"]=true;
	skillSwitch["shield"]=true;
	skillSwitch["cure"]=true;
	skillSwitch["treat"]=true;
		//pow=false

	//Cool Down
	map<string,pair<int,int>> mapCooldown; // CD pair : current,max
	mapCooldown["freeze"] = {0,18};
	mapCooldown["fire"] = {0,9};
	mapCooldown["swipe"] = {0,5};
	mapCooldown["dizzy"] = {0,13};
	mapCooldown["blood"] = {0,27};
	mapCooldown["shield"] = {0,16};
	mapCooldown["cure"] = {0,20};
	mapCooldown["treat"] = {0,14};
	map<string,pair<int,int>>::iterator it;

	/*int dizzied=0,burned=0,frozen=0,curing=0,dizzing=0,sapping=0,explosion=0,stand=0;*/ // 惡龍持續狀態
	map<string,pair<int,int>> dragonStatus = {
		//{ "dizzied",{,0} },
		{ "burned",{0,5} },
		{ "frozen",{0,2} },
		{ "dizzing",{0,4} },
		{ "sapping",{0,3} },
		{ "explosion",{0,3} },
		{ "stand",{0,1} }
	};

    /*int weaken=0,reflect=0,poison=0,shielding=0;*/ // 勇者持續狀態
	map<string,pair<int,int>> heroStatus = {
		{ "weaken",{0,3} },
		{ "reflect",{0,2} },
		{ "poison",{0,5} },
		{ "treating",{0,3} },
		{ "shielding",{0,3} }
	};

	double damage_rate;
	string action,yn;
	string effect;
	/* 隨機亂數初始化 */
	random_device rand_dev;
	default_random_engine gen_rand(rand_dev());

	custom_background(true);
	cout<<white_text(" ---------------")<<endl;
	cout<<white_text("|★☆★☆★☆★☆|")<<endl;
	cout<<white_text("|勇者鬥惡龍|")<<endl;
	cout<<white_text("|☆★☆★☆★☆★|")<<endl;
	cout<<white_text(" ---------------")<<endl;
	cout<<version()<<endl<<endl;
	int choice;
	cout<<"請選擇遊戲難度(1:新手 || 2:普通 || 3:困難 || 4:夢魘)"<<endl;
	cin>>choice;
	if (choice == 0){
		cout<<yellow_text("[DEBUG]選擇為自訂難度")<<endl;
		cout<<white_text("勇者最大血量: ");
		cin>>hero.hp;
		player.setHp(hero.hp);
		player.setHpMax(hero.hp);

		cout<<endl<<white_text("勇者基礎攻擊力: ");
		cin>>hero.atk;
		player.setAtk(hero.atk);

		cout<<endl<<white_text("惡龍最大血量: ");
		cin>>dragon.hp;
		enemy.setHp(dragon.hp);
		enemy.setHpMax(dragon.hp);

		cout<<endl<<white_text("惡龍基礎攻擊力: ");
		cin>>dragon.atk;
		enemy.setAtk(dragon.atk);
	}
	else if(choice == 1){
		cout<<yellow_text("選擇為新手難度")<<endl;
		hero.hp = 4000;
		hero.atk = 600;
		// hp,mp,atk
		player = Hero(4000,2000,600);
		dragon.hp = 4000;
		dragon.atk = 200;
		enemy = Dragon(4000,4000,200);
	}
	else if(choice == 2){
		cout<<yellow_text("選擇為普通難度")<<endl;
		hero.hp = 3500;
		hero.atk = 500;
		player = Hero(3500,1500,500);
		dragon.hp = 8000;
		dragon.atk = 250;
		enemy = Dragon(8000,8000,250);
	}
	else if(choice == 3){
		cout<<yellow_text("選擇為困難難度")<<endl;
		hero.hp = 3000;
		hero.atk = 500;
		player = Hero(3000,1000,500);
		dragon.hp = 10000;
		dragon.atk = 300;
		enemy = Dragon(10000,10000,300);
	}
	else if(choice == 4){
		cout<<yellow_text("選擇為夢魘難度")<<endl;
		hero.hp = 2500;
		hero.atk = 400;
		player = Hero(2500,500,400);
		dragon.hp = 12000;
		dragon.atk = 300;
		enemy = Dragon(12000,10000,300);
	}
	else{
		cerr<<"輸入錯誤，程式強制終止!"<<endl;
		return 1;
	}
	cout<<"------------------------------------------------------------"<<endl;
	hero.maxhp = hero.hp;
	dragon.maxhp = dragon.hp;
	while(true)
	{
		cout<<endl<<"是否需要遊戲說明及技能介紹? | [y]es / [n]o |"<<endl<<endl;
		cin>>yn;
		if(yn=="yes" || yn == "y")
		{
			help();
			break;
		}
		else if(yn=="no" || yn == "n")
			break;
		else
			continue;
	}
	for(round=1;round>0;round++)
	{
		cout<<endl<<white_text("------------------------------------------------------------")<<endl;
		/* 使用者介面 */
	   	cout<<"第 "<<round<<" 回合:"<<endl;
		if(hero.ap>=10&&pow==false)
		{
			pow=true;
		}
		cout<<"攻擊: | +  atk|| ++  double atk|| -  defend|"<<endl;
		cout<<"技能: "<<endl;
        cout<<white_text("| 1  ")<<left<<setw(21)<<custom_text("freeze",45)
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["freeze"].first
			<<white_text("/"+to_string(mapCooldown["freeze"].second)+" |");

		cout<<white_text("| 2  ")<<left<<setw(22)<<custom_text("fire",202)
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["fire"].first
			<<white_text("/ "+to_string(mapCooldown["fire"].second)+" |");

		cout<<white_text("| 3  ")<<left<<setw(21)<<yellow_text("swipe")
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["swipe"].first
			<<white_text("/ "+to_string(mapCooldown["swipe"].second)+" |");

		cout<<endl;

		cout<<white_text("| 4  ")<<left<<setw(21)<<yellow_text("dizzy")
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["dizzy"].first
			<<white_text("/"+to_string(mapCooldown["dizzy"].second)+" |");

		cout<<white_text("| 5  ")<<left<<setw(21)<<dark_red_text("blood")
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["blood"].first
			<<white_text("/"+to_string(mapCooldown["blood"].second)+" |");

		cout<<white_text("| 6  ")<<left<<setw(21)<<blue_text("shield")
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["shield"].first
			<<white_text("/"+to_string(mapCooldown["shield"].second)+" |");

		cout<<endl;

		cout<<white_text("| 7  ")<<left<<setw(21)<<custom_text("cure",40)
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["cure"].first
			<<white_text("/"+to_string(mapCooldown["cure"].second)+" |");

		cout<<white_text("| 8  ")<<left<<setw(21)<<custom_text("treat",34)
			<<white_text(" CD: ")<<right<<setw(2)
			<<mapCooldown["treat"].first
			<<white_text("/"+to_string(mapCooldown["treat"].second)+" |");

		if (hero.ap<10){
		cout<<yellow_text("| !  ")<<left<<setw(21)<<yellow_text("pow")<<white_text(" AP: ")<<left<<setw(2)<<hero.ap<<white_text("(10)|");
		}else{
		cout<<yellow_text("| !  ")<<left<<setw(30)<<blink_text(yellow_text("pow"))<<white_text(" AP: ")<<left<<setw(2)<<hero.ap<<white_text("(10)|");
		}
		cout<<endl<<endl;

		/*cout<<white_text("勇者血量:")<<red_text(to_string(hero.hp))<<white_text("/"+to_string(hero.maxhp))
			<<white_text("  惡龍血量:")<<red_text(to_string(dragon.hp))<<white_text("/"+to_string(dragon.maxhp));
		if(dragonStatus["explosion"].first>0) cout <<"("<< custom_text("+"+to_string(dragon_shield),128)<<"/"<<custom_text(to_string(dragonStatus["explosion"].first),92)<<")";
		cout<<endl;*/

		// temporary set
		//player.setHp(hero.hp);
		//enemy.setHp(dragon.hp);
		//player.attack("+",enemy);

		cout<<white_text("勇者血量:")<<red_text(to_string(player.getHp()))<<white_text("/"+to_string(player.getHpMax()))
			<<white_text("  惡龍血量:")<<red_text(to_string(enemy.getHp()))<<white_text("/"+to_string(enemy.getHpMax()));
		if(dragonStatus["explosion"].first>0) cout <<"("<< custom_text("+"+to_string(dragon_shield),128)<<"/"<<custom_text(to_string(dragonStatus["explosion"].first),92)<<")";
		cout<<endl;

		bool haveEffect=false;
		cout<<white_text("勇者附加狀態: ");
		for(it=heroStatus.begin();it!=heroStatus.end();it++){
			if( (it->second).first != 0){
				cout<<(it->first)<<" ";
				haveEffect = true;
			}
		}
		if(!haveEffect) cout<<"(None)";
		cout<<endl;

		haveEffect=false;
		cout<<white_text("惡龍附加狀態: ");
		//cout<<"(Working In Progress)";
		for(it=dragonStatus.begin();it!=dragonStatus.end();it++){
			if( (it->second).first != 0){
				cout<<(it->first)<<" ";
				haveEffect=true;
			}
		}
		if(!haveEffect) cout<<"(None)";

		cout<<endl<<endl;
		// 各項技能CD判斷
		for(it=mapCooldown.begin();it!=mapCooldown.end();it++){
			//cout<<it->first<<" current:"<<(it->second).first<<" max:"<<(it->second).second<<endl;
			if((it->second).first == 0)
				skillSwitch[it->first] = true;
			else if( (it->second).first <= (it->second).second ){
				if( (it->second).first == (it->second).second )
					skillSwitch[it->first] = false;
				(it->second).first--;
			}
		}

		// 隨機傷害倍率
		random_num=gen_rand()%14;
		damage_rate=1;
		action="";
		if(random_num==0||random_num==1) {damage_rate=0.9;}
        if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
        if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
        if(random_num==8||random_num==9) {damage_rate=1.1;}
        if(random_num==10) {damage_rate=1.8;}
		damage=hero.atk*damage_rate; //計算勇者造成傷害
		//if(heroStatus["weaken"].first>0) {damage*=0.7;} //判斷勇者攻擊是否有被弱化
		while(true) //使用者輸入指令與判斷
		{
		    cout << white_text(">>> ");
		    cin>>action;
			cout<<endl;

			if(!player.attack(action,enemy))
			{
				cout<<italic_text("你輸入的文字並未屬於任何一項行動或暫不可用")<<endl<<endl;
				continue;
			}else{
				dragon_death_check(enemy.getHp());
				break;
			}
			/*
			if(action=="+")
			{
				this_thread::sleep_for(chrono::milliseconds(600));
				if(dragonStatus["explosion"].first>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 "+to_string(damage)+" 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)"<<endl;
		    	cout<<endl;
	   			dragon.hp=dragon.hp-damage;
	   			if(heroStatus["reflect"].first>0){ hero.hp -= reflect_damage(&heroStatus["reflect"].first,damage);} //判斷惡龍是否使用反彈
				dragon_death_check(dragon.hp);
	   			break;
			}
			else if(action=="++")
			{
				this_thread::sleep_for(chrono::milliseconds(300));
				damage/=2;
				if(dragonStatus["explosion"].first>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 " + to_string(damage) + " 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl;
	   			dragon.hp=dragon.hp-(damage/2);
	   			if(heroStatus["reflect"].first>0){ hero.hp -= reflect_damage(&heroStatus["reflect"].first,damage);}
	   			 //計算第二次勇者攻擊傷害值
				random_num=gen_rand()%14;
				damage_rate=1;
				this_thread::sleep_for(chrono::milliseconds(300));
				if(random_num==0||random_num==1) {damage_rate=0.9;}
				if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
				if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
				if(random_num==8||random_num==9) {damage_rate=1.1;}
				if(random_num==10) {damage_rate=1.8;}
				damage=hero.atk*damage_rate;
				if(heroStatus["weaken"].first>0) {damage*=0.7;}
				damage/=2;
				if(dragonStatus["explosion"].first>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 " + to_string(damage) + " 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl<<endl;
	   			dragon.hp=dragon.hp-(damage/2);
                if(heroStatus["reflect"].first>0){ hero.hp -= reflect_damage(&heroStatus["reflect"].first,damage);}
				dragon_death_check(dragon.hp);
	   			break;
			}
			else if(action=="-")
			{
				this_thread::sleep_for(chrono::milliseconds(600));
				cout<<"(防禦)"<<endl<<endl;
				skillSwitch["defend"]=true;
				break;
			}
			else if(skillSwitch["freeze"] == true&& ( action=="1" || action == "freeze") )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["freeze"].first = mapCooldown["freeze"].second;
				dragonStatus["frozen"].first=dragonStatus["frozen"].second;
				cout<<yellow_text("勇者使用了") + cyan_text("freeze(冰凍)")<<endl;
				break;
			}
			else if(skillSwitch["fire"] == true&& ( action=="2" || action == "fire" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["fire"].first = mapCooldown["fire"].second;
				cout<<yellow_text("勇者使用了") + red_text("fire(燃燒)")<<endl;
	   			dragonStatus["burned"].first=dragonStatus["burned"].second;
	   			break;
			}
			else if(skillSwitch["swipe"] == true&& ( action=="3" || action == "swipe" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["swipe"].first = mapCooldown["swipe"].second;
	   			cout<<yellow_text("\a勇者使用了swipe(重擊)")<<endl<<endl;
				damage=hero.atk*3;
				if(dragonStatus["explosion"].first>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<"勇者對惡龍造成了 "<<damage<<" 點傷害"<<endl;
	    		dragon.hp=dragon.hp-damage;

				dragon_death_check(dragon.hp);
	    		break;
			}
			else if(skillSwitch["dizzy"] == true&&( action=="4" || action == "dizzy" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["dizzy"].first = mapCooldown["dizzy"].second;
	   			cout<<yellow_text("勇者使用了dizzy(暈眩)")<<endl;
	   			dragonStatus["dizzing"].first=dragonStatus["dizzing"].second;
	   			break;
			}
			else if(skillSwitch["blood"] == true&&( action=="5" || action == "blood" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["blood"].first = mapCooldown["blood"].second;
	   			cout<<yellow_text("勇者使用了") + dark_red_text("blood(吸血)")<<endl;
	   			dragonStatus["sapping"].first = dragonStatus["sapping"].second;
	   			break;
			}
			else if(skillSwitch["shield"] == true&&( action=="6" || action == "shield" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["shield"].first = mapCooldown["shield"].second;
	   			cout<<yellow_text("勇者使用了shield(護盾)")<<endl;
	   			heroStatus["shielding"].first = heroStatus["shielding"].second;
	   			break;
			}
			else if(skillSwitch["cure"] == true&&( action=="7" || action == "cure" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["cure"].first = mapCooldown["cure"].second;
				cout<<yellow_text("勇者使用了") +red_text("cure(治癒)")<<endl;
				gain_hp=hero.maxhp*0.4;
				cout<<endl;
				gain_hp_check(&gain_hp,&hero.hp,&hero.maxhp);
				cout<<"勇者回復了 "<<gain_hp<<" 點生命"<<endl;
				break;
			}
			else if(skillSwitch["treat"] == true&&(action=="8"|| action == "treat"))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				mapCooldown["treat"].first = mapCooldown["treat"].second;
				cout<<yellow_text("勇者使用了") + red_text("treat(回復)")<<endl;
				heroStatus["treating"].first=heroStatus["treating"].second;
				break;
			}
			else if(pow==true&& (action=="!"|| action == "pow"))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				pow=false;
				cout<<yellow_text("勇者使用了pow(必殺技)")<<endl;
				cout<<bold_text("!!!!!!!!!!!!!!!!!!!!!")<<endl;
				cout<<"\a\a\a\a\a\a\a\a\a\a";
				this_thread::sleep_for(chrono::milliseconds(800));
				damage=hero.atk*5;
				if(dragonStatus["explosion"].first>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 "+ to_string(damage) +" 點傷害")<<endl;
	    		dragon.hp=dragon.hp-(hero.atk*5);
	    		if(heroStatus["reflect"].first>0){ hero.hp -= reflect_damage(&heroStatus["reflect"].first,hero.atk*5);}
				hero.ap=hero.ap-10;
				this_thread::sleep_for(chrono::milliseconds(1200));
				dragon_death_check(dragon.hp);

				random_num=gen_rand()%10;
				this_thread::sleep_for(chrono::milliseconds(500));
				cout<<endl;
				if ( random_num == 6 ) {
					 dragonStatus["stand"].first = dragonStatus["stand"].second;
					 cout<<"定身成功!"<<endl;
				}
				else { cout<<"定身失敗!"<<endl; }
				break;
			}
			else
            {
				cout<<italic_text("你輸入的文字並未屬於任何一項行動")<<endl<<endl;
				continue;
			}
		*/}
		// if(dragonStatus["burned"].first>0||heroStatus["treating"].first>0||dragonStatus["sapping"].first>0||heroStatus["shielding"].first>0)
		// {
		// 	if(dragonStatus["burned"].first>0)
		// 	{
		// 		lost_hp=hero.atk*0.4;
		// 		this_thread::sleep_for(chrono::milliseconds(900));
		// 		dragon.hp=dragon.hp-lost_hp;
		// 		cout<<endl;
		// 		cout<<italic_text("燃燒對惡龍造成了 "+to_string(lost_hp)+" 點傷害")<<endl;
		// 		//if(reflect>0){ hero.hp -= reflect_damage(&reflect,damage);}
		// 		dragonStatus["burned"].first--;
		// 		dragon_death_check(dragon.hp);
		// 	}
		// 	if(heroStatus["treating"].first>0)
		// 	{
		// 		this_thread::sleep_for(chrono::milliseconds(900));
		// 		gain_hp=(hero.maxhp-hero.hp)*0.2;
		// 		gain_hp_check(&gain_hp,&hero.hp,&hero.maxhp);
		// 		cout<<endl;
		// 		cout<<italic_text("勇者回復了 "+to_string(gain_hp)+" 點血量")<<endl;
		// 		heroStatus["treating"].first--;
		// 	}
		// 	if(dragonStatus["sapping"].first>0)
		// 	{
		// 		this_thread::sleep_for(chrono::milliseconds(900));
		// 		gain_hp=dragon.hp*0.03;
		// 		gain_hp_check(&gain_hp,&hero.hp,&hero.maxhp);
		// 		dragon.hp=dragon.hp-gain_hp;
		// 		cout<<endl;
		// 		cout<<italic_text("勇者將惡龍的 "+to_string(gain_hp)+" 點血量轉換成自己的血量")<<endl;
		// 		dragonStatus["sapping"].first--;
		// 		dragon_death_check(dragon.hp);
		// 	}
		// 	if(heroStatus["shielding"].first>0)
        //         heroStatus["shielding"].first--;
		// 	cout<<endl;
		// }
		// if(dragonStatus["stand"].first==1)
		// {
		// 	dragonStatus["stand"].first = 0;
		// 	continue;
		// }
        // if(heroStatus["weaken"].first>0) heroStatus["weaken"].first--;
        // if(heroStatus["reflect"].first>0) heroStatus["reflect"].first--;
		// if(dragonStatus["explosion"].first>0) dragonStatus["explosion"].first--;
		// random_num=gen_rand()%14;
		// damage_rate=1;
		// if(random_num==0||random_num==1) {damage_rate=0.9;}
        // if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
        // if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
        // if(random_num==8||random_num==9) {damage_rate=1.1;}
        // if(random_num==10) {damage_rate=1.8;}
		// /* 如果惡龍沒有處於冰凍狀態，才繼續惡龍的攻擊判斷 */
		// if(dragonStatus["frozen"].first==0)
		// {
		// 	this_thread::sleep_for(chrono::milliseconds(900));
		//     damage=dragon.atk*damage_rate; //惡龍傷害計算
		//     if(heroStatus["weaken"].first) {damage*=1.1;}
		//    	if(dragonStatus["dizzing"].first>0)
		// 	{
		// 		random_num=0;
		//
		// 		random_num=gen_rand()%5;
		// 		this_thread::sleep_for(chrono::milliseconds(500));
		// 		if(action=="4")
		// 			cout<<endl;
		// 		switch(random_num)
		// 		{
		// 			case 0:
		// 			case 1:
		// 				//dizzied=1;
		// 				damage=-damage;
		// 				cout<<"暈眩成功!"<<endl<<endl;
		// 				break;
		// 			case 2:
		// 			case 3:
		// 			case 4:
		// 				cout<<"暈眩失敗!惡龍仍保持清醒"<<endl<<endl;
		// 				break;
		// 		}
		// 		dragonStatus["dizzing"].first--;
		// 	}
		// 	//if(dizzied==0)
		// 	if(damage>0)
		// 	{
		// 		random_num=gen_rand()%20;
		// 		if(random_num==0||random_num==1||random_num==2||random_num==3){
		// 			cout<<yellow_text("惡龍使出") + magenta_text("龍之吐息")<<"!"<<endl<<endl;
		// 			cout<<"惡龍對勇者造成了 "<<hero.maxhp/8<<" 點傷害"<<endl;
		// 			hero.hp = hero.hp - hero.maxhp / 8;
		// 		}else if(random_num==4||random_num==5 && heroStatus["weaken"].first==0){
		// 			cout<<yellow_text("惡龍使出") + custom_text("弱化",205)<<endl;
		// 			heroStatus["weaken"].first = heroStatus["weaken"].second;
		// 		}else if(random_num==6||random_num==7 && heroStatus["reflect"].first==0){
		// 			cout<<yellow_text("惡龍使出") + cyan_text("反彈")<<endl;
		// 			heroStatus["reflect"].first = heroStatus["reflect"].second;
		// 		}else if(random_num==8||random_num==9 && heroStatus["poison"].first==0){
		// 			cout<<yellow_text("惡龍使出") + green_text("毒氣")<<endl;
		// 			heroStatus["poison"].first = heroStatus["poison"].second;
		// 		}else if(random_num==10||random_num==11){
		// 			cout<<yellow_text("惡龍使出") + green_text("連擊")<<endl<<endl;
		// 			for(int i=0;i<5;i++)
        //             {
        //                 random_num=gen_rand()%14;
        //                 damage_rate=1;
        //                 if(random_num==0||random_num==1) {damage_rate=0.9;}
        //                 if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
        //                 if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
        //                 if(random_num==8||random_num==9) {damage_rate=1.1;}
        //                 if(random_num==10) {damage_rate=1.8;}
        //                 damage=dragon.atk*damage_rate*0.45;
		// 				def_check(&heroStatus["shielding"].first,&skillSwitch["defend"],&damage);
        //                 hero.hp-=damage;
        //                 cout<<white_text("惡龍對勇者造成了 " + to_string(damage) + " 點傷害")<<endl;
        //             }
		// 		}else if(random_num==19 && dragonStatus["explosion"].first==0){
		// 			cout<<yellow_text("惡龍使出") + custom_text("毀滅龍盾",128)<<endl;
		// 			dragon_shield=dragon.maxhp*0.2;
		// 			dragonStatus["explosion"].first = dragonStatus["explosion"].second;
		// 		}
		// 		else{
        //             cout<<white_text("惡龍對勇者造成了 " + to_string(damage) + " 點傷害");
        //             if(damage_rate==1.8)
        //             {
        //                 cout<<"\a(暴擊!)"<<endl;
        //                 hero.ap++;
        //                 cout<<"勇者怒氣值加1"<<endl;
        //             }
        //             cout<<endl;
        //             def_check(&heroStatus["shielding"].first,&skillSwitch["defend"],&damage);
        //             hero.hp=hero.hp-damage;
        //         }
		// 	}
		// 	//else if(dizzied==1)
		// 	else if(damage<0)
		// 	{
		// 		//dizzied--;
		// 		damage=-damage;
		// 		cout<<italic_text("惡龍對自己造成了 "+to_string(damage)+" 點傷害");
		// 	    if(damage_rate==1.8)
		// 	    {
		// 	    	cout<<"\a(暴擊!)"<<endl;
		// 		}
		// 		cout<<endl;
		// 		dragon.hp-=damage;
		// 	}
		// 	if(dragon.hp<0)
		// 		dragon.hp=0;
		// 	dragon_death_check(dragon.hp);
		//     if(hero.hp<0)
		// 		hero.hp=0;
		//     if(hero.hp<=0)
		//     {
		// 		this_thread::sleep_for(chrono::milliseconds(700));
		//     	cout<<endl<<dark_red_text("勇者被惡龍擊敗了!");
		// 		this_thread::sleep_for(chrono::milliseconds(500));
		// 		cout<<endl;
		// 		pause();
		// 		return 0;
		//     }
		//     cout<<endl;
		// }
		// else if(dragonStatus["frozen"].first==1)
		// {
		// 	this_thread::sleep_for(chrono::milliseconds(200));
		// 	cout<<bold_text("惡龍將在下一回合解凍")<<endl<<endl;
		// 	dragonStatus["frozen"].first--;
		// }
		// else
		// {
		// 	this_thread::sleep_for(chrono::milliseconds(200));
		// 	cout<<bold_text("惡龍將在 "+to_string(dragonStatus["frozen"].first)+" 回合後解凍")<<endl<<endl;
		// 	dragonStatus["frozen"].first--;
		// }
		// if(dragonStatus["explosion"].first==0 && dragon_shield>0){
		// 	hero.hp=0;
		// 	cout<<custom_text("勇者被龍盾毀滅了",125)<<endl;
		// 	pause();
		// 	exit(0);
		// }
		// if(heroStatus["poison"].first>0)
        // {
        //     cout<<italic_text("中毒對勇者造成了 "+to_string( (int)(dragon.atk*0.3) )+" 點傷害")<<endl;
        //     hero.hp-=dragon.atk*0.3;
        //     heroStatus["poison"].first--;
        // }
		//
		// effect = "";
		// if(dragonStatus["burned"].first==1) effect += "燃燒 ";
		// if(dragonStatus["dizzing"].first==1 && dragonStatus["frozen"].first==0) effect += "暈眩 ";
		// if(dragonStatus["sapping"].first==1) effect += "吸血 ";
		// if(heroStatus["shielding"].first==1) effect += "護盾 ";
		// if(heroStatus["treating"].first==1) effect += "回復 ";
		// if(heroStatus["weaken"].first==1) effect += "弱化 ";
        // if(heroStatus["reflect"].first==1) effect += "反彈 ";
        // if(heroStatus["poison"].first==1) effect += "中毒 ";
		// if (effect != ""){
		// 	cout<<bold_text( effect + yellow_text("效果將在下一回合結束時失效"))<<endl<<endl;
		// 	this_thread::sleep_for(chrono::milliseconds(200));
		// }
		//
		// hero.ap++;
		// this_thread::sleep_for(chrono::milliseconds(1500));
	}
}
