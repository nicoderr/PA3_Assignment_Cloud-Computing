//Include the required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//defining buffer and chunk sizes
#define BUFFER_SIZE 100
#define CHUNK_SIZE 1000000

int stringsCompare(const void *a, const void *b) 
{
    return strcmp(*(const char **)a, *(const char **)b);
}

//main function
int main(int argc, char *argv[]) 
{	
	//taking  input, output and logfile in command line argument
    	if (argc != 4) 
	{
        	printf("Usage: %s <input_file> <output_file> <log_file>\n", argv[0]);
        	return 1;
    	}
    	FILE *logFile = fopen(argv[3], "a");
    	if (logFile == NULL) 
	{
        	fprintf(stderr, "Error in opening the log file\n");
        	return 1;
    	}

    	// Redirecting the output in log file
    	dup2(fileno(logFile), STDOUT_FILENO);
    	dup2(fileno(logFile), STDERR_FILENO);

    	clock_t start_time, end_time;
    	double cpu_time;
	start_time = clock();
	FILE *file_in, *file_out;
    	char buffer[BUFFER_SIZE];
	file_in = fopen(argv[1], "r");
    	if (file_in == NULL) 
	{
        	fprintf(stderr, "fopen(%s) failed", argv[1]);
        	return 1;
    	}
    	file_out = fopen(argv[2], "w");
    	if (file_out == NULL) 
	{
        	fprintf(stderr, "fopen(%s) failed", argv[2]);
        	fclose(file_in);
        	return 1;
    	}

    	char *chunk[CHUNK_SIZE];
    	int num_line = 0;
    	long long total_read_Bytes = 0, totalBytesWritten = 0;
    	long long totalAllocatedMemory = 0;
    	long long num_Allocations = 0;

    	fseek(file_in, 0, SEEK_END);

    	fseek(file_in, 0, SEEK_SET);

    	while (fgets(buffer, BUFFER_SIZE, file_in) != NULL) 
	{
        	buffer[strcspn(buffer, "\n")] = '\0'; 
		//Allocating memory
        	chunk[num_line] = strdup(buffer); 
        	num_line += 1;

        	if(num_line == CHUNK_SIZE) 
		{
            		//Sorting the chunk using Quicksort
            		qsort(chunk, num_line, sizeof(char *), stringsCompare);
			//writing output to output file
            		for (int i = 0; i < num_line; ++i) 
			{
                		fprintf(file_out, "%s\n", chunk[i]);
                		free(chunk[i]); 
            		}
			//Reseting num_line for next chunk
			num_line = 0; 
        	}
    	}	
    	qsort(chunk, num_line, sizeof(char *), stringsCompare);
    	for (int i = 0; i < num_line; ++i) 
	{
        	fprintf(file_out, "%s\n", chunk[i]);
		// Freeing the memory
        	free(chunk[i]); 
    	}

    	totalAllocatedMemory += sizeof(char) * BUFFER_SIZE * CHUNK_SIZE; // Memory for buffer and chunk array
    	num_Allocations++;
    	total_read_Bytes = ftell(file_in);
   	totalBytesWritten = ftell(file_out);
    	fclose(file_out);
    	fclose(file_in);

    	end_time = clock();
    	cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    	double avg_memory_uti = 0.0;
    	if (num_Allocations > 0) 
    	{
        	avg_memory_uti = (double)totalAllocatedMemory / num_Allocations;
        	avg_memory_uti /= (1024 * 1024 * 1024); // Convert to gigabytes
    	}

	//Calculating Total CPU time used by the process
	double total_cpu_time = cpu_time * sysconf(_SC_CLK_TCK); 
	double cpu_utilization = (total_cpu_time / (sysconf(_SC_CLK_TCK) * sysconf(_SC_CLK_TCK))) * 100.0;

	double io_Throughput = (total_read_Bytes + totalBytesWritten) / (1024 * 1024 * cpu_time);
   	printf("Sort Time : %.2f seconds\n", cpu_time);
    	printf("Overall I/O Throughput : %.2f MB/sec\n", io_Throughput);
    	printf("Overall CPU Utilization : %.2f%%\n", cpu_utilization);
    	printf("Average Memory Utilization : %.2f GB\n", avg_memory_uti);
    	fclose(logFile);
    	
	return 0;
}
