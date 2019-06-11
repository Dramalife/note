

```bash
# create new branck
git checkout br_to_merge_strace_2squash

git remote add -f strace ~/strace/

git merge -s ours --squash strace/master

git read-tree --prefix=strace5/ -i strace/master

git commit -m"[tools - strace]"

git checkout strace5 

```

