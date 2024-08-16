#include "button.h"
#include "joystick.h"
#include "AudioMixer.h"
#include "LEDmatrix.h"
#include "function.h"
#include "control.h"
#include "BeatGeneration.h"
#include "intervalTimer.h"
#include "pattern.h"
#include "analysis.h"

int main(){	

	start();
	check_Q();
	terminate();

    return 0;
}
