./prepare.sh
sleep 10
./robot.py -v ./values -l results2 -d /mnt/sdfs/rami_fileset -x /mnt/sdbdrive/dedupfs/files/rami_fileset -w work_write.f
sudo rm -rf /var/tmp/*
./robot.py -v ./values -l results2 -d /mnt/sdfs/rami_fileset -x /mnt/sdbdrive/dedupfs/files/rami_fileset -w work_read.f
sudo rm -rf /var/tmp/*
