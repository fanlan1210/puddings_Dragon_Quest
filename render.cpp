#include "render.h"

#include <iostream>
using namespace std;
//改變文字狀態
string blink_text(string text){return "\033[5m" + text + "\033[25m";}
string bold_text(string text){return "\033[1m" + text + "\033[22m";}
string italic_text(string text){return "\033[3m" + text + "\033[23m";}
//改變文字顏色
string black_text(string text){return "\033[38;5;00m" + text + "\033[37m";}
string dark_red_text(string text){return "\033[38;5;01m" + text + "\033[37m";}
string red_text(string text){return "\033[38;5;09m" + text + "\033[37m";}
string green_text(string text){return "\033[38;5;10m" + text + "\033[37m";}
string yellow_text(string text){return "\033[38;5;11m" + text + "\033[37m";}
string blue_text(string text){return "\033[38;5;12m" + text + "\033[37m";}
string magenta_text(string text){return "\033[38;5;13m" + text + "\033[37m";}
string cyan_text(string text){return "\033[38;5;14m" + text + "\033[37m";}
string white_text(string text){return "\033[38;5;15m" + text + "\033[37m";}

//自訂文字色彩(256色)
string custom_text(string text,int color){
	return "\033[38;5;"+to_string(color)+"m" + text + "\033[37m";
	}

//自訂背景色彩(256色)
void custom_background(bool status,int color){
	if (status == true) cout<<"\033[48;5;"+to_string(color)+"m";
	else cout<<"\033[48;5;0m";
}
