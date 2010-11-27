set $dir=/media/sda7
define fileset name=rami_fileset,path=$dir,size=1m,entries=500,dirwidth=1000,prealloc=0,datasource=entro,entropy=3.4
define process name=filewriter,instances=1
{
  thread name=filewriterthread,memsize=10m,instances=10
  {
    flowop createfile name=createfile,filesetname=rami_fileset,fd=1
    flowop write name=writefile,fd=1,iosize=1m
    flowop closefile name=closefile,fd=1
  }
}
run 30

stats dump "rami_write.log"