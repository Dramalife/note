#! /bin/bash
#####
# dramalife@live.com
#


# Warning
echo -e "\nBelow is the content of this script:"
echo -e "\nRead CAREFULLY!"
cat ${0}
echo -e "\n\nPress any key to continue:"
read tmp
echo -e "\n\nPress any key again to continue:"
read tmp


# Check & Install vim
dpkg -s vim >/dev/null 2>&1
if [ $? != 0 ]
then
echo -e "\nInstallation check error, install now..."
sudo apt-get -y install vim
else
echo -e "\nInstallation check passed."
fi


# Update "vimrc" of current user
echo -e "\nBackup the original vimrc ..."
mv -v ~/.vimrc ~/.vimrc_dl_note_backup
echo -e "\nInstall new vimrc ..."
cp -v ./vimrc ~/.vimrc
echo -e "\nDone\n"
