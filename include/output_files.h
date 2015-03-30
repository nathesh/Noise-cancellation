#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <string.h>
#define LENGTH (1638286)
//#define _GNU_SOURCE
float* output_file();
void output_audio();