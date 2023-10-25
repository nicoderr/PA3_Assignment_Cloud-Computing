**Prerequisites:**

sudo apt udpate
sudo apt install gcc(For installing gcc)

Generating the files using gensort:
$./gensort -a filesize filename

**Code Files:**

1. mysort.c(For shared memory sorting):
	mysort.c code is used for shared memory sorting of 1GB, 4GB, 16GB and 64GB and displaying sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB). The Quick sort technique is used for sorting the data. 

_Commands used to execute:_

$ gcc mysort.c -o sortout
$ ./sortout filename sortedfilename logfilename


2. linsort.sh(For Linux sorting):
	linsort.sh code is used for linux sorting of 1GB, 4GB, 16GB and 64GB and displaying sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) through command line. 

_Commands used to execute:_

$ script logfilename
$ chmod +x linsort.sh
$ ./linsort.sh filename sortedfilename 
$ exit

3. Makefile:
	Makefile used to execute the mysort.c for sorting the data

_Commands used to execute:_

$makefile



**Generated Log Files:**

linsort1GB.log : Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 1GB file using linux sort

linsort4GB.log :  Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 4GB file using linux sort

linsort16GB.log : Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 16GB file using linux sort

linsort64GB.log : Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 64GB file using linux sort

mysort1GB.log : Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 1GB file using shared-memory sort

mysort4GB.log : Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 4GB file using shared-memory sort

mysort16GB.log : Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 16GB file using shared-memory sort

mysort64GB.log : Log file indicates sort time (sec), Overall, I/O Throughput (MB/sec) Overall CPU Utilization (%), and Average Memory Utilization (GB) for sorting 64GB file using shared-memory sort


