#! /bin/bash
#
# note tools svn related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init	: 2019.07.13 14:20
#

DATE_NOTE=$(date "+%Y%m%d%H%m%S")
TEMP_FILE=./.status_svn.note
BACKUP_OUT_FILE=svn.${DATE_NOTE}.tgz

# USEAGE : 
#	1) Run the script;
#	2) Edit ${TEMP_FILE}  manually;
#	3) Run the script again.

# STEP 1. Output the list in which items should be packed to {TEMP_FILE},
#	if it is not exist.
if [ ! -f ${TEMP_FILE} ]; then
echo "Step 1 : Create tmp file ${TEMP_FILE} done, Edit it manually!"
svn status -q > ${TEMP_FILE}
else

# STEP 2. TODO 
# 	Before starting this script the second time,you should modified the
#	${TEMP_FILE} first to the format that {xargs} can recognize.

# STEP 3. Read list from {TEMP_FILE} and pack the items.
echo "Step 3 : Packing files!"
cat ${TEMP_FILE} | xargs tar czvf ${BACKUP_OUT_FILE}
rm -rvf ${TEMP_FILE}
fi

