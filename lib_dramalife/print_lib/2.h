/*******************************************************
source url: 
  https://www.cnblogs.com/clover-toeic/p/4031618.html
sample:
  printf(L_RED "hello,var:%d\r\n" NONE, var);
*******************************************************/
//terminal_color_dramalife.h
#ifndef TERMINALI_COLOR_DRAMALIFE_H
#define TERMINALI_COLOR_DRAMALIFE_H

//cursor move up
#define MOVEU(x) printf("\033[%dA", (x))
//cursor move down
#define MOVED(x) printf("\033[%dB", (x))
//cursor move left
#define MOVEL(y) printf("\033[%dD", (y))
//cursor move right
#define MOVER(y) printf("\033[%dC",(y))

#endif

