#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <string.h>
#define LENGTH (16382856)
float* output_file();
void output_audio();