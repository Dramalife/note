/*******************************************************
 * terminal_color_dramalife.h
 *
 * REF url: 
 *   https://www.cnblogs.com/clover-toeic/p/4031618.html
 * sample:
 *   printf(L_RED "hello,var:%d\r\n" NONE, var);
 *
 * Init :
 * Update : 2020.03.30
 *	version-5002;
 *
 *******************************************************/
#ifndef TERMINALI_COLOR_DRAMALIFE_H
#define TERMINALI_COLOR_DRAMALIFE_H



/********************************
 *	Version	Code		*
 ********************************/
//#define LIB_DRAMALIFE_C_COLOR_VERSION	5001
#define LIB_DRAMALIFE_C_COLOR_VERSION	5002



/********************************
 * LIB_DRAMALIFE_C_COLOR_VERSION=5002
 * DLC - Colours for Dramalife(DL) Language C(C)
 ********************************/
#if LIB_DRAMALIFE_C_COLOR_VERSION == 5002
#define	DLC_NONE	"\e[0m"
#define	DLC_RED         "\e[0;31m"
#define	DLC_LRED        "\e[1;31m"
#define	DLC_GREEN       "\e[0;32m"
#define	DLC_LGREEN      "\e[1;32m"
#define	DLC_BLACK       "\e[0;30m"
#define	DLC_LBLACK      "\e[1;30m"
#define	DLC_BROWN       "\e[0;33m"
#define	DLC_YELLOW      "\e[1;33m"
#define	DLC_BLUE        "\e[0;34m"
#define	DLC_LBLUE       "\e[1;34m"
#define	DLC_PURPLE      "\e[0;35m"
#define	DLC_LPURPLE     "\e[1;35m"
#define	DLC_CYAN        "\e[0;36m"
#define	DLC_LCYAN       "\e[1;36m"
#define	DLC_GRAY        "\e[0;37m"
#define	DLC_WHITE       "\e[1;37m"
#define	DLC_BOLD        "\e[1m"
#define	DLC_UNDERLINE   "\e[4m"
#define	DLC_BLINK       "\e[5m"
#define	DLC_REVERSE     "\e[7m"
#define	DLC_HIDE        "\e[8m"
#define	DLC_CLEAR       "\e[2J"
#define	DLC_CLRLINE	"\r\e[K"
// For compatiable with v5001
#define 	CNONE                DLC_NONE	
#define 	CRED                 DLC_RED         
#define 	CLRED                DLC_LRED        
#define 	CGREEN               DLC_GREEN       
#define 	CLGREEN              DLC_LGREEN      
#define 	CBLACK               DLC_BLACK       
#define 	CLBLACK              DLC_LBLACK      
#define 	CBROWN               DLC_BROWN       
#define 	CYELLOW              DLC_YELLOW      
#define 	CBLUE                DLC_BLUE        
#define 	CLBLUE               DLC_LBLUE       
#define 	CPURPLE              DLC_PURPLE      
#define 	CLPURPLE             DLC_LPURPLE     
#define 	CCYAN                DLC_CYAN        
#define 	CLCYAN               DLC_LCYAN       
#define 	CGRAY                DLC_GRAY        
#define 	CWHITE               DLC_WHITE       
#define 	CBOLD                DLC_BOLD        
#define 	UNDERLINE            DLC_UNDERLINE   
#define 	BLINK                DLC_BLINK       
#define 	REVERSE              DLC_REVERSE     
#define 	HIDE                 DLC_HIDE        
#define 	CLEAR                DLC_CLEAR       
#define 	CLRLINE              DLC_CLRLINE	
#endif


/**************************************
 * LIB_DRAMALIFE_C_COLOR_VERSION=5001 *
 * OLD VERSION !		      *
 **************************************/
#if LIB_DRAMALIFE_C_COLOR_VERSION == 5001
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
#endif



//cursor move up
#define MOVEU(x) printf("\033[%dA", (x))
//cursor move down
#define MOVED(x) printf("\033[%dB", (x))
//cursor move left
#define MOVEL(y) printf("\033[%dD", (y))
//cursor move right
#define MOVER(y) printf("\033[%dC",(y))

#endif

