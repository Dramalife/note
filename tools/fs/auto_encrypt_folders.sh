#! /bin/bash

# auto encrypt folders by index


startnum=3
maxnum=8

father_folder="000"
pic="pic000"
avi="avi000"

passwd="666"

for ((;startnum<=maxnum;startnum++));
do
echo "${father_folder}${startnum}";
echo ${date} >> nohup.out
cd "/root/disk-ug2t/clear_ug2t/new/avi/${father_folder}${startnum}";
echo "${pic}${startnum}";
nohup encrypt-FloderPasswdOutpath.sh ${pic}${startnum}  ${passwd} ./ &
echo "${avi}${startnum}";
nohup encrypt-FloderPasswdOutpath.sh ${avi}${startnum}  ${passwd} ./ &
#touch test.tmp
#rm test.tmp
done

