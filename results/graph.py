# Script takes 4 arguments
# 1 = Name of the CSV file
# 2 = Y variable {valid values: ops, mb, latency}
# Example: python graph.py ../reports/Random_E.csv 25 ops

import matplotlib.pyplot
from pylab import *

c2=0
c1=9

xl="dummy"
yl="dummy"

if(sys.argv[2] == 'ops'):
	c1 = 1
	yl="Operations/sec"
elif(sys.argv[2] == 'mb'):
	c1 = 2
	yl="Bandwidth (mb/sec)"
elif(sys.argv[2] == 'latency'):
	c1 = 3
	yl="Latency (msec)"
elif(sys.argv[2] == 'comp'):
	c1 = 4
	yl="Compression Ratio (%)"

xl="File Entropy (Bits/Byte)"

fh=open(sys.argv[1])
lines = fh.readlines()
s = [ (float) (line.split(',')[c1]) for line in lines]
e = [ float(line.split(',')[c2]) for line in lines]
fig = figure()
xlabel(xl)
ylabel(yl)
title(yl+" v/s "+xl+"\n in Filebench")
foo = fig.add_subplot(111)
line_plots = foo.plot(e, s, 'o-')

xlim(0,8)
ylim(0,)

grid(True)
show()
