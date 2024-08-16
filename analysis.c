#include "button.h"
#include "joystick.h"
#include "AudioMixer.h"
#include "LEDmatrix.h"
#include "function.h"
#include "control.h"
#include "BeatGeneration.h"
#include "intervalTimer.h"
#include "pattern.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

static int stop = 0;

static pthread_t analysis_threadid;
static void* analysising(void* args);

void Print_init(void){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&analysis_threadid, &attr, &analysising, NULL);
}
void Print_cleanup(void){
    stop = 1;
    pthread_join(analysis_threadid, NULL);
}


static void* analysising(void* args){
    
    while(stop == 0){

        Interval_statistics_t PCM;
        Interval_statistics_t beats;
        Interval_getStatisticsAndClear(INTERVAL_LOW_LEVEL_AUDIO, &PCM);
        Interval_getStatisticsAndClear(INTERVAL_BEAT_BOX, &beats);
        printf("M%d %dbpm vol:%d ",get_mode(), get_bpm(), get_vol());
        printf("Low[%.2f, %.2f] avg %.2f/%d  ", PCM.minIntervalInMs, PCM.maxIntervalInMs, PCM.avgIntervalInMs, PCM.numSamples);
        printf("Beat[%.2f, %.2f] avg %.2f/%d\n", beats.minIntervalInMs, beats.maxIntervalInMs, beats.avgIntervalInMs, beats.numSamples);
        sleepForMs(1000);
    }
    return NULL;
}
