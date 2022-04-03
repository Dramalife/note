source ~/.bashrc
if [ -z $PATH_LIBDRAMALIFE ] ; then
cat >> ~/.bashrc << EOF
export PATH_LIBDRAMALIFE=$(cd $(dirname ${BASH_SOURCE:-$0});pwd)
EOF
source ~/.bashrc
fi
