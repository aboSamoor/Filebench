set $dir=/mnt/sdfs
define fileset name=rami_fileset,path=$dir,size=1m,entries=50000,dirwidth=100000,prealloc,datasource=entro,entropy=3.0
define process name=filereader,instances=1
{
  thread name=filereaderthread,memsize=10m,instances=10
  {
    flowop read name=readfile,filesetname=rami_fileset,iosize=1m
  }
}
run 300
