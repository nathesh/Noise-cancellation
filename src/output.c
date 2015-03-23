#include <stdio.h>
#include <stdlib.h>
#include <vlc/vlc.h>

int main(int argc, char **argv)
{
    libvlc_instance_t *inst;
    libvlc_media_player_t *mp;
    libvlc_media_t *m;

    // load the engine
    inst = libvlc_new(0, NULL);

    // create a file to play
    m = libvlc_media_new_path(inst, "../data/rain.wav");

    // create a media play playing environment
    mp = libvlc_media_player_new_from_media(m);

    // release the media now.
    libvlc_media_release(m);

    // play the media_player
    libvlc_media_player_play(mp);

    sleep(10); // let it play for 10 seconds

    // stop playing
    libvlc_media_player_stop(mp);

    // free the memory.
    libvlc_media_player_release(mp);

    libvlc_release(inst);


    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

int main()
    {
    SNDFILE *sf;
    SF_INFO info;
    int num_channels;
    int num, num_items;
    int *buf;
    int f,sr,c;
    int i,j;
    FILE *out;
    
    // Open the WAV file. 
    info.format = 0;
    sf = sf_open("file.wav",SFM_READ,&info);
    if (sf == NULL)
        {
        printf("Failed to open the file.\n");
        exit(-1);
        }
    // Print some of the info, and figure out how much data to read. 
    f = info.frames;
    sr = info.samplerate;
    c = info.channels;
    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);
    num_items = f*c;
    printf("num_items=%d\n",num_items);
    // Allocate space for the data to be read, then read it. 
    buf = (int *) malloc(num_items*sizeof(int));
    num = sf_read_int(sf,buf,num_items);
    sf_close(sf);
    printf("Read %d items\n",num);
    // Write the data to filedata.out. 
    out = fopen("filedata.out","w");
    for (i = 0; i < num; i += c)
        {
        for (j = 0; j < c; ++j)
            fprintf(out,"%d ",buf[i+j]);
        fprintf(out,"\n");
        }
    fclose(out);
    return 0;
    }
    */
    