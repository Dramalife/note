> \# note "vim-encrypt" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.09.03;  
\# Update   
\#  
  

### NOT STEP 1. Encrypt file

```bash
vim -x YOUR_FILE
# password required.
```

### NOT STEP 2. Set encryption method

Add to vimrc or input directly.  
```diff
// ~/.vimrc
+ :setlocal cm=blowfish
```

### 3. Make key empty

```
:set key=
```

