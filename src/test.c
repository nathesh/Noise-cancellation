#include "../include/test.h"
int main () {

        DIR * target;
        struct dirent *about;
        struct stat myfile;

        target = opendir("../data/Ideal_Noise/wav_files/");

    while (about = readdir(target)) {
        printf("\n%s\n",about->d_name);
        // Need to use strcat to add directory name on front
        // Only works here 'cos it's current directory
        // lstat for links

        lstat(about->d_name,&myfile);

        printf("File is %d bytes\n",myfile.st_size);
        printf("File permissions %o\n",myfile.st_mode);
        if (myfile.st_mode & 16384)
                printf("WE GOT A DIRECORY, MATE!\n");
        if (myfile.st_mode & 8192)
                printf("OH GOWD - HE'S USING LINKS!\n");
                }

        }