dramalife@Lenovo:~/note$ git pull
Auto-merging tools/gcc/git_compile.sh
CONFLICT (add/add): Merge conflict in tools/gcc/git_compile.sh
Auto-merging tools/fs/linux_mount_smb.md
CONFLICT (content): Merge conflict in tools/fs/linux_mount_smb.md
Auto-merging README.md
CONFLICT (content): Merge conflict in README.md
Auto-merging 80-userspace_programming/script/encrypt-FloderPasswdOutpath.sh
CONFLICT (add/add): Merge conflict in 80-userspace_programming/script/encrypt-FloderPasswdOutpath.sh
Auto-merging 80-userspace_programming/script/decrypt.sh
CONFLICT (add/add): Merge conflict in 80-userspace_programming/script/decrypt.sh
Auto-merging 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/server.c
CONFLICT (add/add): Merge conflict in 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/server.c
Auto-merging 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/readme.txt
CONFLICT (add/add): Merge conflict in 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/readme.txt
Auto-merging 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.h
CONFLICT (add/add): Merge conflict in 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.h
Auto-merging 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/client.c
CONFLICT (add/add): Merge conflict in 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/client.c
Auto-merging 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/Makefile
CONFLICT (add/add): Merge conflict in 80-userspace_programming/com_unix_sock/dlpi_dramalifepi/Makefile
Auto-merging 70-gcc_gnu_compiler_collection/README.md
CONFLICT (add/add): Merge conflict in 70-gcc_gnu_compiler_collection/README.md
Auto-merging 50-books/00-note/l2tp_layer_two_tunneling_protocol/readme.md
Automatic merge failed; fix conflicts and then commit the result.
dramalife@Lenovo:~/note$ git status
On branch master
Your branch and 'origin/master' have diverged,
and have 258 and 280 different commits each, respectively.
  (use "git pull" to merge the remote branch into yours)

You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Changes to be committed:

	modified:   50-books/00-note/l2tp_layer_two_tunneling_protocol/readme.md
	new file:   50-books/00-note/l2tp_layer_two_tunneling_protocol/xl2tpd_install.htm
	new file:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.c
	new file:   81-kernel_programming/networks/forward.md
	new file:   81-kernel_programming/networks/network_model.md
	new file:   90-operating_system/ssh_login_via_key.txt
	new file:   tools/clear_file.sh
	new file:   tools/clone_lcd_tft.sh
	new file:   tools/clone_libpcap.sh
	new file:   tools/clone_xl2tpd.sh
	new file:   tools/coding/git/del_file_commit_history.sh
	new file:   tools/coding/git/local_clone.sh
	new file:   tools/gcc/libpcap_compile.md
	new file:   tools/gcc/xl2tpd_compile.md
	new file:   tools/lcd_show_pic.sh

Unmerged paths:
  (use "git add <file>..." to mark resolution)

	both added:      70-gcc_gnu_compiler_collection/README.md
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/Makefile
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/client.c
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.h
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/readme.txt
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/server.c
	both added:      80-userspace_programming/script/decrypt.sh
	both added:      80-userspace_programming/script/encrypt-FloderPasswdOutpath.sh
	both modified:   README.md
	both modified:   tools/fs/linux_mount_smb.md
	both added:      tools/gcc/git_compile.sh

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	tmp/


