set $dir=/media/sda7
define fileset name=rami_fileset,path=$dir,size=1m,entries=5000,dirwidth=1000,prealloc
define process name=filereader,instances=1
{
  thread name=filereaderthread,memsize=10m,instances=10
  {
    flowop read name=readfile,filesetname=rami_fileset,iosize=1m
  }
}
run 30

stats dump "rami_read.log"
