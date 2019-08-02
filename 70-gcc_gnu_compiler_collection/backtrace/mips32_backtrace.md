<div class="content" id="articleContent">
<div class="ad-wrap">
source : https://my.oschina.net/lgl88911/blog/221036
</div>
<p>在嵌入式开发过程中，经常会遇到出问题了想知道函数调用关系，不过目前我用到的toochain的Libc提供的backtrace只能出来2层，所以就只好另外写代码来backtrace。目前嵌入式mips32在gcc编译器上的ABI都遵循o32, 从一段反汇编简单看一下o32 ABI的帧结构</p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>0040064c&nbsp;&lt;Test2&gt;:
&nbsp;&nbsp;40064c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;27bdffe0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;sp,sp,-32&nbsp;&nbsp;&nbsp;&nbsp;##mips不会自动处理sp，这里进行函数堆栈开辟
&nbsp;&nbsp;400650:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;afbf001c&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ra,28(sp)&nbsp;&nbsp;&nbsp;&nbsp;##将ra入栈
&nbsp;&nbsp;400654:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;afbe0018&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;s8,24(sp)&nbsp;&nbsp;&nbsp;&nbsp;##其它寄存器入栈
&nbsp;&nbsp;400658:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03a0f021&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;move&nbsp;&nbsp;&nbsp;&nbsp;s8,sp
&nbsp;&nbsp;40065c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0c100184&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;jal&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;400610&nbsp;&lt;Test1&gt;
&nbsp;&nbsp;400660:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00000000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;nop
&nbsp;&nbsp;400664:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;24420001&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;v0,v0,1
&nbsp;&nbsp;400668:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03c0e821&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;move&nbsp;&nbsp;&nbsp;&nbsp;sp,s8
&nbsp;&nbsp;40066c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8fbf001c&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ra,28(sp)&nbsp;&nbsp;&nbsp;&nbsp;##从堆栈取出ra
&nbsp;&nbsp;400670:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8fbe0018&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;s8,24(sp)&nbsp;&nbsp;&nbsp;&nbsp;##其它寄存器出栈
&nbsp;&nbsp;400674:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;27bd0020&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;sp,sp,32&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;##恢复堆栈
&nbsp;&nbsp;400678:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03e00008&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;jr&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ra&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;##跳回到函数调用处
&nbsp;&nbsp;40067c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00000000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;nop</code></pre> 
<p></p> 
<p>从上面看堆栈中大约保存的就是各个要保护的寄存器内容，但不同的函数保护的内容不一样，因此帧内数据不一定一样，例如下面这个函数就不用保存ra</p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>00400610&nbsp;&lt;Test1&gt;:
&nbsp;&nbsp;400610:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;27bdffe8&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;sp,sp,-24
&nbsp;&nbsp;400614:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;afbe0014&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;s8,20(sp)
&nbsp;&nbsp;400618:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03a0f021&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;move&nbsp;&nbsp;&nbsp;&nbsp;s8,sp
&nbsp;&nbsp;40061c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;24020003&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;li&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;v0,3
&nbsp;&nbsp;400620:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;afc20008&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;v0,8(s8)
&nbsp;&nbsp;400624:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;24020004&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;li&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;v0,4
&nbsp;&nbsp;400628:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;afc2000c&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;v0,12(s8)
&nbsp;&nbsp;40062c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8fc30008&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;v1,8(s8)
&nbsp;&nbsp;400630:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8fc2000c&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;v0,12(s8)
&nbsp;&nbsp;400634:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00621021&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addu&nbsp;&nbsp;&nbsp;&nbsp;v0,v1,v0
&nbsp;&nbsp;400638:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03c0e821&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;move&nbsp;&nbsp;&nbsp;&nbsp;sp,s8
&nbsp;&nbsp;40063c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8fbe0014&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;s8,20(sp)
&nbsp;&nbsp;400640:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;27bd0018&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;sp,sp,24
&nbsp;&nbsp;400644:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03e00008&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;jr&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ra
&nbsp;&nbsp;400648:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;00000000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;nop</code></pre> 
<p></p> 
<p>在C/C++函数中，启动程序函数，再向上就是汇编了, 这是能backtrace C/C++的最后一层<br></p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>00400440&nbsp;&lt;__start&gt;:
&nbsp;&nbsp;400440:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3c1c0042&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lui&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;gp,0x42&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;##Load&nbsp;GOT
&nbsp;&nbsp;400444:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;279c8920&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;gp,gp,-30432
&nbsp;&nbsp;400448:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0000f821&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;move&nbsp;&nbsp;&nbsp;&nbsp;ra,zero
&nbsp;&nbsp;40044c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3c040040&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lui&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a0,0x40
&nbsp;&nbsp;400450:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;248406c0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;a0,a0,1728
&nbsp;&nbsp;400454:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8fa50000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a1,0(sp)
&nbsp;&nbsp;400458:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;27a60004&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;a2,sp,4
&nbsp;&nbsp;40045c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2401fff8&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;li&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;at,-8
&nbsp;&nbsp;400460:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03a1e824&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sp,sp,at
&nbsp;&nbsp;400464:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;27bdffe0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;sp,sp,-32
&nbsp;&nbsp;400468:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3c070040&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lui&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a3,0x40
&nbsp;&nbsp;40046c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;24e70710&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;a3,a3,1808
&nbsp;&nbsp;400470:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3c080040&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lui&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;t0,0x40
&nbsp;&nbsp;400474:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;250807b8&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;t0,t0,1976
&nbsp;&nbsp;400478:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;afa80010&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;t0,16(sp)
&nbsp;&nbsp;40047c:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;afa20014&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;v0,20(sp)</code></pre> 
<p></p> 
<p>从上面的分析来看，</p> 
<p>1. 进入函数最先做的事情就是开辟堆栈：</p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>27bdffe8&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;addiu&nbsp;&nbsp;&nbsp;sp,sp,-24</code></pre> 
<p></p> 
<p>2.如果ra要保护,则需要入栈</p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>afbf001c&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sw&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ra,28(sp)</code></pre> 
<p></p> 
<p>3. 最顶层的C/C++函数是要准备GOT的</p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>&nbsp;400440:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3c1c0042&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lui&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;gp,0x42</code></pre> 
<p></p> 
<p>4.一个函数结束，需要跳回到ra指向的地址</p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>400644:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;03e00008&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;jr&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ra</code></pre> 
<p></p> 
<p>有了以上三点，就可以backtrace了：</p> 
<pre class="brush:cpp;toolbar: true; auto-links: false;"><code>#include&nbsp;"syscall.h"
#define&nbsp;abs(X)&nbsp;((X)&gt;=0?(X):(-(X)))

