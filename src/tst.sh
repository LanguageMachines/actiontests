#! /bin/sh
./main > tst.log 2>&1
./fork >> tst.log 2>&1
