#! /bin/sh
status=0
./main > tst.log 2>&1
status=$(($status + $?))
cat < afile
exit $status
