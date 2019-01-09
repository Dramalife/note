```flow
st=>start: 注册印象笔记
e=>end: 您可以使用markdown
op1=>operation: 登录印象笔记
op2=>operation: 购买并登录马克飞象
cond=>condition: 是否已经购买并登录了马克飞象?

st->op1->cond
cond(yes)->e
cond(no)->op2->e
```
