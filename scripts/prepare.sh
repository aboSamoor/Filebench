mkfs -t ext2 /dev/sdb1
mount -t ext2 /dev/sdb1 /mnt/sdbdrive
rm -rf /mnt/sdbdrive/dedupfs/*
mount.sdfs -v sdfs_vol3 -m /mnt/sdfs &
sleep 10
rm -rf /mnt/sdfs/*
