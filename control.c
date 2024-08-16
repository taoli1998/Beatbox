#include "control.h"
#include "joystick.h"
#include "LEDmatrix.h"
#include "function.h"
#include "button.h"
#include "AudioMixer.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define Joy_thres 0.5
#define volume_default 80
#define BPM_default 120
#define BPM_MAX 300
#define BPM_MIN 40

static pthread_t threadId;
static int stop = 0;
static int mode = 0;
static int BPM = BPM_default;
static int vol = volume_default;
static void* Controlling(void* args);
static void mode_display(void);
static void AudioMixer_setBPM(int newBPM);
static int AudioMixer_getBPM(void);


void Control_start(void){
    pthread_create(&threadId, NULL, Controlling, NULL);
}

void Control_stop(void){
    stop = 1;
    pthread_join(threadId, NULL);
}

int get_mode(void){
    return mode;
}

int get_bpm(void){
    return BPM;
}

int get_vol(void){
    return vol;
}

static void* Controlling(void* args){
    while(stop==0){
        double x,y;
        joystick_readXY(&x,&y);
        vol = AudioMixer_getVolume();
        if(x > Joy_thres){
            BPM = AudioMixer_getBPM() + 5;
            if(BPM>300){
                BPM = 300;
            }          
            double BPS = BPM/60.0;
            dou_display(BPS);
            AudioMixer_setBPM(BPM);
            sleep_random_time();
        }
        else if(x < -Joy_thres){
            BPM = AudioMixer_getBPM()- 5;
            if (BPM < 40){
                BPM = 40;
            }
            double BPS = BPM/60.0;
            dou_display(BPS);
            AudioMixer_setBPM(BPM);
            sleep_random_time();
        }
        else if(y > Joy_thres){
            vol = vol+5;
            if (vol > 99){
                vol = 100;
                int_display(99);
            }
            else{
                int_display(vol);
            }            
            AudioMixer_setVolume(vol);
            sleep_random_time();
        }
        else if(y < -Joy_thres){
            vol = vol-5;
            if (vol < 0){
                vol = 0;
            }
            int_display(vol);
            AudioMixer_setVolume(vol);
            sleep_random_time();
        }
        else if(gray_button_press()){
            while(gray_button_press()){}
            mode++;
            if (mode > 2){
                mode = 0;
            }
            mode_display();
        }
        else{
            mode_display();
        }
        sleepForMs(100);
    }
    return NULL;
}

static int AudioMixer_getBPM(void){
    return BPM;
}

static void AudioMixer_setBPM(int newBPM){
    BPM = newBPM;
}
double HalfBeat_ms(void){
    double HalfBeat = 30*1000/BPM;
    return HalfBeat;
}

static void mode_display(){
    if(mode==0){
        Convert_logical("M0");
    }
    else if(mode==1){
        Convert_logical("M1");
    }
    else{
        Convert_logical("M2");
    }
}
