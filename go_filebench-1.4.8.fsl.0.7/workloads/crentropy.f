#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.

set $dir=/tmp
set $nfiles=50000
set $meandirwidth=100
set $filesize=16k
set $iosize=1m
set $nthreads=16
set $srcval=entro

set mode quit firstdone

define fileset name=bigfileset,path=$dir,size=$filesize,entries=$nfiles,dirwidth=$meandirwidth,datasource=entro,entropy=3.4 #,dummy=baddum
define process name=filecreate,instances=1
{
  thread name=filecreatethread,memsize=10m,instances=$nthreads
  {
    flowop createfile name=createfile1,filesetname=bigfileset,fd=1
    flowop writewholefile name=writefile1,fd=1,iosize=$iosize
    flowop closefile name=closefile1,fd=1
    flowop opslimit name=limit
  }
}

echo  "Createfiles Version 2.5 personality successfully loaded"
usage "Usage: set \$dir=<dir>          defaults to $dir"
usage "       set \$filesize=<size>    defaults to $filesize"
usage "       set \$iosize=<size>      defaults to $iosize"
usage "       set \$nfiles=<value>     defaults to $nfiles"
usage "       set \$nthreads=<value>   defaults to $nthreads"
usage "       set \$meandirwidth=<size> defaults to $meandirwidth"
usage "(sets mean dir width and dir depth is calculated as log (width, nfiles)"
usage " "
usage "       run"
