/*******************************************************
source url: 
  https://www.cnblogs.com/clover-toeic/p/4031618.html
sample:
  printf(L_RED "hello,var:%d\r\n" NONE, var);
*******************************************************/
//terminal_color_dramalife.h
#ifndef TERMINALI_COLOR_DRAMALIFE_H
#define TERMINALI_COLOR_DRAMALIFE_H

#define 	CNONE                 "\e[0m"
#define 	CRED                  "\e[0;31m"
#define 	CLRED                "\e[1;31m"
#define 	CGREEN                "\e[0;32m"
#define 	CLGREEN              "\e[1;32m"

#define 	CBLACK                "\e[0;30m"
#define 	CLBLACK              "\e[1;30m"
#define 	CBROWN                "\e[0;33m"
#define 	CYELLOW               "\e[1;33m"
#define 	CBLUE                 "\e[0;34m"
#define 	CLBLUE               "\e[1;34m"
#define 	CPURPLE               "\e[0;35m"
#define 	CLPURPLE             "\e[1;35m"
#define 	CCYAN                 "\e[0;36m"
#define 	CLCYAN               "\e[1;36m"
#define 	CGRAY                 "\e[0;37m"
#define 	CWHITE                "\e[1;37m"
#define 	CBOLD                 "\e[1m"
#define 	UNDERLINE            "\e[4m"
#define 	BLINK                "\e[5m"
#define 	REVERSE              "\e[7m"
#define 	HIDE                 "\e[8m"
#define 	CLEAR                "\e[2J"
#define 	CLRLINE              "\r\e[K" //or "\e[1K\r"

//cursor move up
#define MOVEU(x) printf("\033[%dA", (x))
//cursor move down
#define MOVED(x) printf("\033[%dB", (x))
//cursor move left
#define MOVEL(y) printf("\033[%dD", (y))
//cursor move right
#define MOVER(y) printf("\033[%dC",(y))

#endif

