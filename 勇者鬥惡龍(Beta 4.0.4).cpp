#include<iostream>
#include<cstdlib>
#include<ctime>
#include<Windows.h>
#include<iomanip>
using namespace std;
int main()
{
	int yhp,yatk,dhp,datk,i,R,D,rr,ff=0,f,c=0,st=0,de=0;
	int chp,hp,ddhp,dd=0,ii=0,cc=0,d=0,b=0,bhp,sh=0,ang=0;
	int freeze=1,fire=1,swipe=1,dizzy=1,blood=1,shield=1,cure=1,treat=1,pow=0;
	int fre=18,fir=8,swi=5,diz=13,blo=27,shi=16,cur=20,tre=14;
	double r;
	string s,yn;
	cout<<" ---------------"<<endl;
	cout<<"|"<<"★☆★☆★☆★"<<" |"<<endl;
	cout<<"|"<<"  勇者鬥惡龍  "<<" |"<<endl;
	cout<<"|"<<"☆★☆★☆★☆"<<" |"<<endl;
	cout<<" ---------------"<<endl;
	cout<<"Beta: 4.0.4"<<endl<<endl;
	cout<<"勇者最大血量: ";
	cin>>yhp;
	cout<<endl<<"勇者基礎攻擊力: ";
	cin>>yatk;
	cout<<endl<<"惡龍最大血量: ";
	cin>>dhp;
	cout<<endl<<"惡龍基礎攻擊力: ";
	cin>>datk;
	cout<<"------------------------------------------------------------"<<endl;
	f=yatk*0.45;
	hp=yhp;
	ddhp=dhp;
	while(1)
	{
		cout<<endl<<"是否需要遊戲說明及技能介紹? | yes / no |"<<endl<<endl;
		cin>>yn;
		if(yn=="yes")
		{
			Sleep(300);
			cout<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			cout<<"遊戲方式:"<<endl;
			Sleep(800);
			cout<<"\t輸入技能之代號即可攻擊"<<endl<<endl;
			Sleep(800);
			cout<<"\t普通攻擊: 造成基礎傷害乘以傷害係數的傷害"<<endl<<endl;
			Sleep(800);
			cout<<"\t雙重普通攻擊: 攻擊2次，但傷害減半，傷害係數各自分開計算"<<endl<<endl;
			Sleep(800);
			cout<<"\t防禦: 該回合不進行任何動作，抵擋住惡龍之60%的傷害"<<endl<<endl;
			Sleep(800);
			cout<<"\t傷害係數: 可能是0.90、0.95、1.00、1.05、1.10或1.80(暴擊)"<<endl<<endl;
			Sleep(800);
			cout<<"\t技能之冷卻時間(CD)到0即可再次使用該技能"<<endl;
			system("pause");
			cout<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			Sleep(300);
			cout<<"技能介紹: (以下每個技能只能使用1次)"<<endl<<endl;
			Sleep(900);
			cout<<"freeze(冰凍 CD-18):"<<endl<<endl;
			cout<<"\t冰凍惡龍3回合(包括當前回合)，使惡龍無法行動"<<endl<<endl;
			Sleep(900);
			cout<<"fire(燃燒 CD-8):"<<endl<<endl;
			cout<<"\t接下來的5回合(包括當前回合)，對惡龍造成攻擊之45%的傷害"<<endl<<endl;
			Sleep(900);
			cout<<"swipe(重擊 CD-5):"<<endl<<endl;
			cout<<"\t該回合對惡龍造成攻擊力3倍之傷害(無法再與暴擊加成)"<<endl<<endl;
			Sleep(900);
			cout<<"dizzy(暈眩 CD-13):"<<endl<<endl;
			cout<<"\t接下來的4回合(包括當前回合)，惡龍有40%的機率傷害自己"<<endl<<endl;
			Sleep(900);
			cout<<"blood(吸血 CD-27):"<<endl<<endl;
			cout<<"\t接下來的3回合(包括當前回合)，將惡龍當前生命之3%，轉成自己的血量"<<endl<<endl;
			Sleep(900);
			cout<<"shield(護盾 CD-16):"<<endl<<endl;
			cout<<"\t接下來的3回合(包括當前回合)，免疫惡龍的所有傷害"<<endl<<endl;
			Sleep(900);
			cout<<"cure(治癒 CD-20):"<<endl<<endl;
			cout<<"\t該回合回復最大生命之40%"<<endl<<endl;
			Sleep(900);
			cout<<"treat(回復 CD-14):"<<endl<<endl;
			cout<<"\t接下來的3回合(包括當前回合)，回復已損生命之20%"<<endl<<endl;
			system("pause");
			cout<<endl;
			cout<<"------------------------------------------------------------"<<endl;
			system("pause");
			cout<<"怒氣值:"<<endl;
			Sleep(800);
			cout<<"\t每回合加1，若惡龍該回合暴擊則再加1，到10則可以使用必殺技pow"<<endl<<endl;
			Sleep(800);
			cout<<"pow(必殺技):"<<endl;
			cout<<"\t使用後怒氣值減10，該回合對惡龍造成攻擊力5倍之傷害，"<<endl;
			cout<<"\t並有70%機率在當前回合定身惡龍"<<endl;
			system("pause");
			cout<<endl;
			/*cout<<"------------------------------------------------------------"<<endl;
			cout<<"惡龍技能:"<<endl;
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
			cout<<endl;*/
			break;
		}
		else if(yn=="no")
			break;
		else
			continue;
	}

	for(i=1;i>0;i++)
	{
		cout<<endl<<"------------------------------------------------------------"<<endl;
	   	cout<<"第 "<<i<<" 回合:"<<endl;
		if(ang>=10&&pow==0)
		{
			pow++;
		}
		cout<<"攻擊: | +  atk|| ++  double atk|| -  defend|"<<endl;
		cout<<"技能: "<<endl;
			cout<<"| 1  "<<left<<setw(6)<<"freeze"<<" CD: "<<left<<setw(2)<<18-fre<<"/18"<<" |";
			cout<<"| 2  "<<left<<setw(6)<<"fire"<<" CD: "<<left<<setw(2)<<8-fir<<"/8 "<<" |";
			cout<<"| 3  "<<left<<setw(6)<<"swipe"<<" CD: "<<left<<setw(2)<<5-swi<<"/5 "<<" |";
			cout<<endl;
			cout<<"| 4  "<<left<<setw(6)<<"dizzy"<<" CD: "<<left<<setw(2)<<13-diz<<"/13"<<" |";
			cout<<"| 5  "<<left<<setw(6)<<"blood"<<" CD: "<<left<<setw(2)<<27-blo<<"/27"<<" |";
			cout<<"| 6  "<<left<<setw(6)<<"shield"<<" CD: "<<left<<setw(2)<<16-shi<<"/16"<<" |";
			cout<<endl;
			cout<<"| 7  "<<left<<setw(6)<<"cure"<<" CD: "<<left<<setw(2)<<20-cur<<"/20"<<" |";
			cout<<"| 8  "<<left<<setw(6)<<"treat"<<" CD: "<<left<<setw(2)<<14-tre<<"/14"<<" |";
		if(pow==1)
			cout<<"| !   pow |";
		cout<<endl<<endl;
		cout<<"怒氣值: "<<ang<<endl<<endl;
		cout<<"勇者血量:"<<yhp<<"/"<<hp<<"  惡龍血量:"<<dhp<<"/"<<ddhp<<endl<<endl;
		if(freeze==0)
		{
			if(fre<18)
				fre++;
			else if(fre==18)
				freeze++;
		}
		if(fire==0)
		{
			if(fir<8)
				fir++;
			else if(fir==8)
				fire++;
		}
		if(swipe==0)
		{
			if(swi<5)
				swi++;
			else if(swi==5)
				swipe++;
		}
		if(dizzy==0)
		{
			if(diz<13)
				diz++;
			else if(diz==13)
				dizzy++;
		}
		if(blood==0)
		{
			if(blo<27)
				blo++;
			else if(blo==27)
				blood++;
		}
		if(shield==0)
		{
			if(shi<16)
				shi++;
			else if(shi==16)
				shield++;
		}
		if(cure==0)
		{
			if(cur<20)
				cur++;
			else if(cur==20)
				cure++;
		}
		if(treat==0)
		{
			if(tre<14)
				tre++;
			else if(tre==14)
				treat++;
		}
		srand(time(NULL));
		R=rand()%14;
		r=0;
		s="";
		switch(R)
		{
		case 0:
		case 1:
			r=0.9;
			break;
		case 2:
		case 3:
		case 4:
			r=0.95;
			break;
		case 5:
		case 6:
		case 7:
			r=1;
			break;
		case 8:
		case 9:
		case 10:
			r=1.05;
			break;
		case 11:
		case 12:
			r=1.1;
			break;
		case 13:
			r=1.8;
			break;
		}
		rr=yatk*r;
		while(cin>>s)
		{
			cout<<endl;
			if(s=="+")
			{
				Sleep(600);
				cout<<"勇者對惡龍造成了 "<<rr<<" 點傷害";
				if(r==1.8)
		    		cout<<"\a(暴擊!)"<<endl;
		    	cout<<endl;
	   			dhp=dhp-rr;
	   			if(dhp<0)
					dhp=0;
				if(dhp==0)
			    {
					Sleep(700);
					cout<<endl<<"勇者擊敗了惡龍!";
					Sleep(500);
					cout<<endl;
					system("pause");
					return 0;
			    }
	   			break;
			}
			else if(s=="++")
			{
				Sleep(300);
				cout<<"勇者對惡龍造成了 "<<rr/2<<" 點傷害";
				if(r==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl;
	   			dhp=dhp-(rr/2);
	   			srand(time(NULL));
				R=rand()%14;
				r=0;
				Sleep(300);
				switch(R)
				{
					case 0:
					case 1:
						r=0.9;
						break;
					case 2:
					case 3:
					case 4:
						r=0.95;
						break;
					case 5:
					case 6:
					case 7:
						r=1;
						break;
					case 8:
					case 9:
					case 10:
						r=1.05;
						break;
					case 11:
					case 12:
						r=1.1;
						break;
					case 13:
						r=1.8;
						break;
				}
				rr=yatk*r;
				cout<<"勇者對惡龍造成了 "<<rr/2<<" 點傷害";
				if(r==1.8)
		    		cout<<"\a(暴擊!)";
		    	cout<<endl;
	   			dhp=dhp-(rr/2);
	   			if(dhp<0)
					dhp=0;
				if(dhp==0)
			    {
					Sleep(700);
					cout<<endl<<"勇者擊敗了惡龍!";
					Sleep(500);
					cout<<endl;
					system("pause");
					return 0;
			    }
	   			break;
			}
			else if(s=="-")
			{
				Sleep(600);
				cout<<"(防禦)"<<endl;
				de++;
				break;
			}
			else if(freeze==1&&s=="1")
			{
				Sleep(900);
				freeze--;
				ff=2;
				cout<<"勇者使用了freeze(冰凍)"<<endl;
				fre=fre-18;
				break;
			}
			else if(fire==1&&s=="2")
			{
				Sleep(900);
				fire--;
				cout<<"勇者使用了fire(燃燒)"<<endl;
	   			ii=5;
	   			fir=fir-8;
	   			break;
			}
			else if(swipe==1&&s=="3")
			{
				Sleep(900);
				swipe--;
	   			cout<<"\a勇者使用了swipe(重擊)"<<endl<<endl;
				cout<<"勇者對惡龍造成了 "<<yatk*3<<" 點傷害"<<endl;
	    		dhp=dhp-(yatk*3);
	    		swi=swi-5;
	    		if(dhp<0)
					dhp=0;
				if(dhp==0)
			    {
					Sleep(700);
					cout<<endl<<"勇者擊敗了惡龍!";
					Sleep(500);
					cout<<endl;
					system("pause");
					return 0;
			    }
	    		break;
			}
			else if(dizzy==1&&s=="4")
			{
				Sleep(900);
				dizzy--;
	   			cout<<"勇者使用了dizzy(暈眩)"<<endl;
	   			d=4;
	   			diz=diz-13;
	   			break;
			}
			else if(blood==1&&s=="5")
			{
				Sleep(900);
				blood--;
	   			cout<<"勇者使用了blood(吸血)"<<endl;
	   			b=3;
	   			blo=blo-27;
	   			break;
			}
			else if(shield==1&&s=="6")
			{
				Sleep(900);
				shield--;
	   			cout<<"勇者使用了shield(護盾)"<<endl;
	   			sh=3;
	   			shi=shi-16;
	   			break;
			}
			else if(cure==1&&s=="7")
			{
				Sleep(900);
				cure--;
				cout<<"勇者使用了cure(治癒)"<<endl;
				c=hp*0.4;
				cout<<endl;
				yhp=yhp+c;
				if(yhp>hp)
				{
					c=c+hp-yhp;
					yhp=hp;
				}
				cout<<"勇者回復了 "<<c<<" 點生命"<<endl;
				cur=cur-20;
				break;
			}
			else if(treat==1&&s=="8")
			{
				Sleep(900);
				treat--;
				cout<<"勇者使用了treat(回復)"<<endl;
				cc=3;
				tre=tre-14;
				break;
			}
			else if(pow==1&&s=="!")
			{
				Sleep(900);
				pow--;
				cout<<"勇者使用了pow(必殺技)"<<endl;
				cout<<"!!!!!!!!!!!!!!!!!!!!!"<<endl;
				cout<<"\a\a\a\a\a\a\a\a\a\a";
				Sleep(800);
				cout<<"勇者對惡龍造成了 "<<yatk*5<<" 點傷害"<<endl;
	    		dhp=dhp-(yatk*5);
	    		if(dhp<0)
					dhp=0;
				ang=ang-10;
				Sleep(1200);
				if(dhp==0)
			    {
					Sleep(700);
					cout<<endl<<"勇者擊敗了惡龍!";
					Sleep(500);
					cout<<endl;
					system("pause");
					return 0;
			    }
			    D=0;
				srand(time(NULL));
				D=rand()%10;
				Sleep(500);
				cout<<endl;
				switch(D)
				{
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						st++;
						cout<<"定身成功\!"<<endl;
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
		if(ii>0||cc>0||b>0)
		{
			if(ii>0)
			{
				Sleep(900);
				dhp=dhp-f;
				if(dhp<0)
					dhp=0;
				cout<<endl;
				cout<<"燃燒對惡龍造成了 "<<f<<" 點傷害"<<endl;
				ii--;
				if(dhp==0)
			    {
					Sleep(700);
					cout<<endl<<"勇者擊敗了惡龍!";
					Sleep(500);
					cout<<endl;
					system("pause");
					return 0;
			    }
			}
			if(cc>0)
			{
				Sleep(900);
				chp=(hp-yhp)*0.2;
				yhp=yhp+chp;
				if(yhp>hp)
				{
					chp=chp+hp-yhp;
					yhp=hp;
				}
				cout<<endl;
				cout<<"勇者回復了 "<<chp<<" 點血量"<<endl;
				cc--;
			}
			if(b>0)
			{
				Sleep(900);
				bhp=dhp*0.03;
				yhp=yhp+bhp;
				if(yhp>hp)
				{
					bhp=bhp+hp-yhp;
					yhp=hp;
				}
				dhp=dhp-bhp;
				if(dhp<0)
					dhp=0;
				cout<<endl;
				cout<<"勇者將惡龍的 "<<bhp<<" 點血量轉換成自己的血量"<<endl;
				b--;
				if(dhp==0)
			    {
					Sleep(700);
					cout<<endl<<"勇者擊敗了惡龍!";
					Sleep(500);
					cout<<endl;
					system("pause");
					return 0;
			    }
			}
			cout<<endl;
		}
		if(st==1)
		{
			st--;
			continue;
		}
		srand(time(NULL));
		R=rand()%14;
		r=0;
		switch(R)
		{
			case 0:
			case 1:
				r=0.9;
				break;
			case 2:
			case 3:
			case 4:
				r=0.95;
				break;
			case 5:
			case 6:
			case 7:
				r=1;
				break;
			case 8:
			case 9:
			case 10:
				r=1.05;
				break;
			case 11:
			case 12:
				r=1.1;
				break;
			case 13:
				r=1.8;
				break;
		}
		if(ff==0)
		{
			Sleep(900);
		    rr=datk*r;
		   	if(d>0)
			{
				D=0;
				srand(time(NULL));
				D=rand()%5;
				Sleep(500);
				if(s=="4")
					cout<<endl;
				switch(D)
				{
					case 0:
					case 1:
						dd=1;
						cout<<"暈眩成功\!"<<endl<<endl;
						break;
					case 2:
					case 3:
					case 4:
						cout<<"暈眩失敗!"<<endl<<endl;
						break;
				}
				d--;
			}
			if(dd==0)
			{
				if(sh==0&&de==1)
				{
					cout<<"勇者防禦住了 "<<int(rr*0.6)<<" 點傷害"<<endl<<endl;
					rr=rr*0.4;
					de--;
				}
				else if(sh>0&&de==0)
				{
					cout<<"(護盾吸收了 "<<rr<<" 點傷害)"<<endl;
					rr=0;
					sh--;
				}
				else if(sh>0&&de==1)
				{
					cout<<"勇者防禦住了 0 點傷害"<<endl<<endl;
					de--;
					cout<<"(護盾吸收了 "<<rr<<" 點傷害)"<<endl;
					rr=0;
					sh--;
				}
				cout<<"惡龍對勇者造成了 "<<rr<<" 點傷害";
			    if(r==1.8)
			    {
			    	cout<<"\a(暴擊!)"<<endl;
					ang++;
					cout<<"勇者怒氣值加1"<<endl;
				}
				cout<<endl;
				yhp=yhp-rr;
			}
			else if(dd==1)
			{
				dd--;
				cout<<"惡龍對自己造成了 "<<rr<<" 點傷害";
			    if(r==1.8)
			    {
			    	cout<<"\a(暴擊!)"<<endl;
					ang++;
				}
				cout<<endl;
				dhp=dhp-rr;
			}
			if(dhp<0)
				dhp=0;
			if(dhp==0)
			{
				Sleep(700);
				cout<<endl<<"勇者擊敗了惡龍!"<<endl<<endl;
				Sleep(500);
				cout<<endl;
				system("pause");
				return 0;
	   		}
		    if(yhp<0)
				yhp=0;
		    if(yhp<=0)
		    {
				Sleep(700);
		    	cout<<endl<<"勇者被惡龍擊敗了!";
				Sleep(500);
				cout<<endl;
				system("pause");
				return 0;
		    }
		    cout<<endl;
		}
		else if(ff==1)
		{
			Sleep(200);
			cout<<"惡龍將在下一回合解凍"<<endl<<endl;
			ff--;
		}
		else
		{
			Sleep(200);
			cout<<"惡龍將在 "<<ff<<" 回合後解凍"<<endl<<endl;
			ff--;
		}
		if(ii==1)
		{
			Sleep(200);
			cout<<"燃燒效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(d==1)
		{
			Sleep(200);
			cout<<"暈眩效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(b==1)
		{
			Sleep(200);
			cout<<"吸血效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(sh==1)
		{
			Sleep(200);
			cout<<"護盾效果將在下一回合結束時失效"<<endl<<endl;
		}
		if(cc==1)
		{
			Sleep(200);
			cout<<"回復效果將在下一回合結束時失效"<<endl<<endl;
		}
		ang++;
		Sleep(1500);
	}
}
