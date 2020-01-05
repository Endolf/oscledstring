#ifndef MAIN_H
#define MAIN_H

//Disable annoying compile "warnings"
#define FASTLED_INTERNAL

#define OSCPORT 2000
#define LED_DATA_PIN 2
#define LED_TYPE WS2813
#define COLOR_ORDER GRB
#define NUM_LEDS 144

#define FRAMES_PER_SECOND 120

void setup();
void loop();

#endif