#! /bin/bash

home=$HOME
prog="${PWD}/go_filebench -f"
write_load="${PWD}/workloads/rami_write.f"
read_load="${PWD}/workloads/rami_read.f"

change_dir="cd ${PWD}"
cmd_write="${prog} ${write_load}"
cmd_read="${prog} ${read_load}"
cmd_mv="cp -r ${PWD}/rami_* /home/eid/Desktop/ ; rm ${PWD}/rami_*"
testing="${HOME}/ent/ent /media/sda7/rami_fileset/00000001/00000005"

echo "@@@@@@@@@@@@@@@@@@This script expects to run as a superuser, to switch to a superuser run 'sudo -i'@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@This script expects that you have  /root/ent/ent to test files                   @@@@@@@@@@@@@@"

#sudo -i
$change_dir

echo "Dropping memory caches...................."
sync && echo 3 > /proc/sys/vm/drop_caches

echo "Writing load.............................."
$cmd_write

echo "Testing files.............................."
$testing

echo "Reading load.............................."
$cmd_read

echo "Testing files.............................."
$testing

echo "Moving log files.........................."
$cmd_mv
