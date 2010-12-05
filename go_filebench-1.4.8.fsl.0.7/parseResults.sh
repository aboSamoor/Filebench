#!/bin/sh

# This script takes one command line argument.
# The argument is the name of the directory that contains all the log files
# This script iterates over all log files and prints the results to std out
# Output should be redirected to a file that is not in the logs directory itself

for f in $1/*
do
	echo -n "$f,"
	# Extract filename
	fgrep -w "./go_filebench" $f | awk '{printf "%s,",$3}'

	# Extract Entropy
	fgrep -w "Entropy" $f | awk '{printf "%s,",$3}'

	# Extract 'writtfile' Details
	fgrep -w "writtfile" $f | awk '{printf "%s,%s,%s,%s,",$2,$3,$4,$5}'
	
	# Extract IO Summary
	fgrep -w "IO Summary" $f | awk '{printf "%s,%s,%s,%s%s,%s,",$5,$7,$9,$11,$12,$14}'
	
	# Extract ext2 File Size
	tail -4 $f | head -n 1 | awk '{printf "%s,",$1}'

	# Extract ext2 File Size
	tail -2 $f | head -n 1 | awk '{printf "%s",$1}'
	
	echo -n '\n'
done
