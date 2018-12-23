#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;
//改變文字狀態
string blink_text(string text){return "\033[5m" + text + "\033[25m";}
string bold_text(auto text){return string("\033[1m") + text + string("\033[21m");}
string italic_text(auto text){return string("\033[3m") + text + string("\033[23m");}
//改變文字顏色
string black_text(auto text){return string("\033[38;5;00m") + text + string("\033[37m");}
string dark_red_text(auto text){return string("\033[38;5;01m") + text + string("\033[37m");}
string red_text(auto text){return string("\033[38;5;09m") + text + string("\033[37m");}
string green_text(auto text){return string("\033[38;5;10m") + text + string("\033[37m");}
string yellow_text(auto text){return string("\033[38;5;11m") + text + string("\033[37m");}
string blue_text(auto text){return string("\033[38;5;12m") + text + string("\033[37m");}
string magenta_text(auto text){return string("\033[38;5;13m") + text + string("\033[37m");}
string cyan_text(auto text){return string("\033[38;5;14m") + text + string("\033[37m");}
string white_text(auto text){return string("\033[38;5;15m") + text + string("\033[37m");}

string custom_text(auto text,int color=7){
	return string("\033[38;5;"+to_string(color)+"m") + text + string("\033[37m");
	}
void custom_background(bool status,int color=0){
	if (status == true) cout<<string("\033[48;5;"+to_string(color)+"m");
	else cout<<string("\033[0m");
}


