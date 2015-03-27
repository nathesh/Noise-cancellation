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
    struct dirent *about;
    struct stat myfile;
    char* path_name; 
    path_name = "../data/Ideal_Noise/wav_files/";
    target = opendir("../data/Ideal_Noise/wav_files/");
    /* Open the WAV file. */
    char buff[128];
    int one;
    one = 0;
    long int length;
    int counter;
    counter = 0;
    length = 1638286; 
    
    float* all_files;
    all_files = (float *) malloc(length*sizeof(float)*10);


    while (about = readdir(target)) {
    
        if((one != 1) && (one !=6) && (one !=0)){

            strcpy(buff,path_name);
            strcat(buff,about->d_name);
            //printf("\n%d%s\n",one,buff);
            sf = sf_open(buff,SFM_READ,&info);
        if (sf == NULL){

            printf("Failed to open the file.\n");
            exit(-1);
        }

        /* Print some of the info, and figure out how much data to read. */

        f = info.frames;
        sr = info.samplerate;
        c = info.channels;
        //printf("frames=%d\n",f);
        //printf("samplerate=%d\n",sr);
        //printf("channels=%d\n",c);
        num_items = f*c;
        //printf("num_items=%d\n",num_items);

        /* Allocate space for the data to be read, then read it. */
        buf = (float *) malloc(num_items*sizeof(float));
        num = sf_read_float(sf,buf,num_items);
        sf_close(sf);
        //printf("Read %d items\n",num);
        int x;
        for(x = 0; x<length;x++) {
            all_files[counter*length+x] = buf[x];
            if(x<0)
            {
                printf("%s","PRINT SHIT!!!!");
            }
        }
        //printf("%ld\n",(long int) counter*length);
        counter +=1;
        }
        one += 1;
        }
    return all_files;
}

