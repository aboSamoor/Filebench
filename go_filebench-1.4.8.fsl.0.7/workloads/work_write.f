set $dir=/mnt
define fileset name=myfileset,path=$dir,size=1m,entries=50000,dirwidth=100000,prealloc=0
define process name=filewriter,instances=1
{
  thread name=filewriterthread,memsize=10m,instances=10
  {
    flowop createfile name=createfile,filesetname=myfileset,fd=1
    flowop write name=writtfile,fd=1,iosize=1m
    flowop closefile name=closefile,fd=1
  }
}
run 300
