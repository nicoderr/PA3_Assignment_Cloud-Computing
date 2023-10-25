#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <input_file> <output_file>"
    exit 1
fi

# taking input and output filenames from command-line
input_file="$1"
output_file="$2"

# Running the sort command
{ time LC_ALL=C sort -S G --parallel=8 "$input_file" -o "$output_file"; } 2> sort_log.txt

# Extracting real time, user time, and system time from output
real_time=$(grep real sort_log.txt | awk '{print $2}' | sed 's/m//' | sed 's/s//')
user_time=$(grep user sort_log.txt | awk '{print $2}' | sed 's/m//' | sed 's/s//')
sys_time=$(grep sys sort_log.txt | awk '{print $2}' | sed 's/m//' | sed 's/s//')

file_size=$(wc -c < "$input_file")

//Calculating Sort time, overall I/O Throughput, Overall CPU Utilization and Average Memory Utilization
io_time=$(echo "$real_time" | sed 's/[ms]//g')
io_throughput=$(echo "scale=2; $file_size / ($real_time * 1024 * 1024)" | bc)
total_cpu_time=$(echo "$user_time + $sys_time" | bc)
num_cores=$(nproc)
cpu_utilization=$(echo "scale=2; ($total_cpu_time / ($real_time * $num_cores)) * 100" | bc)

//Allocating memory size as allocated
memory_size=500
average_memory_utilization=$(echo "scale=2; $memory_size / $num_cores" | bc)

# Displaying the results
echo "Sort Time : $io_time s"
echo "Overall I/O Throughput : $io_throughput MB/sec"
echo "Overall CPU Utilization : $cpu_utilization %"
echo "Average Memory Utilization : $average_memory_utilization GB"
