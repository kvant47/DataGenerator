#ifndef PLANEDATAGENERATOR_H
#define PLANEDATAGENERATOR_H
#include "DataGenerator.h"

class PlaneDataGenerator : public DataGenerator {
    double fuelLevel;
    double altitude;
    double attakAngle;
    double consumptionFuel;
    double echelon;

    void landing();

    void computeFuelLevel();
    void computeConsumptionFuel(int);
    void computeAttakAngle(int);
    void computeAltitude(int);

    int analysis();
    void synchronization();

public:
    double getFuelLevel();
    double getAltitude();
    double getAttakAngle();
    double getConsumptionFuel();

    PlaneDataGenerator(double deltaTime);
    PlaneDataGenerator(double deltaTime, double fuelLevel, double altitude, double attakAngle);
    PlaneDataGenerator(double deltaTime, double minFuelLevel, double maxFuelLevel, double minAltitude, double maxAltitude, double minAttakAngle, double maxAttakAngle);

    void compute() override;
    ~PlaneDataGenerator()override;
};
#endif // PLANEDATAGENERATOR_H
