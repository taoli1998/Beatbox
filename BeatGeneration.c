#include "AudioMixer.h"
#include "function.h"
#include "button.h"
#include "BeatGeneration.h"
#include "control.h"
#include "intervalTimer.h"

#include <alsa/asoundlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <limits.h>
#include <alloca.h> 

#define BASE "beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav"
#define HIHAT "beatbox-wav-files/100053__menegass__gui-drum-cc.wav"
#define SNARE "beatbox-wav-files/100059__menegass__gui-drum-snare-soft.wav"

static wavedata_t base;
static wavedata_t snare;
static wavedata_t hihat;
static int stop = 0;

static pthread_t BeatThreadId;
static void* BeatGenerating(void* args);

void Beat_start(void){
    pthread_create(&BeatThreadId, NULL, BeatGenerating, NULL);
}

void Beat_stop(void){
    stop = 1;
    pthread_join(BeatThreadId, NULL);
}

static void* BeatGenerating(void* args){
	AudioMixer_readWaveFileIntoMemory(BASE, &base);	
	AudioMixer_readWaveFileIntoMemory(SNARE, &snare);	
	AudioMixer_readWaveFileIntoMemory(HIHAT, &hihat);
    while (stop ==0){
        if(red_button_press()){
            while(red_button_press()){};
            AudioMixer_queueSound(&base);
            Interval_markInterval(INTERVAL_BEAT_BOX); 
        }
        else if(yellow_button_press()){
            while(yellow_button_press()){};
            AudioMixer_queueSound(&snare);
            Interval_markInterval(INTERVAL_BEAT_BOX);
        }
        else if(green_button_press()){
            while(green_button_press());
            AudioMixer_queueSound(&hihat);
            Interval_markInterval(INTERVAL_BEAT_BOX);
        }
    }
    return NULL;
}


