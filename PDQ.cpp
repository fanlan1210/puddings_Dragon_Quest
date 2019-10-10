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

using namespace std;
//版本資訊
inline string version(){return "Beta 6.9.3_DEV";}

void pause();

struct entity{
	int maxhp;
	int hp;
	int atk;
	int ap;
};

int main()
{
	/* 初始化 */
	entity hero,dragon;
	//int /*hero_maxhp,hero_hp,hero_atk,*/ap=0; //勇者數值
	hero.ap=0;
	int /*dragon_hp,dragon_atk,dragon_maxhp,*/dragon_shield=0; //惡龍數值
	int round,random_num,damage,gain_hp,lost_hp; // 計算用數值

	//勇者技能開關
	bool /*defend=false,
		 freeze=true,fire=true,swipe=true,dizzy=true,blood=true,
		 shield=true,cure=true,treat=true,*/pow=false;
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
	/*int freeze_cd=18,fire_cd=9,swipe_cd=5,dizzy_cd=13,blood_cd=27,shield_cd=16,
		cure_cd=20,treat_cd=14; */

	map<string,pair<int,int>> mapCooldown; // CD pair : current,max
	mapCooldown["freeze"] = {18,18};
	mapCooldown["fire"] = {9,9};
	mapCooldown["swipe"] = {5,5};
	mapCooldown["dizzy"] = {13,13};
	mapCooldown["blood"] = {27,27};
	mapCooldown["shield"] = {16,16};
	mapCooldown["cure"] = {20,20};
	mapCooldown["treat"] = {14,14};
	map<string,pair<int,int>>::iterator it;

	int dizzied=0,burned=0,frozen=0,curing=0,dizzing=0,sapping=0,explosion=0,stand=0; // 惡龍持續狀態
    int weaken=0,reflect=0,poison=0,shielding=0; // 勇者持續狀態
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
		cout<<endl<<white_text("勇者基礎攻擊力: ");
		cin>>hero.atk;
		cout<<endl<<white_text("惡龍最大血量: ");
		cin>>dragon.hp;
		cout<<endl<<white_text("惡龍基礎攻擊力: ");
		cin>>dragon.atk;
	}
	else if(choice == 1){
		cout<<yellow_text("選擇為新手難度")<<endl;
		hero.hp = 4000;
		hero.atk = 600;
		dragon.hp = 4000;
		dragon.atk = 200;
	}
	else if(choice == 2){
		cout<<yellow_text("選擇為普通難度")<<endl;
		hero.hp = 3500;
		hero.atk = 500;
		dragon.hp = 8000;
		dragon.atk = 250;
	}
	else if(choice == 3){
		cout<<yellow_text("選擇為困難難度")<<endl;
		hero.hp = 3000;
		hero.atk = 500;
		dragon.hp = 10000;
		dragon.atk = 300;
	}
	else if(choice == 4){
		cout<<yellow_text("選擇為夢魘難度")<<endl;
		hero.hp = 2500;
		hero.atk = 400;
		dragon.hp = 12000;
		dragon.atk = 300;
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
		cout<<white_text("勇者血量:")<<red_text(to_string(hero.hp))<<white_text("/"+to_string(hero.maxhp))
			<<white_text("  惡龍血量:")<<red_text(to_string(dragon.hp))<<white_text("/"+to_string(dragon.maxhp));
		if(explosion>0) cout <<"("<< custom_text("+"+to_string(dragon_shield),128)<<"/"<<custom_text(to_string(explosion),92)<<")";
		cout<<endl<<endl;
		// 各項技能CD判斷
		for(it=mapCooldown.begin();it!=mapCooldown.end();it++){
			//cout<<it->first<<" current:"<<(it->second).first<<" max:"<<(it->second).second<<endl;
			if( (it->second).first < (it->second).second ){
				if( (it->second).first == 0)
					skillSwitch[it->first] = false;
				(it->second).first++;
			}
			else if((it->second).first == (it->second).second)
				skillSwitch[it->first] = true;
		}
		/*
		if(freeze==false)
		{
			if(freeze_cd<18)
				freeze_cd++;
			else if(freeze_cd==18)
				freeze=true;
		}
		if(fire==false)
		{
			if(fire_cd<9)
				fire_cd++;
			else if(fire_cd==9)
				fire=true;
		}
		if(swipe==false)
		{
			if(swipe_cd<5)
				swipe_cd++;
			else if(swipe_cd==5)
				swipe=true;
		}
		if(dizzy==false)
		{
			if(dizzy_cd<13)
				dizzy_cd++;
			else if(dizzy_cd==13)
				dizzy=true;
		}
		if(blood==false)
		{
			if(blood_cd<27)
				blood_cd++;
			else if(blood_cd==27)
				blood=true;
		}
		if(shield==false)
		{
			if(shield_cd<16)
				shield_cd++;
			else if(shield_cd==16)
				shield=true;
		}
		if(cure==false)
		{
			if(cure_cd<20)
				cure_cd++;
			else if(cure_cd==20)
				cure=true;
		}
		if(treat==false)
		{
			if(treat_cd<14)
				treat_cd++;
			else if(treat_cd==14)
				treat=true;
		}*/

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
		if(weaken>0) {damage*=0.7;} //判斷勇者攻擊是否有被弱化
		while(true) //使用者輸入指令與判斷
		{
		    cout << white_text(">>> ");
		    cin>>action;
			cout<<endl;
			if(action=="+")
			{
				this_thread::sleep_for(chrono::milliseconds(600));
				if(explosion>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 "+to_string(damage)+" 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)"<<endl;
		    	cout<<endl;
	   			dragon.hp=dragon.hp-damage;
	   			if(reflect>0){ hero.hp -= reflect_damage(&reflect,damage);} //判斷惡龍是否使用反彈
				dragon_death_check(dragon.hp);
	   			break;
			}
			else if(action=="++")
			{
				this_thread::sleep_for(chrono::milliseconds(300));
				damage/=2;
				if(explosion>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 " + to_string(damage) + " 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl;
	   			dragon.hp=dragon.hp-(damage/2);
	   			if(reflect>0){ hero.hp -= reflect_damage(&reflect,damage);}
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
				if(weaken>0) {damage*=0.7;}
				damage/=2;
				if(explosion>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 " + to_string(damage) + " 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl<<endl;
	   			dragon.hp=dragon.hp-(damage/2);
                if(reflect>0){ hero.hp -= reflect_damage(&reflect,damage);}
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
				//skillSwitch["freeze"] = false;
				mapCooldown["freeze"].first = 0;
				frozen=2;
				cout<<yellow_text("勇者使用了") + cyan_text("freeze(冰凍)")<<endl;
				//freeze_cd=freeze_cd-18;
				break;
			}
			else if(skillSwitch["fire"] == true&& ( action=="2" || action == "fire" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				//skillSwitch["fire"] = false;
				mapCooldown["fire"].first = 0;
				cout<<yellow_text("勇者使用了") + red_text("fire(燃燒)")<<endl;
	   			burned=5;
	   			//fire_cd=fire_cd-9;
	   			break;
			}
			else if(skillSwitch["swipe"] == true&& ( action=="3" || action == "swipe" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				//skillSwitch["swipe"] = false;
				mapCooldown["swipe"].first = 0;
	   			cout<<yellow_text("\a勇者使用了swipe(重擊)")<<endl<<endl;
				damage=hero.atk*3;
				if(explosion>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<"勇者對惡龍造成了 "<<damage<<" 點傷害"<<endl;
	    		dragon.hp=dragon.hp-damage;
	    		//swipe_cd-=5;

				dragon_death_check(dragon.hp);
	    		break;
			}
			else if(skillSwitch["dizzy"] == true&&( action=="4" || action == "dizzy" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				//skillSwitch["dizzy"] = false;
				mapCooldown["dizzy"].first = 0;
	   			cout<<yellow_text("勇者使用了dizzy(暈眩)")<<endl;
	   			dizzing=4;
	   			//dizzy_cd-=13;
	   			break;
			}
			else if(skillSwitch["blood"] == true&&( action=="5" || action == "blood" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				//skillSwitch["blood"]=false;
				mapCooldown["blood"].first = 0;
	   			cout<<yellow_text("勇者使用了") + dark_red_text("blood(吸血)")<<endl;
	   			sapping=3;
	   			//blood_cd-=27;
	   			break;
			}
			else if(skillSwitch["shield"] == true&&( action=="6" || action == "shield" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				skillSwitch["shield"]=false;
				mapCooldown["shield"].first = 0;
	   			cout<<yellow_text("勇者使用了shield(護盾)")<<endl;
	   			shielding=3;
	   			//shield_cd-=16;
	   			break;
			}
			else if(skillSwitch["cure"] == true&&( action=="7" || action == "cure" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				//skillSwitch["cure"] = false;
				mapCooldown["cure"].first = 0;
				cout<<yellow_text("勇者使用了") +red_text("cure(治癒)")<<endl;
				gain_hp=hero.maxhp*0.4;
				cout<<endl;
				gain_hp_check(&gain_hp,&hero.hp,&hero.maxhp);
				cout<<"勇者回復了 "<<gain_hp<<" 點生命"<<endl;
				//cure_cd-=20;
				break;
			}
			else if(skillSwitch["treat"] == true&&(action=="8"|| action == "treat"))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				//skillSwitch["treat"]=false;
				mapCooldown["treat"].first = 0;
				cout<<yellow_text("勇者使用了") + red_text("treat(回復)")<<endl;
				curing=3;
				//treat_cd-=14;
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
				if(explosion>0 && dragon_shield!=0) dragon_shield_check(&dragon_shield,&damage);
				cout<<white_text("勇者對惡龍造成了 "+ to_string(damage) +" 點傷害")<<endl;
	    		dragon.hp=dragon.hp-(hero.atk*5);
	    		if(reflect>0){ hero.hp -= reflect_damage(&reflect,hero.atk*5);}
				hero.ap=hero.ap-10;
				this_thread::sleep_for(chrono::milliseconds(1200));
				dragon_death_check(dragon.hp);

				random_num=gen_rand()%10;
				this_thread::sleep_for(chrono::milliseconds(500));
				cout<<endl;
				if ( random_num == 6 ) {
					 stand=1;
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
		}
		if(burned>0||curing>0||sapping>0||shielding>0)
		{
			if(burned>0)
			{
				lost_hp=hero.atk*0.4;
				this_thread::sleep_for(chrono::milliseconds(900));
				dragon.hp=dragon.hp-lost_hp;
				cout<<endl;
				cout<<italic_text("燃燒對惡龍造成了 "+to_string(lost_hp)+" 點傷害")<<endl;
				//if(reflect>0){ hero.hp -= reflect_damage(&reflect,damage);}
				burned--;
				dragon_death_check(dragon.hp);
			}
			if(curing>0)
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				gain_hp=(hero.maxhp-hero.hp)*0.2;
				gain_hp_check(&gain_hp,&hero.hp,&hero.maxhp);
				cout<<endl;
				cout<<italic_text("勇者回復了 "+to_string(gain_hp)+" 點血量")<<endl;
				curing--;
			}
			if(sapping>0)
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				gain_hp=dragon.hp*0.03;
				gain_hp_check(&gain_hp,&hero.hp,&hero.maxhp);
				dragon.hp=dragon.hp-gain_hp;
				cout<<endl;
				cout<<italic_text("勇者將惡龍的 "+to_string(gain_hp)+" 點血量轉換成自己的血量")<<endl;
				sapping--;
				dragon_death_check(dragon.hp);
			}
			if(shielding>0)
                shielding--;
			cout<<endl;
		}
		if(stand==1)
		{
			stand=false;
			continue;
		}
        if(weaken>0) weaken--;
        if(reflect>0) reflect--;
		if(explosion>0) explosion--;
		random_num=gen_rand()%14;
		damage_rate=1;
		if(random_num==0||random_num==1) {damage_rate=0.9;}
        if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
        if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
        if(random_num==8||random_num==9) {damage_rate=1.1;}
        if(random_num==10) {damage_rate=1.8;}
		/* 如果惡龍沒有處於冰凍狀態，才繼續惡龍的攻擊判斷 */
		if(frozen==0)
		{
			this_thread::sleep_for(chrono::milliseconds(900));
		    damage=dragon.atk*damage_rate; //惡龍傷害計算
		    if(weaken) {damage*=1.1;}
		   	if(dizzing>0)
			{
				random_num=0;

				random_num=gen_rand()%5;
				this_thread::sleep_for(chrono::milliseconds(500));
				if(action=="4")
					cout<<endl;
				switch(random_num)
				{
					case 0:
					case 1:
						dizzied=1;
						cout<<"暈眩成功!"<<endl<<endl;
						break;
					case 2:
					case 3:
					case 4:
						cout<<"暈眩失敗!惡龍仍保持清醒"<<endl<<endl;
						break;
				}
				dizzing--;
			}
			if(dizzied==0)
			{
				random_num=gen_rand()%20;
				if(random_num==0||random_num==1||random_num==2||random_num==3){
					cout<<yellow_text("惡龍使出") + magenta_text("龍之吐息")<<"!"<<endl<<endl;
					cout<<"惡龍對勇者造成了 "<<hero.maxhp/8<<" 點傷害"<<endl;
					hero.hp = hero.hp - hero.maxhp / 8;
				}else if(random_num==4||random_num==5 && weaken==0){
					cout<<yellow_text("惡龍使出") + custom_text("弱化",205)<<endl;
					weaken=3;
				}else if(random_num==6||random_num==7 && reflect==0){
					cout<<yellow_text("惡龍使出") + cyan_text("反彈")<<endl;
					reflect=2;
				}else if(random_num==8||random_num==9 && poison==0){
					cout<<yellow_text("惡龍使出") + green_text("毒氣")<<endl;
					poison=5;
				}else if(random_num==10||random_num==11){
					cout<<yellow_text("惡龍使出") + green_text("連擊")<<endl<<endl;
					for(int i=0;i<5;i++)
                    {
                        random_num=gen_rand()%14;
                        damage_rate=1;
                        if(random_num==0||random_num==1) {damage_rate=0.9;}
                        if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
                        if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
                        if(random_num==8||random_num==9) {damage_rate=1.1;}
                        if(random_num==10) {damage_rate=1.8;}
                        damage=dragon.atk*damage_rate*0.45;
						def_check(&shielding,&skillSwitch["defend"],&damage);
                        hero.hp-=damage;
                        cout<<white_text("惡龍對勇者造成了 " + to_string(damage) + " 點傷害")<<endl;
                    }
				}else if(random_num==19 && explosion==0){
					cout<<yellow_text("惡龍使出") + custom_text("毀滅龍盾",128)<<endl;
					dragon_shield=dragon.maxhp*0.2;
					explosion=3;
				}
				else{
                    cout<<white_text("惡龍對勇者造成了 " + to_string(damage) + " 點傷害");
                    if(damage_rate==1.8)
                    {
                        cout<<"\a(暴擊!)"<<endl;
                        hero.ap++;
                        cout<<"勇者怒氣值加1"<<endl;
                    }
                    cout<<endl;
                    def_check(&shielding,&skillSwitch["defend"],&damage);
                    hero.hp=hero.hp-damage;
                }
			}
			else if(dizzied==1)
			{
				dizzied--;
				cout<<italic_text("惡龍對自己造成了 "+to_string(damage)+" 點傷害");
			    if(damage_rate==1.8)
			    {
			    	cout<<"\a(暴擊!)"<<endl;
				}
				cout<<endl;
				dragon.hp-=damage;
			}
			if(dragon.hp<0)
				dragon.hp=0;
			dragon_death_check(dragon.hp);
		    if(hero.hp<0)
				hero.hp=0;
		    if(hero.hp<=0)
		    {
				this_thread::sleep_for(chrono::milliseconds(700));
		    	cout<<endl<<dark_red_text("勇者被惡龍擊敗了!");
				this_thread::sleep_for(chrono::milliseconds(500));
				cout<<endl;
				pause();
				return 0;
		    }
		    cout<<endl;
		}
		else if(frozen==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("惡龍將在下一回合解凍")<<endl<<endl;
			frozen--;
		}
		else
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("惡龍將在 "+to_string(frozen)+" 回合後解凍")<<endl<<endl;
			frozen--;
		}
		if(explosion==0 && dragon_shield>0){
			hero.hp=0;
			cout<<custom_text("勇者被龍盾毀滅了",125)<<endl;
			pause();
			exit(0);
		}
		if(poison>0)
        {
            cout<<italic_text("中毒對勇者造成了 "+to_string( (int)(dragon.atk*0.3) )+" 點傷害")<<endl;
            hero.hp-=dragon.atk*0.3;
            poison--;
        }

		effect = "";
		if(burned==1) effect += "燃燒 ";
		if(dizzing==1 && frozen==0) effect += "暈眩 ";
		if(sapping==1) effect += "吸血 ";
		if(shielding==1) effect += "護盾 ";
		if(curing==1) effect += "回復 ";
		if(weaken==1) effect += "弱化 ";
        if(reflect==1) effect += "反彈 ";
        if(poison==1) effect += "中毒 ";
		if (effect != ""){
			cout<<bold_text( effect + "效果將在下一回合結束時失效")<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(200));
		}

		hero.ap++;
		this_thread::sleep_for(chrono::milliseconds(1500));
	}
}
