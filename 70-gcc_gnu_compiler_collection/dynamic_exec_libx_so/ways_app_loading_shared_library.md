<h2 class="header">
Linux共享库两种加载方式简述
</h2>

Source Url : https://my.oschina.net/u/249511/blog/91999?p=1
<p> &nbsp;&nbsp; &nbsp; 动态库技术通常能减少程序的大小，节省空间，提高效率，具有很高的灵活性，对于升级软件版本也更加容易。与静态库不同，动态库里面的函数不是执行程序本身 的一部分，而是在程序执行时按需载入，其执行代码可以同时在多个程序中共享。由于在编译过程中无法知道动态库函数的地址，所以需要在运行期间查找，这对程 序的性能会有影响。 </p> 
<p> &nbsp; </p> 
<h3> <a rel="nofollow"></a><span>共享库&nbsp;</span> </h3> 
<p> &nbsp;&nbsp; &nbsp; 对于共享库来讲，它只包括<span>2</span>个段：只读的代码段 和可修改的数据段。堆和栈段，只有进程才有。如果你在共享库的函数里，分配了一块内存，这段内存将被算在调用该函数的进程的堆中。代码段由于其内容是对每 个进程都是一样的，所以它在系统中是唯一的，系统只为其分配一块内存，多个进程之间共享。数据段由于其内容对每个进程是不一样的，所以在链接到进程空间 后，系统会为每个进程创建相应的数据段。也就是说如果一个共享库被<span>N</span>个进程链接，当这<span>N</span>个进程同时运行时，同时共享一个代码段，每个进程拥有一个数据段，系统中共有<span>N</span>个数据段。<span>PIC</span>即<span>position independent code，</span>使<span>.so</span>文件的代码段变为真正意义上的共享。如果编译时不加<span>-fPIC,</span>则加载<span>.so</span>文件的代码段时<span>,</span>代码段引用的数据对象需要重定位<span>,&nbsp;</span>重定位会修改代码段的内容<span>,</span>这就造成每个使用这个<span>.so</span>文件代码段的进程在内核里都会生成这个<span>.so</span>文件代码段的<span>copy。</span> </p> 
<p> &nbsp; </p> 
<h4> <a rel="nofollow"></a>加载方式 </h4> 
<p> <span style="font-weight:normal;">&nbsp;&nbsp; &nbsp; 1. 静态加载</span> </p> 
<p> &nbsp; </p> 
<p> &nbsp;&nbsp; &nbsp; 在程序编译的时候加上<span>“</span><span>-l”</span>选项，指定其所依赖的动态库，这个库的名字将记录在<span>ELF</span>文件的<span>.dynamic</span>节。在程序运行时，<span>loader</span>会预先将程序所依赖的所有动态库都加载在进程空间中。 </p> 
<p> &nbsp;&nbsp; &nbsp; 优点：动态库的接口调用简单，可以直接调用。 </p> 
<p> &nbsp;&nbsp; &nbsp; 缺点：动态库的生存周期等于进程的生存周期，其加载时机不灵活。 </p> 
<p> &nbsp; </p> 
<p> &nbsp;&nbsp; &nbsp; 2. 动态加载 </p> 
<p> &nbsp;&nbsp; &nbsp; 在程序中编码来指定加载动态库的时机，经常使用的函数<span>dlopen和dlclose</span>。 </p> 
<p> &nbsp;&nbsp; &nbsp; 优点：动态库加载的时机非常灵活，可以非常细致的定义动态库的生存周期。 </p> 
<p> &nbsp;&nbsp; &nbsp; 缺点<span>：</span>动态库的接口调用起来比较麻烦，同时还要关注动态库的生存周期。 </p> 
<p> ===================================================== </p> 
<p> <span>&nbsp;&nbsp; &nbsp; &nbsp;#include &lt;dlfcn.h&gt;</span> </p> 
<p> 　<span style="font-family:mceinline;">　<strong>void * dlopen( const char *&nbsp;<em>pathname</em>, int&nbsp;<em>mode</em>&nbsp;);</strong></span> </p> 
<p> 　　<strong>函数描述：</strong> </p> 
<p> 　　在dlopen的（）函数以指定模式打开指定的<a href="http://baike.baidu.com/view/1366783.htm" target="_blank" rel="nofollow">动态连接库</a>文件，并返回一个句柄给调用进程。使用dlclose（）来卸载打开的库。 </p> 
<p> 　　<strong>mode</strong>：分为这两种 </p> 
<p> 　　RTLD_LAZY 暂缓决定，等有需要时再解出符号 </p> 
<p> 　　RTLD_NOW 立即决定，返回前解除所有未决定的符号。 </p> 
<p> 　　RTLD_LOCAL &nbsp;不允许导出符号 </p> 
<p> 　　RTLD_GLOBAL 允许导出符号 </p> 
<p> 　　RTLD_NODELETE </p> 
<p> &nbsp;&nbsp; &nbsp; &nbsp;RTLD_NOLOAD </p> 
<p> &nbsp;&nbsp; &nbsp; &nbsp;RTLD_DEEPBIND &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;//具体含义可通过man查看dlopen函数说明 </p> 
<p> 　　<strong>返回值:</strong> </p> 
<p> 　　打开错误返回NULL </p> 
<p> 　　成功，返回库引用 </p> 
<p> 　　编译时候要加入 -ldl (指定dl库) </p> 
<p> &nbsp; </p> 
<p> 　　<span style="font-family:mceinline;"><strong>int dlclose (void *handle);</strong></span> </p> 
<p> &nbsp; </p> 
<p> 　　<strong>函数描述：</strong> </p> 
<p> <strong>　 &nbsp;</strong>dlclose用于关闭指定句柄的动态链接库，只有当此动态链接库的使用计数为0时,才会真正被系统卸载。 </p> 
<p> &nbsp; </p> 
<p> &nbsp; </p> 
<p> &nbsp;&nbsp; &nbsp; 在<span>dlopen</span>一个共享库时， </p> 
<p> <span>a</span>、进程会加载该共享库的<span>代码</span>段和数据段，同时为这个共享库计数加<span>1</span>。 </p> 
<p> <span>b</span>、进程查找该共享库的<span>dynamic</span>节，查看其所依赖的共享库。 </p> 
<p> <span>c</span>、首先检查所依赖库是否已经被加载，如果已被加载，则为这个共享库计数加<span>1。</span>如果未被加载，则加载其<span>代码</span>段和数据段，然后为这个共享库计数加<span>1</span>。 </p> 
<p> <span>d</span>、再查找这些库所依赖的库。最终进程会为每个加载的共享库维护一个依赖的计数。 </p> 
<p> &nbsp; </p> 
<p> &nbsp;&nbsp; &nbsp; 在<span>dlclose</span>共享库时： </p> 
<p> <span>a</span>、首先将该共享库的计数减<span>1</span>，如果该共享库依赖计数为<span>0</span>，则卸载该共享库。 </p> 
<p> <span>b</span>、在<span>dynamic</span>节中，查找其所依赖的共享库。 </p> 
<p> <span>c</span>、为每个共享库的计数减<span>1</span>，如果该共享库依赖计数为<span>0</span>，则卸载该共享库。 </p> 
<p> <span>d</span>、重复上面的步骤。 </p> 
<ul> 
<li> 优点： </li> 
</ul> 
<p> <span>a</span>、可以在程序启动的时候，减少加载库的数量，这样可以加快进程的启动速度和减少加载库的内存使用。 </p> 
<p> <span>b</span>、为进程提供了卸载共享库的机会，这样就可以回收共享库代码段和数据段所占用的内存。 </p> 
<ul> 
<li> 缺点： </li> 
</ul> 
<p> 对于程序员编码来讲，会产生一定的疑惑。一个<span>static</span>的对象的生存周期是贯穿在进程始终的，实际上不是这样。在动态库中的<span>static</span>对象，其生命周期等于该动态库的生命周期。采用静态链接的方式，动态库的生命周期等于进程的生命周期；而采用动态加载的方式，则是不同的。 </p> 
<p> &nbsp; </p> 
<p> 参考： </p> 
<p> 《嵌入式Linux内存与性能详解》 </p> 
<p> &nbsp; </p>
