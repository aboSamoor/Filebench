#!/usr/bin/env python

from optparse import OptionParser
import re
import time
import os

def generate_work(fname, fout, entropy):
    filp = open(fname, 'r')
    text = filp.read()
    filp.close()
    text_mod = re.sub("entropy=\d+.?\d+", "entropy="+str(entropy), text)
    filp_out = open(fout, 'w')
    filp_out.write(text_mod)
    filp_out.close()


def parse_values_file(fname):
    filp = open(fname, 'r')
    text = filp.readlines()
    filp.close()
    values = filter(lambda x: x, [line.replace('\n','').split(',') for line in text])
    result = []
    for item in values:
        tmp = filter(lambda x: x, item)
        result +=  [float(x) for x in tmp]
    return result

parser = OptionParser()
parser.add_option("-v", "--entropy", dest="values_file",help="File that contains the values of the entropy seperated by commas")
parser.add_option("-l", "--log_dir", dest="log_dir",help="place where logs will be saved")
parser.add_option("-d", "--fileset_dir", dest="fileset_dir",help="The folder where the fileset will be placed, this sdfs access folder")
parser.add_option("-x", "--ext2_dir", dest="ext2_dir",help="The ext2 access folder to the files written")
parser.add_option("-w", "--workload", dest="workload", help="The file that will run in filebench")
parser.add_option("-q", "--quiet", action="store_false", dest="verbose", default=True, help="don't print status messages to stdout")
(options, args) = parser.parse_args()

values = parse_values_file(options.values_file)
i=0
for value in values:
    stamp = time.strftime("%d%b%Y%H%M%S", time.gmtime())
    current_load ="/tmp/fb_"+stamp
    generate_work(options.workload,current_load,value)
    operation = options.workload.split('/')[-1][:-2]
    log_file = options.log_dir+"/log_"+operation+"_"+str(value)+"_"+stamp
    args = ['./process.sh', './go_filebench', current_load, options.fileset_dir, './ent', options.ext2_dir,'>',log_file]
    print "We are running "+operation+" with entropy of "+str(value)
    print ' '.join(args)
    os.system(' '.join(args))
    i+=1
    print str(len(values)-i)+" Jobs are remainging"
