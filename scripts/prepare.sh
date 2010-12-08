sudo mkfs -t ext2 /dev/sdb
sudo mount.ext2 /dev/sdb /mnt/sdbdrive
sudo mkdir /mnt/sdbdrive/dedupfs
sudo mount.sdfs -v sdfs_vol4 -m /mnt/sdfs