void dragon_death_check(int hp){
	if(hp<=0)
    {
        this_thread::sleep_for(chrono::milliseconds(700));
        cout<<endl<<red_text("勇者擊敗了惡龍!");
        this_thread::sleep_for(chrono::milliseconds(300));
        cout<<endl;
        system("pause");
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

void def_check(int* shielding,int* defend,int* damage){
    if(*shielding==0&&*defend==1)
    {
        cout<<"勇者防禦住了 "<<int(*damage*0.6)<<" 點傷害"<<endl<<endl;
        *damage=*damage*0.4;
        *defend--;
    }
    else if(*shielding>0&&*defend==0)
    {
        cout<<"(護盾吸收了 "<<*damage<<" 點傷害)"<<endl;
        *damage=0;
    }
    else if(*shielding>0&&*defend==1)
    {
        cout<<"勇者防禦住了 0 點傷害"<<endl<<endl;
        *defend--;
        cout<<"(護盾吸收了 "<<*damage<<" 點傷害)"<<endl;
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

int main()
{
	/* 初始化 */
	int hero_maxhp,hero_hp,hero_atk,defend=0,ap=0; //勇者數值
	int dragon_hp,dragon_atk,dragon_maxhp; //惡龍數值
	int round,random_num,damage,gain_hp,lost_hp,batter_random[5]; // 計算用數值
	bool freeze=true,fire=true,swipe=true,dizzy=true,blood=true,shield=true,cure=true,treat=true,pow=false; //勇者技能開關
	int freeze_cd=18,fire_cd=9,swipe_cd=5,dizzy_cd=13,blood_cd=27,shield_cd=16,
		cure_cd=20,treat_cd=14; //Cool Down
	int dizzied=0,burned=0,frozen=0,curing=0,dizzing=0,sapping=0,shielding=0,stand=0; // 惡龍持續狀態
    int weaken=0,reflect=0,poison=0; // 勇者持續狀態
	double damage_rate;
	string action,yn;
	/* 隨機亂數初始化 */
	random_device rand_dev;
	default_random_engine gen_rand(rand_dev());
	custom_background(true);
	cout<<white_text(" ---------------")<<endl;
	cout<<white_text("|★☆★☆★☆★☆|")<<endl;
	cout<<white_text("|勇者鬥惡龍|")<<endl;
	cout<<white_text("|☆★☆★☆★☆★|")<<endl;
	cout<<white_text(" ---------------")<<endl;
	cout<<"Beta 6.1.3_DEV"<<endl<<endl;
	int choice;
	cout<<"請選擇遊戲難度(0:新手 || 1:普通 || 2:困難 || 3:夢魘)"<<endl;
	cin>>choice;
	if(choice == 0){
		cout<<yellow_text("選擇為新手難度")<<endl;
		hero_hp = 4000;
		hero_atk = 600;
		dragon_hp = 4000;
		dragon_atk = 200;
	}
	else if(choice == 1){
		cout<<yellow_text("選擇為普通難度")<<endl;
		hero_hp = 3500;
		hero_atk = 500;
		dragon_hp = 8000;
		dragon_atk = 250;
	}
	else if(choice == 2){
		cout<<yellow_text("選擇為困難難度")<<endl;
		hero_hp = 3000;
		hero_atk = 500;
		dragon_hp = 10000;
		dragon_atk = 300;
	}
	else if(choice == 3){
		cout<<yellow_text("選擇為夢魘難度")<<endl;
		hero_hp = 2500;
		hero_atk = 400;
		dragon_hp = 12000;
		dragon_atk = 300;
	}
	cout<<"------------------------------------------------------------"<<endl;
	hero_maxhp = hero_hp;
	dragon_maxhp = dragon_hp;
	while(true)
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
			cout<<"fire(燃燒 CD-9):"<<endl<<endl;
			cout<<"\t接下來的5回合(包括當前回合)，對惡龍造成攻擊之40%的傷害"<<endl<<endl;
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
			system("pause");
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"怒氣值(AP):"<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"\t每回合加1，若惡龍該回合暴擊則再加1，到10則可以使用必殺技pow"<<endl<<endl;
			this_thread::sleep_for(chrono::milliseconds(800));
			cout<<"pow(必殺技):"<<endl;
			cout<<"\t使用後怒氣值減10，該回合對惡龍造成攻擊力5倍之傷害，"<<endl;
			cout<<"\t並有70%機率在當前回合定身惡龍"<<endl<<endl;
			cout<<endl;
			system("pause");
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"惡龍技能:"<<endl;
			cout<<"龍之吐息:"<<endl<<endl;
			cout<<"\t無視防禦及護盾效果，對勇者造成其最大生命值8%傷害"<<endl<<endl;
			cout<<"弱化:"<<endl<<endl;
			cout<<"\t接下來的3回合，勇者的攻擊力弱化30%，受到傷害提升10%"<<endl<<endl;
			cout<<"反彈:"<<endl<<endl;
			cout<<"\t下一回合，反彈勇者的攻擊傷害之40%，再下一回合反彈2倍傷害"<<endl<<endl;
			cout<<"毒氣:"<<endl<<endl;
			cout<<"\t接下來的5回合(包括當前回合)，對勇者造成攻擊30%之傷害，中毒傷害無視防禦及護盾效果"<<endl<<endl;
			cout<<"連擊:"<<endl<<endl;
			cout<<"\t該回合對勇者造成連續5次惡龍攻擊力45%之傷害"<<endl<<endl;
			/*cout<<"自爆:"<<endl<<endl;
			cout<<"\t增加自身最大血量20%之護盾，若勇者在3回合內未能打掉護盾，勇者死亡"<<endl<<endl;
			cout<<endl;
			*/
			this_thread::sleep_for(chrono::milliseconds(1000));
			system("pause");
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
		if(ap>=10&&pow==false)
		{
			pow=true;
		}
		cout<<"攻擊: | +  atk|| ++  double atk|| -  defend|"<<endl;
		cout<<"技能: "<<endl;
        cout<<white_text("| 1  ")<<left<<setw(21)<<cyan_text("freeze")<<white_text(" CD: ")<<left<<setw(2)<<18-freeze_cd<<white_text("/18 |");
        cout<<white_text("| 2  ")<<left<<setw(21)<<red_text("fire")<<white_text(" CD: ")<<left<<setw(2)<<9-fire_cd<<white_text("/ 9 |");
        cout<<white_text("| 3  ")<<left<<setw(21)<<yellow_text("swipe")<<white_text(" CD: ")<<left<<setw(2)<<5-swipe_cd<<white_text("/ 5 |");
        cout<<endl;
        cout<<white_text("| 4  ")<<left<<setw(21)<<yellow_text("dizzy")<<white_text(" CD: ")<<left<<setw(2)<<13-dizzy_cd<<white_text("/13 |");
        cout<<white_text("| 5  ")<<left<<setw(21)<<dark_red_text("blood")<<white_text(" CD: ")<<left<<setw(2)<<27-blood_cd<<white_text("/27 |");
        cout<<white_text("| 6  ")<<left<<setw(21)<<white_text("shield")<<white_text(" CD: ")<<left<<setw(2)<<16-shield_cd<<white_text("/16 |");
        cout<<endl;
        cout<<white_text("| 7  ")<<left<<setw(21)<<white_text("cure")<<white_text(" CD: ")<<left<<setw(2)<<20-cure_cd<<white_text("/20 |");
        cout<<white_text("| 8  ")<<left<<setw(21)<<white_text("treat")<<white_text(" CD: ")<<left<<setw(2)<<14-treat_cd<<white_text("/14 |");
		if (ap<10){
		cout<<yellow_text("| !  ")<<left<<setw(21)<<yellow_text("pow")<<white_text(" AP: ")<<left<<setw(2)<<ap<<white_text("(10)|");
		}else{
		cout<<yellow_text("| !  ")<<left<<setw(29)<<blink_text(yellow_text("pow"))<<white_text(" AP: ")<<left<<setw(2)<<ap<<white_text("(10)|");
		}
		cout<<endl<<endl;
		cout<<white_text("勇者血量:")<<red_text(to_string(hero_hp))<<white_text("/"+to_string(hero_maxhp))
			<<white_text("  惡龍血量:")<<red_text(to_string(dragon_hp))<<white_text("/"+to_string(dragon_maxhp))<<endl<<endl;
		// 各項技能CD判斷
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
		damage=hero_atk*damage_rate; //計算勇者造成傷害
		if(weaken>0) {damage*=0.7;} //判斷勇者攻擊是否有被弱化
		while(true) //使用者輸入指令與判斷
		{
		    cout << white_text(">>> ");
		    cin>>action;
			cout<<endl;
			if(action=="+")
			{
				this_thread::sleep_for(chrono::milliseconds(600));
				cout<<white_text("勇者對惡龍造成了 "+to_string(damage)+" 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)"<<endl;
		    	cout<<endl;
	   			dragon_hp=dragon_hp-damage;
	   			if(reflect>0){ hero_hp -= reflect_damage(&reflect,damage);} //判斷惡龍是否使用反彈
				dragon_death_check(dragon_hp);
	   			break;
			}
			else if(action=="++")
			{
				this_thread::sleep_for(chrono::milliseconds(300));
				cout<<white_text("勇者對惡龍造成了 " + to_string(damage/2) + " 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl;
	   			dragon_hp=dragon_hp-(damage/2);
	   			if(reflect>0){ hero_hp -= reflect_damage(&reflect,damage);}
	   			 //計算第二次勇者攻擊傷害值
				random_num=gen_rand()%14;
				damage_rate=1;
				this_thread::sleep_for(chrono::milliseconds(300));
				if(random_num==0||random_num==1) {damage_rate=0.9;}
				if(random_num==2||random_num==3||random_num==4) {damage_rate=0.95;}
				if(random_num==5||random_num==6||random_num==7) {damage_rate=1.05;}
				if(random_num==8||random_num==9) {damage_rate=1.1;}
				if(random_num==10) {damage_rate=1.8;}
				damage=hero_atk*damage_rate;
				if(weaken>0) {damage*=0.7;}
				cout<<white_text("勇者對惡龍造成了 " + to_string(damage/2) + " 點傷害");
				if(damage_rate==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl<<endl;
	   			dragon_hp=dragon_hp-(damage/2);
                if(reflect>0){ hero_hp -= reflect_damage(&reflect,damage);}
				dragon_death_check(dragon_hp);
	   			break;
			}
			else if(action=="-")
			{
				this_thread::sleep_for(chrono::milliseconds(600));
				cout<<"(防禦)"<<endl<<endl;
				defend++;
				break;
			}
			else if(freeze==true&& ( action=="1" || action == "freeze") )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				freeze=false;
				frozen=2;
				cout<<yellow_text("勇者使用了") + cyan_text("freeze(冰凍)")<<endl;
				freeze_cd=freeze_cd-18;
				break;
			}
			else if(fire==true&& ( action=="2" || action == "fire" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				fire=false;
				cout<<yellow_text("勇者使用了") + red_text("fire(燃燒)")<<endl;
	   			burned=5;
	   			fire_cd=fire_cd-9;
	   			break;
			}
			else if(swipe==true&& ( action=="3" || action == "swipe" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				swipe=false;
	   			cout<<yellow_text("\a勇者使用了swipe(重擊)")<<endl<<endl;
				cout<<"勇者對惡龍造成了 "<<hero_atk*3<<" 點傷害"<<endl;
	    		dragon_hp=dragon_hp-(hero_atk*3);
	    		swipe_cd-=5;

				dragon_death_check(dragon_hp);
	    		break;
			}
			else if(dizzy==true&&( action=="4" || action == "dizzy" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				dizzy=false;
	   			cout<<yellow_text("勇者使用了dizzy(暈眩)")<<endl;
	   			dizzing=4;
	   			dizzy_cd-=13;
	   			break;
			}
			else if(blood==true&&( action=="5" || action == "blood" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				blood=false;
	   			cout<<yellow_text("勇者使用了") + dark_red_text("blood(吸血)")<<endl;
	   			sapping=3;
	   			blood_cd-=27;
	   			break;
			}
			else if(shield==true&&( action=="6" || action == "shield" ) )
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				shield=false;
	   			cout<<yellow_text("勇者使用了shield(護盾)")<<endl;
	   			shielding=3;
	   			shield_cd-=16;
	   			break;
			}
			else if(cure==true&&( action=="7" || action == "cure" ))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				cure=false;
				cout<<yellow_text("勇者使用了") +red_text("cure(治癒)")<<endl;
				gain_hp=hero_maxhp*0.4;
				cout<<endl;
				gain_hp_check(&gain_hp,&hero_hp,&hero_maxhp);
				cout<<"勇者回復了 "<<gain_hp<<" 點生命"<<endl;
				cure_cd-=20;
				break;
			}
			else if(treat==true&&(action=="8"|| action == "treat"))
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				treat=false;
				cout<<yellow_text("勇者使用了") + red_text("treat(回復)")<<endl;
				curing=3;
				treat_cd-=14;
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
				cout<<white_text("勇者對惡龍造成了 "+ to_string(hero_atk*5) +" 點傷害")<<endl;
	    		dragon_hp=dragon_hp-(hero_atk*5);
	    		if(reflect>0){ hero_hp -= reflect_damage(&reflect,hero_atk*5);}
				ap=ap-10;
				this_thread::sleep_for(chrono::milliseconds(1200));
				dragon_death_check(dragon_hp);

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
				lost_hp=hero_atk*0.4;
				this_thread::sleep_for(chrono::milliseconds(900));
				dragon_hp=dragon_hp-lost_hp;
				cout<<endl;
				cout<<italic_text("燃燒對惡龍造成了 "+to_string(lost_hp)+" 點傷害")<<endl;
				if(reflect>0){ hero_hp -= reflect_damage(&reflect,damage);}
				burned--;
				dragon_death_check(dragon_hp);
			}
			if(curing>0)
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				gain_hp=(hero_maxhp-hero_hp)*0.2;
				gain_hp_check(&gain_hp,&hero_hp,&hero_maxhp);
				cout<<endl;
				cout<<italic_text("勇者回復了 "+to_string(gain_hp)+" 點血量")<<endl;
				curing--;
			}
			if(sapping>0)
			{
				this_thread::sleep_for(chrono::milliseconds(900));
				gain_hp=dragon_hp*0.03;
				gain_hp_check(&gain_hp,&hero_hp,&hero_maxhp);
				dragon_hp=dragon_hp-gain_hp;
				cout<<endl;
				cout<<italic_text("勇者將惡龍的 "+to_string(gain_hp)+" 點血量轉換成自己的血量")<<endl;
				sapping--;
				dragon_death_check(dragon_hp);
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
        if(weaken>0)
            weaken--;
        if(reflect>0)
            reflect--;
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
		    damage=dragon_atk*damage_rate; //惡龍傷害計算
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
						cout<<"暈眩失敗!"<<endl<<endl;
						break;
				}
				dizzing--;
			}
			if(dizzied==0)
			{
				random_num=gen_rand()%18;
				if(random_num==0||random_num==1||random_num==2||random_num==3){
					cout<<yellow_text("惡龍使出") + magenta_text("龍之吐息")<<"!"<<endl<<endl;
					cout<<"惡龍對勇者造成了 "<<hero_maxhp/8<<" 點傷害"<<endl;
					hero_hp = hero_hp - hero_maxhp / 8;
				}else if(random_num==4||random_num==5){
					cout<<yellow_text("惡龍使出") + red_text("弱化")<<endl;
					weaken=3;
				}else if(random_num==6||random_num==7){
					cout<<yellow_text("惡龍使出") + cyan_text("反彈")<<endl;
					reflect=2;
				}else if(random_num==8||random_num==9){
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
                        damage=dragon_atk*damage_rate*0.45;
						def_check(&shielding,&defend,&damage);
                        hero_hp-=damage;
                        cout<<white_text("惡龍對勇者造成了 " + to_string(damage) + " 點傷害")<<endl;
                    }
				}else{
                    cout<<white_text("惡龍對勇者造成了 " + to_string(damage) + " 點傷害");
                    if(damage_rate==1.8)
                    {
                        cout<<"\a(暴擊!)"<<endl;
                        ap++;
                        cout<<"勇者怒氣值加1"<<endl;
                    }
                    cout<<endl;
                    def_check(&shielding,&defend,&damage);
                    hero_hp=hero_hp-damage;
                }
			}
			else if(dizzied==1)
			{
				dizzied--;
				cout<<italic_text("惡龍對自己造成了 "+to_string(damage)+" 點傷害");
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
		    	cout<<endl<<dark_red_text("勇者被惡龍擊敗了!");
				this_thread::sleep_for(chrono::milliseconds(500));
				cout<<endl;
				system("pause");
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
		if(poison>0)
        {
            cout<<italic_text("中毒對勇者造成了 "+to_string( (int)(dragon_atk*0.3) )+" 點傷害")<<endl;
            hero_hp-=dragon_atk*0.3;
            poison--;
        }
		if(burned==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("燃燒效果將在下一回合結束時失效")<<endl<<endl;
		}
		if(dizzing==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("暈眩效果將在下一回合結束時失效")<<endl<<endl;
		}
		if(sapping==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("吸血效果將在下一回合結束時失效")<<endl<<endl;
		}
		if(shielding==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("護盾效果將在下一回合結束時失效")<<endl<<endl;
		}
		if(curing==1)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("回復效果將在下一回合結束時失效")<<endl<<endl;
		}
		if(weaken==1)
        {
            this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("弱化效果將在下一回合結束時失效")<<endl<<endl;
        }
        if(reflect==1)
        {
            this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("反彈效果將在下一回合結束時失效")<<endl<<endl;
        }
        if(poison==1)
        {
            this_thread::sleep_for(chrono::milliseconds(200));
			cout<<bold_text("中毒效果將在下一回合結束時失效")<<endl<<endl;
        }
		ap++;
		this_thread::sleep_for(chrono::milliseconds(1500));
	}
}
