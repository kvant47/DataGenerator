#include <iostream>
#include <cmath>
#include <ctime>
#include "HarmonicMotionDataGenerator.h"


    HarmonicMotionDataGenerator::HarmonicMotionDataGenerator(int deltaTime) {
            srand(std::time(NULL));
            setTime(0);
            setDeltaTime(deltaTime);
            x = 0;
            do {
                amplitude = 5 + rand() % 20;									//   от 5 до 25
            }
            while (amplitude == 0);
            do {
                ciclicFrequency = rand() % 2 + ((rand() % 100) / 100.0);			//  от 0,01 до 2,99.
            }
            while (ciclicFrequency < 0.5);
            do {
                phase = (rand() % 6) + ((rand() % 10) / 10.0) * 3.14;		// (от 0,314 до 18,526)
            }
            while (phase == 0);
        };																												// (от 0,314 до 18,526)

    void HarmonicMotionDataGenerator::setAmplitude(double amplitude)
    {
        this->amplitude = amplitude;
    }
    void HarmonicMotionDataGenerator::setCiclicFrequency(double ciclicFrequency)
    {
        this->ciclicFrequency = ciclicFrequency;
    }
    void HarmonicMotionDataGenerator::setPhase(double phase)
    {
        this->phase = phase;
    }
    void HarmonicMotionDataGenerator::setX(double x) {
        this->x = x;
    }

    double HarmonicMotionDataGenerator::getAmplitude()
    {
        return amplitude;
    }
    double HarmonicMotionDataGenerator::getCiclicFrequency() {
        return ciclicFrequency;
    }
    double HarmonicMotionDataGenerator::getPhase() {
        return phase;
    }
    double HarmonicMotionDataGenerator::getX() {
        return x;
    }

    void HarmonicMotionDataGenerator::compute()  {
        setX(getAmplitude() * sin(getCiclicFrequency() * getTime() + getPhase()));
       setTime(getTime() + getDeltaTime());
    }

    HarmonicMotionDataGenerator::~HarmonicMotionDataGenerator() {};

