#! /bin/bash

prog="$1 -f"
load="$2"
fset_dir="$3"
ent="$4"
ext2_dir="$5"

change_dir="cd ${PWD}"
cmd_del_fset="rm -rf ${fset_dir}"
cmd_load="${prog} ${load}"
cmd_testing="${ent} ${fset_dir}/00000001/00000001"
cmd_size1="du -s ${ext2_dir}"
cmd_size2="du -s ${fset_dir}"

echo "@@@@@@@@@@@@@@@@@@This script expects to run as a superuser, to switch to a superuser run 'sudo -i'@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@This script expects that you have  /root/ent/ent to test files                   @@@@@@@@@@@@@@"

echo "Deleting old filesets ...................."
echo "$cmd_del_fset"
$cmd_del_fset
echo
echo "Dropping memory caches...................."
echo "sync && echo 3 > /proc/sys/vm/drop_caches"
sync && echo 3 > /proc/sys/vm/drop_caches
echo
echo "Writing load.............................."
echo "$cmd_load"
stime=$(date +%s)
$cmd_load
etime=$(date +%s)
echo "Time spent in Filebench is $((etime - stime)) seconds"
echo
echo "Testing files.............................."
echo "$cmd_testing"
$cmd_testing
echo "Size of the fileset on the partition......."
echo "$cmd_size1"
$cmd_size1
echo "$cmd_size2"
$cmd_size2
echo
