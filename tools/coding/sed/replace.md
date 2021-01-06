将 1.txt 中的 oldstring 替换为 newstring
```bash
sed -i "s/oldstring/newstring/g" 1.txt
```

递归查找当前目录的c文件和h文件，并将 oldstring 替换为 newstring
```bash
find . -name "*.[h|c]" | xargs sed -i "s/oldstring/newstring/g"
```

将当前目录的文件（非递归）中的 oldstring 替换为 newstring
```bash
ls | xargs sed -i "s/oldstring/newstring/g"
sed -i "s/garden/mirGarden/g" `ls` 
```
