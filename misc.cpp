#include "misc.h"

#include <iostream>
#include <thread>
#include <chrono>
#include "render.h"

using namespace std;

void help(){
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
    pause();
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
    pause();
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"怒氣值(AP):"<<endl;
    this_thread::sleep_for(chrono::milliseconds(800));
    cout<<"\t每回合加1，若惡龍該回合暴擊則再加1，到10則可以使用必殺技pow"<<endl<<endl;
    this_thread::sleep_for(chrono::milliseconds(800));
    cout<<"pow(必殺技):"<<endl;
    cout<<"\t使用後怒氣值減10，該回合對惡龍造成攻擊力5倍之傷害，"<<endl;
    cout<<"\t並有70%機率在當前回合定身惡龍"<<endl<<endl;
    cout<<endl;
    pause();
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"惡龍技能:"<<endl<<endl;
    cout<<"龍之吐息:"<<endl<<endl;
    cout<<"\t無視防禦及護盾效果，對勇者造成其最大生命值8%傷害"<<endl<<endl;
    cout<<"弱化:"<<endl<<endl;
    cout<<"\t接下來的3回合，勇者的攻擊力弱化30%，受到傷害提升10%"<<endl<<endl;
    cout<<"反彈:"<<endl<<endl;
    cout<<"\t下一回合，反彈勇者的攻擊傷害之40%，再下一回合反彈2倍傷害"<<endl<<endl;
    cout<<"毒氣:"<<endl<<endl;
    cout<<"\t接下來的5回合(包括當前回合)，對勇者造成攻擊30%之傷害。\n\t中毒傷害無視防禦及護盾效果"<<endl<<endl;
    cout<<"連擊:"<<endl<<endl;
    cout<<"\t該回合對勇者造成連續5次惡龍攻擊力45%之傷害"<<endl<<endl;
    cout<<"毀滅龍盾:"<<endl<<endl;
    cout<<"\t增加自身最大血量20%之護盾，且該護盾只能以物理攻擊破壞。\n\t若勇者在3回合內未能打掉護盾，勇者死亡"<<endl<<endl;
    cout<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    pause();
}

void pause()
{
	cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string dummy;
    cout << "Press any key to continue . . .";
    getline(cin, dummy);
}
