## [Linux Source����ű���ִ�з�ʽ����](http://www.51testing.com/html/38/225738-206878.html)  
�����޸���/etc/profile�ļ�����������������Ч�����������µ�¼����ʱ���뵽��source�����:source /etc/profile  
��source������ѧϰ������������sh ִ�нű������˶Աȣ������ܽ�һ�¡�  
  
source���  
source����Ҳ��Ϊ���������Ҳ����һ������ţ�.��,��bash���ڲ����  
���ܣ�ʹShell����ָ����Shell�����ļ�������ִ���ļ��е��������  
source����ͨ����������ִ�и��޸ĵĳ�ʼ���ļ���ʹ֮������Ч��������ע�������µ�¼��  
�÷���  
source filename �� . filename  
source����(�� C Shell ����)��bash shell����������;������(.)�����Ǹ������(��Bourne Shell����)��source����һ���ơ�  
  
source filename �� sh filename ��./filenameִ�нű��������������أ�  
1.��shell�ű����п�ִ��Ȩ��ʱ����sh filename��./filenameִ�нű���û������á�./filename����Ϊ��ǰĿ¼û����PATH�У�����"."��������ʾ��ǰĿ¼�ġ�  
2.sh filename ���½���һ����shell������shell��ִ�нű��������䣬����shell�̳и�shell�Ļ�������������shell�½��ġ��ı�ı������ᱻ���ظ�shell������ʹ��export��  
3.source filename�����������ʵֻ�Ǽ򵥵ض�ȡ�ű��������������ڵ�ǰshell����ִ�У�û�н����µ���shell����ô�ű����������½����ı��������䶼�ᱣ���ڵ�ǰshell���档  
  
  
����˵����  
1.�½�һ��test.sh�ű�������Ϊ:A=1  
2.Ȼ��ʹ���ִ��chmod +x test.sh  
3.����sh test.sh��echo $A����ʾΪ�գ���ΪA=1��δ���ظ���ǰshell  
4.����./test.sh��Ҳ��һ����Ч��  
5.����source test.sh ���� . test.sh��Ȼ��echo $A�������ʾ1��˵��A=1�ı����ڵ�ǰshell��  