int&nbsp;autobt_mips32(void&nbsp;**btbuffer,int&nbsp;size)
{
&nbsp;&nbsp;&nbsp;&nbsp;unsigned&nbsp;long&nbsp;*addr;
&nbsp;&nbsp;&nbsp;&nbsp;unsigned&nbsp;long&nbsp;*ra;
&nbsp;&nbsp;&nbsp;&nbsp;unsigned&nbsp;long&nbsp;*sp;
&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;unsigned&nbsp;int&nbsp;raoffset;
&nbsp;&nbsp;&nbsp;&nbsp;unsigned&nbsp;int&nbsp;stacksize;
&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;unsigned&nbsp;int&nbsp;bt;

&nbsp;&nbsp;&nbsp;&nbsp;if(!btbuffer&nbsp;||&nbsp;size&lt;0)
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return&nbsp;-1;
&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;//获取当前函数的ra和sp
&nbsp;&nbsp;&nbsp;&nbsp;__asm__&nbsp;__volatile__(
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"move&nbsp;%0,&nbsp;$ra\n"
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"move&nbsp;%1,&nbsp;$sp\n"
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:"=r"(ra),"=r"(sp)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;);

&nbsp;&nbsp;&nbsp;&nbsp;//因为当前函数是叶子函数，所以ra不会再被占用，因此不会将ra入栈，所以不用去找ra的在sp中的偏移地址,因此ra中的值就是调用autobt_mips32的下一条指令地址

&nbsp;&nbsp;&nbsp;&nbsp;stacksize&nbsp;=&nbsp;0;
&nbsp;&nbsp;&nbsp;&nbsp;for(addr=(unsigned&nbsp;long*)autobt_mips32;;++addr)&nbsp;//从当前函数的起始地址找堆栈大小
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if((*addr&amp;0xffff0000)&nbsp;==&nbsp;0x2fbd0000)&nbsp;&nbsp;&nbsp;&nbsp;//0x2fbd&nbsp;is&nbsp;"addiu&nbsp;sp,sp"，前面分析过，这个指令是为函数开辟堆栈的
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//当发现是开辟堆栈的指令时，取出堆栈大小
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;stacksize&nbsp;=&nbsp;abs((short)(*addr&amp;0xffff));&nbsp;&nbsp;&nbsp;&nbsp;//mips堆栈是负增长，所以要取绝对值
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if(stacksize&nbsp;!=&nbsp;0)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;break;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;else&nbsp;if(*addr&nbsp;==&nbsp;0x3e00008)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//0x3e00008&nbsp;is&nbsp;"jr&nbsp;ra"
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//发现返回指令，说明已经找到头了，退出查找
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;break;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;}

