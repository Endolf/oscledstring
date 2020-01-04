#include "solidcolourstate.h"

SolidColourState::SolidColourState(CRGB leds[], int numLeds) {
    this->numLeds = numLeds;
    this->leds = leds;
};

void SolidColourState::setColour(CRGB colour) {
    this->colour[0] = colour[0];
    this->colour[1] = colour[1];
    this->colour[2] = colour[2];
};

void SolidColourState::setRed(uint8_t red) {
    this->colour[0] = red;
};
void SolidColourState::setGreen(uint8_t green) {
    this->colour[1] = green;
};
void SolidColourState::setBlue(uint8_t blue) {
    this->colour[2] = blue;
};

void SolidColourState::update() {
    fill_solid(leds,numLeds,colour);
};
