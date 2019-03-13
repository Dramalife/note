/*
Dramalife@live.com
Date:2018.12~2019.2
功能:交替输出A,B（LED闪烁）；
重点：方法2，取反某一bit，缩短代码行数
*/
#include<stdio.h>
void main(void)
{
  unsigned char flag = 0x00;
  while(1)
  {
    //ex.1 print:A,B,A,B...
    if(flag & 0x80)
    {
      flag &= ~0x80;
      printf("A\r\n");
    }
    else
    {
      flag |= 0x80;
      printf("B\r\n");
    }

    //ex.2  print:1,0,1,0...
    printf("%d\r\n",(flag>>3)&0x01);
    flag = ((~flag)&(1<<3)) | (flag&(~(1<<3)));//取反指定bit | 清空指定bit
  }
  return;
}
