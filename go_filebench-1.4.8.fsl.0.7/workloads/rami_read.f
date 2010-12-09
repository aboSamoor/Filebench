set $dir=/media/sda7
define fileset name=rami_fileset,path=$dir,size=1m,entries=10,dirwidth=10,prealloc,datasource=entro,entropy=3.0
define process name=filereader,instances=1
{
  thread name=filereaderthread,memsize=10m,instances=10
  {
    flowop read name=readfile,filesetname=rami_fileset,iosize=1m
  }
}
run 20
