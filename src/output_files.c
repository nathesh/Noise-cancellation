#include "../include/output_files.h"
float* output_file()
{
    SNDFILE *sf;
    SF_INFO info;
    int num_channels;
    int num, num_items;
    float *buf;
    int f,sr,c;
    int i,j;
    FILE *out;
    DIR * target;
    struct stat myfile;
    char* path_name; 
    path_name = "data/Ideal_Noise/wav_files/";
    target = opendir("data/Ideal_Noise/wav_files/");
    /* Open the WAV file. */
    char buff[128];
    long int length;
    int counter;
    counter = 0;
    int files_counter;
    files_counter = 0;
    length = 1638286; 
    const char* a[10];
    struct dirent **namelist;
    int n;
    float* all_files;
    all_files = (float *) malloc(length*sizeof(float)*10);

    n = scandir(path_name, &namelist, 0, versionsort);
    if (n < 0)
    perror("scandir");
    else {
        while (files_counter<n-1) 
        {
            if(strcmp(namelist[files_counter]->d_name,".") != 0 && strcmp(namelist[files_counter]->d_name,"..") )
            {
                printf("%d, %s\n",files_counter,namelist[files_counter]->d_name);
                strcpy(buff,path_name);
                strcat(buff,namelist[files_counter]->d_name);
                sf = sf_open(buff,SFM_READ,&info);
                if (sf == NULL){
                    printf("Failed to open the file.\n");
                    exit(-1);
                }
                f = info.frames;
                sr = info.samplerate;
                c = info.channels;
                printf("frames=%d\n",f);
                printf("samplerate=%d\n",sr);
                printf("channels=%d\n",c);
                num_items = f*c;
                printf("num_items=%d\n",num_items);

                /* Allocate space for the data to be read, then read it. */
                buf = (float *) malloc(num_items*sizeof(float));
                num = sf_read_float(sf,buf,num_items);
                sf_close(sf);
                int x;
                for(x = 0; x<length;x++) {
                    all_files[counter*length+x] = buf[x];
                    //printf("%4.10f, %d\n",all_files[counter*length+x],22);
                    if(x<0)
                    {
                        printf("%s","PRINT SHIT!!!!");
                    }
                }

                counter +=1;
            }
        free(namelist[files_counter]);
        //free(buff);
        //printf("%s\n","PRINT SHIT!!!!");
        files_counter +=1;
        }
        free(namelist);
    }

        
        //printf("\n%s\n",about->d_name);
        
        /* Print some of the info, and figure out how much data to read. */

        
        //printf("Read %d items\n",num);
        
            
            //printf("%ld\n",(long int) counter*length);
            
        
 
    return all_files;
}

