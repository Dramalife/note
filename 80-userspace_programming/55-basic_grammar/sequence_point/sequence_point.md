[C语言中的序列点](https://www.cnblogs.com/jiqingwu/p/c_sequence_point.html)
[source url - author:jiqingwu](https://www.cnblogs.com/jiqingwu/p/c_sequence_point.html)

> TAG: C, 序列点 
> DATE: 2013-08-07

序列点是程序执行序列中一些特殊的点。 当有序列点存在时，序列点前面的表达式必须求值完毕，并且副作用也已经发生， 才会计算序列点后面的表达式和其副作用。

什么是副作用？举例子来说明。

```
int a = 5;
int b = a ++;
```

在给*b*赋值的语句中，表达式`a++`就有副作用，它返回`a`当前的值5后，要对`a`进行加1的操作。

哪些符号会生成序列点呢？

### "`,`"会生成序列点。

"`,`"用于把多条语句拼接成一条语句。 例如：

```
int b = 5;
++ b;
```

可由"`,`"拼接成

```
int b = 5, ++b;
```

因为"`,`"会产生序列点，所以"`,`"左边的表达式必须先求值，如果有副作用，副作用也会生效。然后才会继续处理"`,`"右边的表达式。

### `&&`和`||`会产生序列点

*逻辑与* `&&` 和*逻辑或* `||` 会产生序列点。

因为`&&`支持短路操作，必须先将`&&`左边的表达式计算完毕，如果结果为`false`，则不必再计算`&&`右边的表达式，直接返回`false`。

`||`和`&&`类似。

### `?:`中的"`?`"会产生序列点

*三元操作符* `?:`中的"`?`"会产生序列点。 如：

```
int a = 5;
int b = a++ > 5? 0 : a;
```

`b`的结果是什么？因为"`?`"处有序列点，其左边的表达式必须先求值完毕。 `a++ > 5`在和5比较时，`a`并没有自增，所以表达式求值为`false`。 因为"`?`"处的序列点，其左边表达式的副作用也要立即生效，即`a`自增1，变为6。 因为"`?`"左边的表达式求值为`false`，所以三元操作符`?:`返回`:`右边的值`a`。 此时`a`的值是6，所以`b`的值是6。

### 序列点之间的执行顺序

[奇怪的C代码](http://user.qzone.qq.com/39088480/blog/1375715161)中给出的例子。

```
int i = 3;
int ans = (++i)+(++i)+(++i);
```

`(++i)+(++i)+(++i)`之间并没有序列点，它们的执行顺序如何呢？ *gcc*编译后，先执行两个`++i`，把它们相加后，再计算第三个`++i`， 再相加。而*Microsoft VC++*编译后，先执行三个`++i`，再相加。 两者得到的结果不同，谁对谁错呢？

谁也没有错。C标准规定：**两个序列点之间的执行顺序是任意的**。 当然这个任意是在不违背操作符优先级和结合特性的前提下的。 这个规定的意义是为编译器的优化留下空间。

知道这个规定，我们就应该避免在一行代码中重复出现被递增的同一个变量， 因为编译器的行为不可预测。 试想如果`(++i)+(++i)+(++i)`换成`(++a)+(++b)+(++c)`（其中`a`、`b`、`c`是不同的变量）， 不管`++a`，`++b`和`++c`的求值顺序谁先谁后，结果都会是一致的。