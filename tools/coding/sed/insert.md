在 所有c文件 的开头 插入 “#include "port4f8.h"”
```bash
ls *.c | xargs sed -i '1i\#include \"port4f8.h\"'
```
