#!/bin/bash

# This script takes two command line arguments.
# The first argument is the name of the directory that contains all the log files
# The second argument is either a "w" or a "r", depending on whether write or read
# log files need to be parsed.
# This script iterates over all log files and prints the results to std out
# Output should be redirected to a file that is not in the logs directory itself.

if [ $# -ne 2 ]
then
	echo "Incorrect number of arguments"
	echo "Usage: ./parseResults folder w|r"
fi

for f in $1/*
do
	echo -n "$f,"
	# Extract filename
	fgrep -w "./go_filebench" $f | awk '{printf "%s,",$3}'

	# Extract Entropy
	fgrep -w "Entropy" $f | awk '{printf "%s,",$3}'

	if [ "$2" == "w" ]
	then
		# Extract 'writtfile' Details
		fgrep -w "writtfile" $f | awk '{printf "%s,%s,%s,%s,",$2,$3,$4,$5}'
	elif [ "$2" == "r" ]
	then
		# Extract 'readfile' Details
		fgrep -w "readfile" $f | awk '{printf "%s,%s,%s,%s,",$2,$3,$4,$5}'
	fi
	
	# Extract IO Summary
	fgrep -w "IO Summary" $f | awk '{printf "%s,%s,%s,%s%s,%s,",$5,$7,$9,$11,$12,$14}'
	
	# Extract ext2 File Size
	# tail -4 $f | head -n 1 | awk '{printf "%s,",$1}'
	grep -C 2 "du -s" $f | tail -4 | head -n 1 | awk '{printf "%s,",$1}'
	
	# Extract ext2 File Size
	# tail -2 $f | head -n 1 | awk '{printf "%s",$1}'
	grep -C 2 "du -s" $f | tail -2 | head -n 1 | awk '{printf "%s",$1}'

	echo ""
done
