

- List Branchs
```bash
# all
git branch -a

# remote
git branch -r

# local
git branch
```


- Create Branch
```bash
git branch BRANCH_NAME

# create & switch to
git checkout -b BRANCH_NAME
```

- Create Blank Branch
```bash
git checkout --orphan br_master_blank
```


- Delete Branch
```bash
git branch -d BRANCH_NAME
git branch -D BRANCH_NAME

# del remote
git push origin --delete BRANCH_NAME
```
