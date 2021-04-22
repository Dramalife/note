#### 类访问修饰符
针对类的外部；
- public	公有成员在程序中类的外部是可访问的,可以不使用任何成员函数来设置和获取公有变量的值;
- protected	（受保护）成员变量或函数与私有成员十分相似，但有一点不同，protected（受保护）成员在派生类（即子类）中是可访问的。
- private	私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。只有类和友元函数可以访问私有成员。
	默认情况下，类的所有成员都是私有的。


### 继承
B类继承A类，B是A的派生类(子类)，A是B的基类(父类)????;

#### 继承导致的基类成员属性变化
|继承方式 \ 基类成员属性	|public		|protected	|private|
|--|--|--|--|
|public继承		|public		|protected	|private|
|protected继承		|protected	|protected	|private|
|private继承		|private	|private	|private|


### 友元(friend)
