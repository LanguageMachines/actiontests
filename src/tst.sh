#! /bin/sh
status=0
./main > tst.log 2>&1
status=$(($status + $?))
./fork >> tst.log 2>&1
status=$(($status + $?))
exit $status
