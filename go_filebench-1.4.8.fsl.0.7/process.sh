#! /bin/bash

home=$HOME
prog="${PWD}/go_filebench -f"
write_load="${PWD}/workloads/rami_write.f"
read_load="${PWD}/workloads/rami_read.f"
fset_dir="/media/sda7/rami_fileset"

#rw_load="${PWD}/workloads/rami_rw.f"

change_dir="cd ${PWD}"
cmd_del_fset="rm -rf ${fset_dir}"
cmd_write="${prog} ${write_load}"
cmd_read="${prog} ${read_load}"
cmd_mv="cp -r ${PWD}/rami_* /home/eid/Desktop/ ; rm -rf ${PWD}/rami_*"
testing="${HOME}/ent/ent ${fset_dir}/00000001/00000001"

echo "@@@@@@@@@@@@@@@@@@This script expects to run as a superuser, to switch to a superuser run 'sudo -i'@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@This script expects that you have  /root/ent/ent to test files                   @@@@@@@@@@@@@@"

#sudo -i
$change_dir
echo "Deleting old filesets ...................."
$cmd_del_fset
echo
echo "Dropping memory caches...................."
sync && echo 3 > /proc/sys/vm/drop_caches
echo
echo "Writing load.............................."
stime=$(date +%s)
$cmd_write
etime=$(date +%s)
echo "Time spent in Filebench is $((etime - stime)) seconds"
echo
echo "Testing files.............................."
$testing
echo
#echo "Dropping memory caches...................."
#sync && echo 3 > /proc/sys/vm/drop_caches
#echo
#echo "Reading load.............................."
#$cmd_read
#echo
#echo "Testing files.............................."
#$testing
#echo
#echo "Moving log files.........................."
#$cmd_mv
