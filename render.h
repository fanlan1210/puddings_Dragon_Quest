#ifndef RENDER_H
#define RENDER_H

#include <string>
std::string blink_text(std::string);
std::string bold_text(std::string);
std::string italic_text(std::string);
//改變文字顏色
std::string black_text(std::string);
std::string dark_red_text(std::string);
std::string red_text(std::string);
std::string green_text(std::string);
std::string yellow_text(std::string);
std::string blue_text(std::string);
std::string magenta_text(std::string);
std::string cyan_text(std::string);
std::string white_text(std::string);

//自訂文字色彩(256色)
std::string custom_text(std::string, int = 7);

//自訂背景色彩(256色)
void custom_background(bool, int = 0);

#endif /* RENDER_H */