&nbsp;&nbsp;&nbsp;&nbsp;//找到了autobt_mips32使用堆栈的大小，就可以算出autobt_mips32调用者的堆栈指针
&nbsp;&nbsp;&nbsp;&nbsp;sp&nbsp;=(unsigned&nbsp;long&nbsp;*)((unsigned&nbsp;long)sp&nbsp;+&nbsp;stacksize);

&nbsp;&nbsp;&nbsp;&nbsp;//做backtrace
&nbsp;&nbsp;&nbsp;&nbsp;for(bt=0;bt&lt;size&amp;&amp;ra;bt++)
&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;btbuffer[bt]=ra;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;raoffset&nbsp;=&nbsp;0;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;stacksize&nbsp;=&nbsp;0;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for(addr=ra;&nbsp;raoffset==0||stacksize==0;&nbsp;addr--)&nbsp;&nbsp;&nbsp;&nbsp;//从ra开始向上找
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;switch(*addr&amp;0xffff0000)&nbsp;&nbsp;&nbsp;&nbsp;//get&nbsp;instruction
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;case&nbsp;0x27bd0000:&nbsp;&nbsp;&nbsp;&nbsp;//找到开辟堆栈的指令，保存堆栈的值
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;stacksize&nbsp;=&nbsp;abs((short)(*addr&amp;0xffff));
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;break;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;case&nbsp;0xafbf0000:&nbsp;&nbsp;&nbsp;&nbsp;//从前面的分析可以知道0xafbf&nbsp;是"sw&nbsp;ra&nbsp;(XX)sp"，这里就是ra存放的偏移地址
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;raoffset&nbsp;=&nbsp;(short)(*addr&amp;0xffff);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;break;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;case&nbsp;0x3c1c0000:&nbsp;&nbsp;&nbsp;&nbsp;//找到C/C++&nbsp;函数的最后一层,&nbsp;停止&nbsp;backtrace。0x3c1c&nbsp;是"lui&nbsp;gp"
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return&nbsp;bt+1;
&nbsp;&nbsp;&nnbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;break;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;default:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;break;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//设置上一层调用者的调用本层函数的返回地址（ra的地址在上一层函数中）和堆栈地址&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ra&nbsp;=(unsigned&nbsp;long&nbsp;*)((unsigned&nbsp;long)ra&nbsp;+&nbsp;raoffset);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sp&nbsp;=(unsigned&nbsp;long&nbsp;*)((unsigned&nbsp;long)sp&nbsp;+&nbsp;stacksize);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;}

&nbsp;&nbsp;&nbsp;&nbsp;return&nbsp;bt;
}</code></pre> 
<p></p> 
<p>当想要知道一个函数的backtrace时，可以在这个函数内call autobt_mips32, 函数的返回值就是backtrace的层数，而btbuffer中保存的是backtrace的地址，根据这些地址和运行程序的反汇编，很容易就可以对应出实际函数的调用关系<br></p> 
<p><br></p> 

<p><br></p>
<div class="ad-wrap" style="margin-top: 12px;">
<div id="blog-title-ad" data-traceid="blog_ali" data-tracepid="blogdown" style="">

</div>
