#ifndef HARMONICMOTIONDATAGENERATOR_H
#define HARMONICMOTIONDATAGENERATOR_H
#include "DataGenerator.h"

class HarmonicMotionDataGenerator : public DataGenerator {
    double amplitude;
    double ciclicFrequency;
    double phase;
    double x;

    HarmonicMotionDataGenerator(int);

    HarmonicMotionDataGenerator(double deltaTime);
    HarmonicMotionDataGenerator(double deltaTime, double amplitude, double ciclicFrequency, double phase);
    HarmonicMotionDataGenerator(double deltaTime, double minAmplitude, double maxAmplitude, double minCiclicFrequency, double maxCiclicFrequency, double minPhase, double maxPhase);
    void setAmplitude(double);
    void setCiclicFrequency(double);
    void setPhase(double);
    void setX(double);

    public:
    double getAmplitude();
    double getCiclicFrequency();
    double getPhase();
    double getX();

    void compute() override;
     ~HarmonicMotionDataGenerator()override;
};
#endif // HARMONICMOTIONDATAGENERATOR_H
