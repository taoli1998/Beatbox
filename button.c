#include "button.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>

#define button "/sys/class/gpio/gpio72/value"
#define gray "/sys/class/gpio/gpio47/value"
#define red "/sys/class/gpio/gpio46/value"
#define yellow "/sys/class/gpio/gpio27/value"
#define green "/sys/class/gpio/gpio65/value"

void button_start(void){
    runCommand("config-pin p8.43 gpio");
    runCommand("config-pin -q p8.43");
    runCommand("echo 72 > export");

    runCommand("config-pin p8.15 gpio");
    runCommand("config-pin -q p8.15");
    runCommand("echo 47 > export");

    runCommand("config-pin p8.16 gpio");
    runCommand("config-pin -q p8.16");
    runCommand("echo 46 > export");

    runCommand("config-pin p8.17 gpio");
    runCommand("config-pin -q p8.17");
    runCommand("echo 27 > export");

    runCommand("config-pin p8.18 gpio");
    runCommand("config-pin -q p8.18");
    runCommand("echo 65 > export");
}

int gray_button_press(void){
    return readFromFileToScreen(gray)==1;
}
int gray_button_release(void){
    return readFromFileToScreen(gray)==0;
}


int red_button_press(void){
    return readFromFileToScreen(red)==1;
}
int red_button_release(void){
    return readFromFileToScreen(red)==0;
}

int yellow_button_press(void){
    return readFromFileToScreen(yellow)==1;
}
int yellow_button_release(void){
    return readFromFileToScreen(yellow)==0;
}

int green_button_press(void){
    return readFromFileToScreen(green)==1;
}
int green_button_release(void){
    return readFromFileToScreen(green)==0;
}


static int button_press(){
    return readFromFileToScreen(button);
}

void check_button(void)
{
    int shutdown = 0;
    while(shutdown==0){
        sleepForMs(100);
        if(button_press()==0){
            shutdown=1;
        }
    }
}
