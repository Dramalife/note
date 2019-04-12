/*******************************************************
source url: 
  https://www.cnblogs.com/clover-toeic/p/4031618.html
sample:
  printf(L_RED "hello,var:%d\r\n" NONE, var);
*******************************************************/
#define 	CNONE                 "\e[0m"
#define 	CRED                  "\e[0;31m"
#define 	CLRED                "\e[1;31m"
#define 	CGREEN                "\e[0;32m"
#define 	CLGREEN              "\e[1;32m"

#define 	BLACK                "\e[0;30m"
#define 	L_BLACK              "\e[1;30m"
#define 	BROWN                "\e[0;33m"
#define 	YELLOW               "\e[1;33m"
#define 	BLUE                 "\e[0;34m"
#define 	L_BLUE               "\e[1;34m"
#define 	PURPLE               "\e[0;35m"
#define 	L_PURPLE             "\e[1;35m"
#define 	CYAN                 "\e[0;36m"
#define 	L_CYAN               "\e[1;36m"
#define 	GRAY                 "\e[0;37m"
#define 	WHITE                "\e[1;37m"
#define 	BOLD                 "\e[1m"
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


