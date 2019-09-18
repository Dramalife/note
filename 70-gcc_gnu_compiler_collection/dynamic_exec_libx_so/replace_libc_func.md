source url : https://my.oschina.net/lgl88911/blog/147901
<p><strong>摘要：</strong></p> 
<p>本文介绍如何替换glibc中的内存分配函数为自定义的内存分配函数的方法，可以方便调试内存分配，和查找内存管理错误而产生的问题。本文并不介绍如何实现内存管理，只是针对如何替换和替换Libc内存管理函数遇到的问题进行分析。</p> 
<p><strong>正文：</strong></p> 
<p><strong>1． 问题提出</strong></p> 
<p>嵌入式Linux平台下开发的项目，通常都是使用glibc提供的内存管理。如果涉及到外购和合作开发，通常得到的都是lib，而这些lib也都是使用glibc进行内存管理。因为大规模操作内存，因此难免会出现内存泄露，访问越界等问题，针对于此很多前辈都开发了不少的检查工具,例如effence, dmalloc等等，这些都是替换掉libc的内存管理函数，以自己特殊的内存管理来查找内存方面引起的问题。同样我们也可以针对自己应用的特点写出内存管理函数并替换掉libc的内存管理函数。</p> 
<p><strong>2． 替换函数</strong></p> 
<p>实现以下函数来替换掉Libc中原有的内存管理函数如下：</p> 
<div> 
 <pre><code><span style="color: #0000ff">extern</span> “C” <span style="color: #0000ff">void</span> *memalign(size_t align, size_t size)

{

}

<span style="color: #0000ff">extern</span> “C” <span style="color: #0000ff">void</span> *<span style="color: #0000ff">malloc</span>(size_t size)

{

}

<span style="color: #0000ff">extern</span> “C” <span style="color: #0000ff">void</span> <span style="color: #0000ff">free</span>(<span style="color: #0000ff">void</span> *ptr)

{

}

<span style="color: #0000ff">extern</span> “C” <span style="color: #0000ff">void</span> *realloc(<span style="color: #0000ff">void</span> *oldBuf, size_t newSize)

{

}

<span style="color: #0000ff">extern</span> “C” <span style="color: #0000ff">void</span> *<span style="color: #0000ff">calloc</span>(size_t nelem, size_t elsize)

{

}

<span style="color: #0000ff">extern</span> “C” <span style="color: #0000ff">void</span> *valloc (size_t size)

{

}</code></pre> 
</div> 
<br> 
<p>如果有用到C++实现以下函数：</p> 
<div> 
 <pre><code><span style="color: #0000ff">void</span> *operator new(<span style="color: #0000ff">unsigned</span> <span style="color: #0000ff">int</span> size)

{

}

<span style="color: #0000ff">void</span> operator delete(<span style="color: #0000ff">void</span> *ptr)

{

}</code></pre> 
</div> 
<br> 
<p><strong>3． 有关问题的解决</strong></p> 
<p>在使用动态链接libc的情况下，只用实现章节2中的函数即可。</p> 
<p>在使用静态链接libc的情况下，因为malloc, free, realloc, memalign在glibc中没有以WEAK声明，因此静态链接无法替换掉这几个函数，会在链接过程中报重复定义，可采取以下两种方法处理：</p> 
<p><strong>a. malloc/free/realloc使用malloc hook的方法，不过这样代码要注意多线程安全</strong></p> 
<p><strong>b. 将libc.a内的相关符号转换为weak</strong></p> 
<ul> 
 <li>找到链接使用的libc</li> 
 <li>ar x libc.a malloc.o&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 提取malloc.o</li> 
 <li>objcopy –W malloc malloc.o&nbsp;&nbsp; 符号weak</li> 
 <li>objcopy –W free malloc.o</li> 
 <li>objcopy –W realloc malloc.o</li> 
 <li>objcopy –W memalign malloc.o</li> 
 <li>ar –r libc.a malloc.o&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 将malloc.o替换回libc</li> 
 <li>使用新的Libc.a进行链接即可</li> 
</ul> 
<p>嵌入式上使用交叉编译器ar和objcopy前添加正确的前缀，例如arm-gcc-ar</p> 
<p><strong>结束语：</strong></p> 
<p>本文提供了在静态编译下libc下替换内存管理函数的方法，方便的替换自己的内存管理.</p>
