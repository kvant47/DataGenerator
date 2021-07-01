#ifndef CARDATAGENERATOR_H
#define CARDATAGENERATOR_H
#include "DataGenerator.h"
#include "cmath"
#include "ctime"

class CarDataGenerator : public DataGenerator {
    double speed;
    double fuelLevel;
    double temperature;
    double rotationalSpeed;
    double consumptionFuel;
    int gear;

protected:
    void findGear();
    void computeSpeed(int);
    void computeRotationalSpeed();
    void computeGear(int);
    void computeConsumptionFuel(int);
    void computeFuelLevel();
    void optimalTempurure();
    void computeTemperature();

public:
    void setSpeed(double);
    void setFuelLevel(double);
    void setTemperatur(double);
    void setRotationalSpeed(double);
    void setConsumptionFuel(double);
    void setGear(int);

    double getSpeed();
    double getFuelLevel();
    double getTemperatur();
    double getRotationalSpeed();
    double getConsumptionFuel();
    int getGear();

    CarDataGenerator(int) {} //===== Первый констрктор. Все параметры случайны
    CarDataGenerator(int deltaTime, double speed, double fuelLevel, double temperature, double consumptionFuel) {} //===== Второй констрктор. Все параметры указаны
    CarDataGenerator(int deltaTime, double minSpeed, double maxSpeed, double minFuelLevel, double maxFuelLevel, double minTemperature, double maxTemperature, double minConsumptionFuel, double maxConsumptionFuel) {} //===== Третий констрктор. Все параметры заданые в диапазоне между отчаянием и надеждой

    void  compute() override {}
    ~CarDataGenerator()override;
};
#endif // CARDATAGENERATOR_H
