#include "AudioMixer.h"
#include "function.h"
#include "button.h"
#include "pattern.h"
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

static pthread_t patternThreadId;
static void* Pattern_rotation(void* args);

static void mode0(void);
static void mode1(void);
static void mode2(void);

void pattern_start(void){
    pthread_create(&patternThreadId, NULL, Pattern_rotation, NULL);
}

void pattern_stop(void){
    stop = 1;
    pthread_join(patternThreadId, NULL);
}

static void* Pattern_rotation(void* args){
    AudioMixer_readWaveFileIntoMemory(BASE, &base);	
	AudioMixer_readWaveFileIntoMemory(SNARE, &snare);	
	AudioMixer_readWaveFileIntoMemory(HIHAT, &hihat);
    while(stop==0){
        if (get_mode()==0){
            mode0();
        }
        else if (get_mode()==1){
            mode1();
        }
        else if (get_mode()==2){
            mode2();
        }
    }
    return NULL;
}


static void mode0(void){
    return;
}

static void mode1(void){
        AudioMixer_queueSound(&base);
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
        AudioMixer_queueSound(&hihat);
        AudioMixer_queueSound(&snare);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
        AudioMixer_queueSound(&base);
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
        AudioMixer_queueSound(&hihat);
        AudioMixer_queueSound(&snare);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=1){
            return;
        }
}

static void mode2(void){
        AudioMixer_queueSound(&base);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
        AudioMixer_queueSound(&snare);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
        AudioMixer_queueSound(&base);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
        AudioMixer_queueSound(&base);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
        AudioMixer_queueSound(&snare);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
        AudioMixer_queueSound(&hihat);
        Interval_markInterval(INTERVAL_BEAT_BOX);
        sleepForMs(HalfBeat_ms());
        if(get_mode()!=2){
            return;
        }
}