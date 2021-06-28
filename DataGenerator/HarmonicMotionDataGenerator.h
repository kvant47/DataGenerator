#ifndef HARMONICMOTIONDATAGENERATOR_H
#define HARMONICMOTIONDATAGENERATOR_H
#include "DataGenerator.h"

class HarmonicMotionDataGenerator : public DataGenerator {
    double amplitude;
    double ciclicFrequency;
    double phase;
    double x;

public:
    HarmonicMotionDataGenerator(int);

    void setAmplitude(double);
    void setCiclicFrequency(double);
    void setPhase(double);
    void setX(double);

    double getAmplitude();
    double getCiclicFrequency();
    double getPhase();
    double getX();

    void compute() override;
     ~HarmonicMotionDataGenerator()override;
};
#endif // HARMONICMOTIONDATAGENERATOR_H
