#ifndef CARDATAGENERATOR_H
#define CARDATAGENERATOR_H
#include "DataGenerator.h"

#include "DataGenerator.h"

class CarDataGenerator : public DataGenerator {
    double speed;
    double fuelLevel;
    double temperature;
    double rotationalSpeed;
    double consumptionFuel;
    int gear;

protected:
    void findGear();
    void findRotationalSpeed(int nextGear);

    void computeFuelLevel();
    void optimalTempurure();
    void computeTemperature();
    void computeSpeed(int gear);
    void computeRotationalSpeed(int nextGear);
    void computeGear(int nextGear);
    void computeConsumptionFuel(int nextGear);

    void engineOff(double *startTemperature);
    bool engineOn();

public:
    void setSpeed(double speed);
    void setFuelLevel(double fuelLevel);
    void setTemperatur(double temperature);
    void setRotationalSpeed(double rotationalSpeed);
    void setConsumptionFuel(double consumptionFuel);
    void setGear(int gear);

    double getSpeed();
    double getFuelLevel();
    double getTemperatur();
    double getRotationalSpeed();
    double getConsumptionFuel();
    int getGear();

    CarDataGenerator(int deltaTime);
    CarDataGenerator(int deltaTime, double speed, double fuelLevel, double temperature, double consumptionFuel, double rotationalSpeed);
    CarDataGenerator(int deltaTime, double minSpeed, double maxSpeed, double minFuelLevel, double maxFuelLevel, double minTemperature, double maxTemperature, double minConsumptionFuel, double maxConsumptionFuel, double minRotationalSpeed, double maxRotationalSpeed);

    void compute() override;

    ~CarDataGenerator()override;
};
#endif // CARDATAGENERATOR_H
