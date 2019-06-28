[source url](https://www.cnblogs.com/memory4young/p/git-command-auto-completion.html)  

```bash
#
# note xxx-xxx related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
```

### 1. compile
see tools/gcc/git_compile.md

### 2. cmd complete

```bash
cd git/contrib/completion/

cp git-completion.bash ~/.git-completion.bash

echo "source ~/.git-completion.bash" >> ~/.bashrc
```

