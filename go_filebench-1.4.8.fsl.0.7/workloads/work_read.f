set $dir=/mnt
define fileset name=myfileset,path=$dir,size=1m,entries=50000,dirwidth=100000,prealloc
define process name=filereader,instances=1
{
  thread name=filereaderthread,memsize=10m,instances=10
  {
    flowop read name=readfile,filesetname=myfileset,iosize=1m
  }
}
run 300