dramalife@Lenovo:~/note$ git checkout --ours  ./*


dramalife@Lenovo:~/note$ git status
On branch master
Your branch and 'origin/master' have diverged,
and have 258 and 280 different commits each, respectively.
  (use "git pull" to merge the remote branch into yours)

You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Changes to be committed:

	modified:   50-books/00-note/l2tp_layer_two_tunneling_protocol/readme.md
	new file:   50-books/00-note/l2tp_layer_two_tunneling_protocol/xl2tpd_install.htm
	new file:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.c
	new file:   81-kernel_programming/networks/forward.md
	new file:   81-kernel_programming/networks/network_model.md
	new file:   90-operating_system/ssh_login_via_key.txt
	new file:   tools/clear_file.sh
	new file:   tools/clone_lcd_tft.sh
	new file:   tools/clone_libpcap.sh
	new file:   tools/clone_xl2tpd.sh
	new file:   tools/coding/git/del_file_commit_history.sh
	new file:   tools/coding/git/local_clone.sh
	new file:   tools/gcc/libpcap_compile.md
	new file:   tools/gcc/xl2tpd_compile.md
	new file:   tools/lcd_show_pic.sh

Unmerged paths:
  (use "git add <file>..." to mark resolution)

	both added:      70-gcc_gnu_compiler_collection/README.md
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/Makefile
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/client.c
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.h
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/readme.txt
	both added:      80-userspace_programming/com_unix_sock/dlpi_dramalifepi/server.c
	both added:      80-userspace_programming/script/decrypt.sh
	both added:      80-userspace_programming/script/encrypt-FloderPasswdOutpath.sh
	both modified:   README.md
	both modified:   tools/fs/linux_mount_smb.md
	both added:      tools/gcc/git_compile.sh

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	tmp/


dramalife@Lenovo:~/note$ git add -u
dramalife@Lenovo:~/note$ git status
On branch master
Your branch and 'origin/master' have diverged,
and have 258 and 280 different commits each, respectively.
  (use "git pull" to merge the remote branch into yours)

All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:

	modified:   50-books/00-note/l2tp_layer_two_tunneling_protocol/readme.md
	new file:   50-books/00-note/l2tp_layer_two_tunneling_protocol/xl2tpd_install.htm
	modified:   70-gcc_gnu_compiler_collection/README.md
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/Makefile
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/client.c
	new file:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.c
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.h
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/readme.txt
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/server.c
	modified:   80-userspace_programming/script/decrypt.sh
	modified:   80-userspace_programming/script/encrypt-FloderPasswdOutpath.sh
	new file:   81-kernel_programming/networks/forward.md
	new file:   81-kernel_programming/networks/network_model.md
	new file:   90-operating_system/ssh_login_via_key.txt
	modified:   README.md
	new file:   tools/clear_file.sh
	new file:   tools/clone_lcd_tft.sh
	new file:   tools/clone_libpcap.sh
	new file:   tools/clone_xl2tpd.sh
	new file:   tools/coding/git/del_file_commit_history.sh
	new file:   tools/coding/git/local_clone.sh
	modified:   tools/fs/linux_mount_smb.md
	modified:   tools/gcc/git_compile.sh
	new file:   tools/gcc/libpcap_compile.md
	new file:   tools/gcc/xl2tpd_compile.md
	new file:   tools/lcd_show_pic.sh

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	tmp/

dramalife@Lenovo:~/note$ git status
On branch master
Your branch and 'origin/master' have diverged,
and have 258 and 280 different commits each, respectively.
  (use "git pull" to merge the remote branch into yours)

All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:

	modified:   50-books/00-note/l2tp_layer_two_tunneling_protocol/readme.md
	new file:   50-books/00-note/l2tp_layer_two_tunneling_protocol/xl2tpd_install.htm
	modified:   70-gcc_gnu_compiler_collection/README.md
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/Makefile
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/client.c
	new file:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.c
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/dlpi_common.h
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/readme.txt
	modified:   80-userspace_programming/com_unix_sock/dlpi_dramalifepi/server.c
	modified:   80-userspace_programming/script/decrypt.sh
	modified:   80-userspace_programming/script/encrypt-FloderPasswdOutpath.sh
	new file:   81-kernel_programming/networks/forward.md
	new file:   81-kernel_programming/networks/network_model.md
	new file:   90-operating_system/ssh_login_via_key.txt
	modified:   README.md
	new file:   tools/clear_file.sh
	new file:   tools/clone_lcd_tft.sh
	new file:   tools/clone_libpcap.sh
	new file:   tools/clone_xl2tpd.sh
	new file:   tools/coding/git/del_file_commit_history.sh
	new file:   tools/coding/git/local_clone.sh
	modified:   tools/fs/linux_mount_smb.md
	modified:   tools/gcc/git_compile.sh
	new file:   tools/gcc/libpcap_compile.md
	new file:   tools/gcc/xl2tpd_compile.md
	new file:   tools/lcd_show_pic.sh

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	tmp/

dramalife@Lenovo:~/note$ git commit -m"conflict"
[master 106305818] conflict
dramalife@Lenovo:~/note$ git status
On branch master
Your branch is ahead of 'origin/master' by 259 commits.
  (use "git push" to publish your local commits)

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	tmp/

nothing added to commit but untracked files present (use "git add" to track)

dramalife@Lenovo:~/note$ git pull
Already up to date.


dramalife@Lenovo:~/note$ git push
Username for 'https://github.com': dramalife@live.com


