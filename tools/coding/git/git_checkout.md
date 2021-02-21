> note "git checkout" related file
> Copyright (C) 2019 Dramalife@live.com
>
> This file is part of [note](https://github.com/Dramalife/note.git)
>
> note is distributed in the hope that it will be useful, but
> WITHOUT ANY WARRANTY; without even the implied warranty of
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
>
> Init : 2019.08.22, Checkout remote branch;
> Update : 2021.02.21, "git checkout -b ..." & "git checkout -t ..."
>




- man git checkout


- git checkout -b|-B <new_branch> [<start point>]
```bash
git checkout -b BRANCH_NAME origin/BRANCH_NAME
```

- git checkout -t
```bash
#           If no -b option is given, the name of the new branch will be derived from the remote-tracking branch, by looking at
#           the local part of the refspec configured for the corresponding remote, and then stripping the initial part up to the
#           "*". This would tell us to use hack as the local branch when branching off of origin/hack (or remotes/origin/hack, or
#           even refs/remotes/origin/hack). If the given name has no slash, or the above guessing results in an empty name, the
#           guessing is aborted. You can explicitly give a name with -b in such a case.

git checkout -t origin/BRANCH_NAME
```
