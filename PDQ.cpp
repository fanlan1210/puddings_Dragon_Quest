#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;
//改變文字顏色
string red_text(string text){return "\033[0;91m" + text + "\033[0m";}
string green_text(string text){return "\033[0;92m" + text + "\033[0m";}
string yellow_text(string text){return "\033[0;93m" + text + "\033[0m";}
string blue_text(string text){return "\033[0;94m" + text + "\033[0m";}
string magenta_text(string text){return "\033[0;95m" + text + "\033[0m";}
string cyan_text(string text){return "\033[0;96m" + text + "\033[0m";}
string white_text(string text){return "\033[0;97m" + text + "\033[0m";}

int dragon_death_check(int hp){
	if(hp<=0)
	    {
			this_thread::sleep_for(chrono::milliseconds(700));
			cout<<endl<<red_text("勇者擊敗了惡龍!");
			this_thread::sleep_for(chrono::milliseconds(300));
			cout<<endl;
			system("pause");
			exit(0);
	    }
		return 0;
}
int gain_hp_check(int* gain_hp,int* hp,int* max_hp){
	if(hp>max_hp)
	{
		*gain_hp = *max_hp-*hp;
		*hp = *max_hp;
	}
	return 0;
}

int main()
{
	int hero_maxhp,hero_hp,hero_atk,defend=0,ap=0; //勇者數值
	int dragon_hp,dragon_atk,dragon_maxhp; //惡龍數值
	int round,random_num,damage,gain_hp,lost_hp; // 計算用數值
	bool freeze=1,fire=1,swipe=1,dizzy=1,blood=1,shield=1,cure=1,treat=1,pow=0; //技能開關
	int freeze_cd=18,fire_cd=8,swipe_cd=5,dizzy_cd=13,blood_cd=27,shield_cd=16,\
		cure_cd=20,treat_cd=14; //Cool Down
	int dizzied=0,burned=0,freezed=0,curing=0,dizzing=0,sapping=0,shielding=0,stand=0; // 持續狀態
	double damage_rate;
	string action,yn;
	cout<<white_text(" ---------------")<<endl;
	cout<<white_text("|★☆★☆★☆★☆|")<<endl;
	cout<<white_text("|勇者鬥惡龍|")<<endl;
	cout<<white_text("|☆★☆★☆★☆★|")<<endl;
	cout<<white_text(" ---------------")<<endl;
	cout<<"Beta 5.2.0_DEV"<<endl<<endl;
	int game_diffculty,choice;
	cout<<"請選擇遊戲難度(0:自訂，簡單:1~困難:3)";
	cin>>choice;
	if(choice == 0){
		cout<<white_text("勇者最大血量: ");
		cin>>hero_hp;
		cout<<endl<<white_text("勇者基礎攻擊力: ");
		cin>>hero_atk;
		cout<<endl<<white_text("惡龍最大血量: ");
		cin>>dragon_hp;
		cout<<endl<<white_text("惡龍基礎攻擊力: ");
		cin>>dragon_atk;
	}
	else if(choice == 1){
		cout<<yellow_text("選擇為簡單難度")<<endl;
		hero_hp = 300;
		hero_atk = 5;
		dragon_hp = 100;
		dragon_atk = 10;
	}
	else if(choice == 2){
		cout<<yellow_text("選擇為普通難度")<<endl;
		hero_hp = 200;
		hero_atk = 5;
		dragon_hp = 100;
		dragon_atk = 10;
	}
	else if(choice == 3){
		cout<<yellow_text("選擇為困難難度")<<endl;
		hero_hp = 100;
		hero_atk = 5;
		dragon_hp = 150;
		dragon_atk = 10;
	}
	cout<<"------------------------------------------------------------"<<endl;
	hero_maxhp = hero_hp;
	dragon_maxhp=dragon_hp;
	while(1)
	{
		cout<<endl<<"是否需要遊戲說明及技能介紹? | [y]es / [n]o |"<<endl<<endl;
		cin>>yn;
		if(yn=="yes" || yn == "y")
		{
			this_thread::sleep_for(chrono::milliseconds(300));
			cout<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"遊戲方式:"<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<yellow_text("\t輸入技能之代號或名稱即可攻擊")<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"\t普通攻擊: 造成基礎傷害乘以傷害係數的傷害"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"\t雙重普通攻擊: 攻擊2次，但傷害減半，傷害係數各自分開計算"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"\t防禦: 該回合不進行任何動作，抵擋住惡龍之60%的傷害"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"\t傷害係數: 可能是0.90、0.95、1.00、1.05、1.10或1.80(暴擊)"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"\t技能之冷卻時間(CD)到0即可再次使用該技能"<<endl;
			cout<<endl;
			this_thread::sleep_for(chrono::milliseconds(300));
			cout<<"------------------------------------------------------------"<<endl;
			system("pause");
			cout<<"技能介紹:"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"freeze(冰凍 CD-18):"<<endl<<endl;
			cout<<"\t冰凍惡龍3回合(包括當前回合)，使惡龍無法行動"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"fire(燃燒 CD-8):"<<endl<<endl;
			cout<<"\t接下來的5回合(包括當前回合)，對惡龍造成攻擊之45%的傷害"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"swipe(重擊 CD-5):"<<endl<<endl;
			cout<<"\t該回合對惡龍造成攻擊力3倍之傷害(無法再與暴擊加成)"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"dizzy(暈眩 CD-13):"<<endl<<endl;
			cout<<"\t接下來的4回合(包括當前回合)，惡龍有40%的機率傷害自己"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"blood(吸血 CD-27):"<<endl<<endl;
			cout<<"\t接下來的3回合(包括當前回合)，將惡龍當前生命之3%，轉成自己的血量"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"shield(護盾 CD-16):"<<endl<<endl;
			cout<<"\t接下來的3回合(包括當前回合)，免疫惡龍的所有傷害"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"cure(治癒 CD-20):"<<endl<<endl;
			cout<<"\t該回合回復最大生命之40%"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(900));
			cout<<"treat(回復 CD-14):"<<endl<<endl;
			cout<<"\t接下來的3回合(包括當前回合)，回復已損生命之20%"<<endl<<endl;
			cout<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			system("pause");
			cout<<"怒氣值:"<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"\t每回合加1，若惡龍該回合暴擊則再加1，到10則可以使用必殺技pow"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"pow(必殺技):"<<endl;
			cout<<"\t使用後怒氣值減10，該回合對惡龍造成攻擊力5倍之傷害，"<<endl;
			cout<<"\t並有70%機率在當前回合定身惡龍"<<endl;
			system("pause");
			cout<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"惡龍技能:"<<endl;
			cout<<"龍之吐息:"<<endl<<endl;
			cout<<"\t無視護盾效果，對勇者造成其最大生命值10%傷害"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(1000));
			system("pause");
			/*
			cout<<"弱化:"<<endl<<endl;
			cout<<"\t接下來的三回合，勇者的攻擊力弱化30%，受到傷害提升10%"<<endl<<endl;
			cout<<"反彈:"<<endl<<endl;
			cout<<"\t接下來的2回合，反彈勇者的傷害之40%，第3回合的攻擊力為2倍"<<endl<<endl;
			cout<<"毒氣:"<<endl<<endl;
			cout<<"\t接下來的5回合，對勇者造成攻擊30%之傷害"<<endl<<endl;
			cout<<"炸彈:"<<endl<<endl;
			cout<<"\t該回合對勇者造成連續5次攻擊40%之傷害"<<endl<<endl;
			cout<<"自爆:"<<endl<<endl;
			cout<<"\t增加自身最大血量20%之護盾，若勇者在3回合內未能打掉護盾，勇者死亡"<<endl<<endl;
			cout<<endl;
			*/
			break;
		}
		else if(yn=="no" || yn == "n")
			break;
		else
			continue;
	}

	for(round=1;round>0;round++)
	{
		cout<<endl<<"------------------------------------------------------------"<<endl;
		/* 使用者介面 */
	   	cout<<"第 "<<round<<" 回合:"<<endl;
		if(ap>=10&&pow==0)
		{
			pow++;
		}
		cout<<"攻擊: | +  atk|| ++  double atk|| -  defend|"<<endl;
		cout<<"技能: "<<endl;
			cout<<white_text("| 1  ")<<left<<setw(6)<<"freeze"<<white_text(" CD: ")<<left<<setw(2)<<18-freeze_cd<<white_text("/18")<<white_text(" |");
			cout<<white_text("| 2  ")<<left<<setw(6)<<"fire"<<white_text(" CD: ")<<left<<setw(2)<<8-fire_cd<<white_text("/8 ")<<white_text(" |");
			cout<<white_text("| 3  ")<<left<<setw(6)<<"swipe"<<white_text(" CD: ")<<left<<setw(2)<<5-swipe_cd<<white_text("/5 ")<<white_text(" |");
			cout<<endl;
			cout<<white_text("| 4  ")<<left<<setw(6)<<"dizzy"<<white_text(" CD: ")<<left<<setw(2)<<13-dizzy_cd<<white_text("/13")<<white_text(" |");
			cout<<white_text("| 5  ")<<left<<setw(6)<<"blood"<<white_text(" CD: ")<<left<<setw(2)<<27-blood_cd<<white_text("/27")<<white_text(" |");
			cout<<white_text("| 6  ")<<left<<setw(6)<<"shield"<<white_text(" CD: ")<<left<<setw(2)<<16-shield_cd<<white_text("/16")<<white_text(" |");
			cout<<endl;
			cout<<white_text("| 7  ")<<left<<setw(6)<<"cure"<<white_text(" CD: ")<<left<<setw(2)<<20-cure_cd<<white_text("/20")<<white_text(" |");
			cout<<white_text("| 8  ")<<left<<setw(6)<<"treat"<<white_text(" CD: ")<<left<<setw(2)<<14-treat_cd<<white_text("/14")<<white_text(" |");
		if(pow==1)
			cout<<yellow_text("| !   pow |");
		cout<<endl<<endl;
		cout<<white_text("怒氣值: ")<<ap<<endl<<endl;
		cout<<white_text("勇者血量:")<<hero_hp<<white_text("/")<<hero_maxhp<<white_text("  惡龍血量:")<<dragon_hp<<white_text("/")<<dragon_maxhp<<endl<<endl;
		// 各項技能CD判斷
		if(freeze==0)
		{
			if(freeze_cd<18)
				freeze_cd++;
			else if(freeze_cd==18)
				freeze++;
		}
		if(fire==0)
		{
			if(fire_cd<8)
				fire_cd++;
			else if(fire_cd==8)
				fire++;
		}
		if(swipe==0)
		{
			if(swipe_cd<5)
				swipe_cd++;
			else if(swipe_cd==5)
				swipe++;
		}
		if(dizzy==0)
		{
			if(dizzy_cd<13)
				dizzy_cd++;
			else if(dizzy_cd==13)
				dizzy++;
		}
		if(blood==0)
		{
			if(blood_cd<27)
				blood_cd++;
			else if(blood_cd==27)
				blood++;
		}
		if(shield==0)
		{
			if(shield_cd<16)
				shield_cd++;
			else if(shield_cd==16)
				shield++;
		}
		if(cure==0)
		{
			if(cure_cd<20)
				cure_cd++;
			else if(cure_cd==20)
				cure++;
		}
		if(treat==0)
		{
			if(treat_cd<14)
				treat_cd++;
			else if(treat_cd==14)
				treat++;
		}
		// 隨機傷害倍率
		srand(time(NULL));
		damage_rate=rand()%14;
		damage_rate=0;
		action="";
		switch(random_num)
		{
		case 0:
		case 1:
			damage_rate=0.9;
			break;
		case 2:
		case 3:
		case 4:
			damage_rate=0.95;
			break;
		case 5:
		case 6:
		case 7:
			damage_rate=1;
			break;
		case 8:
		case 9:
		case 10:
			damage_rate=1.05;
			break;
		case 11:
		case 12:
			damage_rate=1.1;
			break;
		case 13:
			damage_rate=1.8;
			break;
		}
		damage=hero_atk*damage_rate; //計算勇者造成傷害
		while(true) //使用者輸入指令與判斷
		{
		    cout << white_text(">>>");
		    cin>>action;
			cout<<endl;
			if(action=="+")
			{
				this_thread::sleep_for(chrono::milliseconds(600));
				cout<<"勇者對惡龍造成了 "<<damage<<" 點傷害";
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)"<<endl;
		    	cout<<endl;
	   			dragon_hp=dragon_hp-damage;

				dragon_death_check(dragon_hp);
	   			break;
			}
			else if(action=="++")
			{
				this_thread::sleep_for(chrono::milliseconds(300));
				cout<<"勇者對惡龍造成了 "<<damage/2<<" 點傷害";
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl;
	   			dragon_hp=dragon_hp-(damage/2);
	   			srand(time(NULL)); //計算第二次勇者攻擊傷害值
				damage_rate=rand()%14;
				damage_rate=0;
				this_thread::sleep_for(chrono::milliseconds(300));
				switch(random_num)
				{
					case 0:
					case 1:
						damage_rate=0.9;
						break;
					case 2:
					case 3:
					case 4:
						damage_rate=0.95;
						break;
					case 5:
					case 6:
					case 7:
						damage_rate=1;
						break;
					case 8:
					case 9:
					case 10:
						damage_rate=1.05;
						break;
					case 11:
					case 12:
						damage_rate=1.1;
						break;
					case 13:
						damage_rate=1.8;
						break;
				}
				damage=hero_atk*damage_rate;
				cout<<"勇者對惡龍造成了 "<<damage/2<<" 點傷害";
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl;
	   			dragon_hp=dragon_hp-(damage/2);

				dragon_death_check(dragon_hp);
	   			break;
			}
			else if(action=="-")
			{
				this_thread::sleep_for(chrono::milliseconds(600));
				cout<<"(防禦)"<<endl;
				defend++;
				break;
			}
			else if(freeze==1&& ( action=="1" || action == "freeze") )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				freeze=false;
				freezed=2;
				cout<<"勇者使用了freeze(冰凍)"<<endl;
				freeze_cd=freeze_cd-18;
				break;
			}
			else if(fire==1&& ( action=="2" || action == "fire" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				fire=false;
				cout<<"勇者使用了fire(燃燒)"<<endl;
	   			burned=5;
	   			fire_cd=fire_cd-8;
	   			break;
			}
			else if(swipe==1&& ( action=="3" || action == "swipe" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				swipe=false;
	   			cout<<"\a勇者使用了swipe(重擊)"<<endl<<endl;
				cout<<"勇者對惡龍造成了 "<<hero_atk*3<<" 點傷害"<<endl;
	    		dragon_hp=dragon_hp-(hero_atk*3);
	    		swipe_cd-=5;

				dragon_death_check(dragon_hp);
	    		break;
			}
			else if(dizzy==1&&( action=="4" || action == "dizzy" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				dizzy=false;
	   			cout<<"勇者使用了dizzy(暈眩)"<<endl;
	   			dizzing=4;
	   			dizzy_cd-=13;
	   			break;
			}
			else if(blood==1&&( action=="5" || action == "blood" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				blood=false;
	   			cout<<"勇者使用了blood(吸血)"<<endl;
	   			sapping=3;
	   			blood_cd-=27;
	   			break;
			}
			else if(shield==1&&( action=="6" || action == "shield" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				shield=false;
	   			cout<<"勇者使用了shield(護盾)"<<endl;
	   			shielding=3;
	   			shield_cd-=16;
	   			break;
			}
			else if(cure==1&&( action=="7" || action == "cure" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				cure=false;
				cout<<"勇者使用了cure(治癒)"<<endl;
				gain_hp=hero_maxhp*0.4;
				cout<<endl;
				hero_hp=hero_hp+gain_hp;
				if(hero_hp>hero_maxhp)
				{
					gain_hp+=hero_maxhp-hero_hp;
					hero_hp=hero_maxhp;
				}
				cout<<"勇者回復了 "<<gain_hp<<" 點生命"<<endl;
				cure_cd-=20;
				break;
			}
			else if(treat==1&&(action=="8"|| action == "treat"))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				treat=false;
				cout<<"勇者使用了treat(回復)"<<endl;
				curing=3;
				treat_cd-=14;
				break;
			}
			else if(pow==1&& (action=="!"|| action == "pow"))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				pow=false;
				cout<<"勇者使用了pow(必殺技)"<<endl;
				cout<<"!!!!!!!!!!!!!!!!!!!!!"<<endl;
				cout<<"\a\a\a\a\a\a\a\a\a\a";
				this_thread::sleep_for(chrono::milliseconds(800));
				cout<<"勇者對惡龍造成了 "<<hero_atk*5<<" 點傷害"<<endl;
	    		dragon_hp=dragon_hp-(hero_atk*5);

				ap=ap-10;
				this_thread::sleep_for(chrono::milliseconds(1200));
				dragon_death_check(dragon_hp);
			    random_num=0;
				srand(time(NULL));
				random_num=rand()%10;
				this_thread::sleep_for(chrono::milliseconds(500));
				cout<<endl;
				switch(random_num)
				{
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						stand=1;
						cout<<"定身成功!"<<endl;
						break;
					case 7:
					case 8:
					case 9:
						cout<<"定身失敗!"<<endl;
						break;
				}
	    		break;
			}
			else
				cout<<"你輸入的文字並未屬於任何一項行動"<<endl<<endl;
				continue;
		}
		cout<<endl;
		if(burned>0||curing>0||sapping>0)
		{
			if(burned>0)
			{
				lost_hp=hero_atk*0.45;
				this_thread::sleep_for(chrono::milliseconds(900));
				dragon_hp=dragon_hp-lost_hp;
				cout<<endl;
				cout<<"燃燒對惡龍造成了 "<<lost_hp<<" 點傷害"<<endl;
				burned--;
				dragon_death_check(dragon_hp);
			}
			if(curing>0)
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				gain_hp=(hero_maxhp-hero_hp)*0.2;
				hero_hp=hero_hp+gain_hp;
				gain_hp_check(&gain_hp,&hero_hp,&hero_maxhp);
				cout<<endl;
				cout<<"勇者回復了 "<<gain_hp<<" 點血量"<<endl;
				curing--;
			}
			if(sapping>0)
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				gain_hp=dragon_hp*0.03;
				hero_hp=hero_hp+gain_hp;
				gain_hp_check(&gain_hp,&hero_hp,&hero_maxhp);
				dragon_hp=dragon_hp-gain_hp;
				cout<<endl;
				cout<<"勇者將惡龍的 "<<gain_hp<<" 點血量轉換成自己的血量"<<endl;
				sapping--;
				dragon_death_check(dragon_hp);
			}
			cout<<endl;
		}
		if(stand==1)
		{
			stand=false;
			continue;
		}
		srand(time(NULL));
		damage_rate=rand()%14;
		damage_rate=0;
		switch(random_num)
		{
			case 0:
			case 1:
				damage_rate=0.9;
				break;
			case 2:
			case 3:
			case 4:
				damage_rate=0.95;
				break;
			case 5:
			case 6:
			case 7:
				damage_rate=1;
				break;
			case 8:
			case 9:
			case 10:
				damage_rate=1.05;
				break;
			case 11:
			case 12:
				damage_rate=1.1;
				break;
			case 13:
				damage_rate=1.8;
				break;
		}

		/* 如果惡龍沒有處於冰凍狀態，才繼續惡龍的攻擊判斷 */
		if(freezed==0)
		{
			this_thread::sleep_for(chrono::milliseconds(900));
		    damage=dragon_atk*damage_rate;
		   	if(dizzing>0)
			{
				random_num=0;
				srand(time(NULL));
				random_num=rand()%5;
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
						cout<<"暈眩失敗!"<<endl<<endl;
						break;
				}
				dizzing--;
			}
			if(dizzied==0)
			{
				damage_rate=rand()%5;
				if(damage_rate==4){
					cout<<"惡龍使出"<<magenta_text("龍之吐息")<<"!";
					cout<<"惡龍對勇者造成了 "<<hero_maxhp/10<<" 點傷害";
					hero_hp = hero_hp - hero_maxhp / 10;
				}else{
				if(shielding==0&&defend==1)
				{
					cout<<"勇者防禦住了 "<<int(damage*0.6)<<" 點傷害"<<endl<<endl;
					damage=damage*0.4;
					defend--;
				}
				else if(shielding>0&&defend==0)
				{
					cout<<"(護盾吸收了 "<<damage<<" 點傷害)"<<endl;
					damage=0;
					shielding--;
				}
				else if(shielding>0&&defend==1)
				{
					cout<<"勇者防禦住了 0 點傷害"<<endl<<endl;
					defend--;
					cout<<"(護盾吸收了 "<<damage<<" 點傷害)"<<endl;
					damage=0;
					shielding--;
				}
				cout<<"惡龍對勇者造成了 "<<damage<<" 點傷害";
			    if(damage_rate==1.8)
			    {
			    	cout<<"\a(暴擊!)"<<endl;
					ap++;
					cout<<"勇者怒氣值加1"<<endl;
				}
				cout<<endl;
				hero_hp=hero_hp-damage;
				}
			}
			else if(dizzied==1)
			{
				dizzied--;
				cout<<"惡龍對自己造成了 "<<damage<<" 點傷害";
			    if(damage_rate==1.8)
			    {
			    	cout<<"\a(暴擊!)"<<endl;
					ap++;
				}
				cout<<endl;
				dragon_hp=dragon_hp-damage;
			}
			if(dragon_hp<0)
				dragon_hp=0;
			dragon_death_check(dragon_hp);
		    if(hero_hp<0)
				hero_hp=0;
		    if(hero_hp<=0)
		    {
				this_thread::sleep_for(chrono::milliseconds(700));
		    	cout<<endl<<cyan_text("勇者被惡龍擊敗了!");
				this_thread::sleep_for(chrono::milliseconds(500));
				cout<<endl;
				system("pause");
				return 0;
		    }
		    cout<<endl;
		}
		else if(freezed==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<"惡龍將在下一回合解凍"<<endl<<endl;
			freezed--;
		}
		else
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<"惡龍將在 "<<freezed<<" 回合後解凍"<<endl<<endl;
			freezed--;
		}

		if(burned==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<"燃燒效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(dizzing==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<"暈眩效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(sapping==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<"吸血效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(shielding==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<"護盾效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(curing==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<"回復效果將在下一回合結束時失效"<<endl<<endl;
		}
		ap++;
		this_thread::sleep_for(chrono::milliseconds(1500));
	}
}
