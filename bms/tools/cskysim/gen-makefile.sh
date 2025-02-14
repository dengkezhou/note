#!/bin/bash

THISPATH=`pwd`
THISDIR=`basename $THISPATH`

if [ -z $1 ]; then
	echo "ARCHIVE := ${THISDIR}.a"
else
	echo "ARCHIVE := $1"
fi

echo
echo "SRCS := \\"

for i in `ls *.c *.S 2>/dev/null`; do
	echo -e "\t$i \\";
done
echo
echo
echo 'include $(BUILD_LIB)'
echo
