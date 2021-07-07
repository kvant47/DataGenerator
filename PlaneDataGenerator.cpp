#include <iostream>
#include <cmath>
#include <ctime>
#include "DataGenerator.h"
#include "PlaneDataGenerator.h"

using namespace std;

void PlaneDataGenerator:: landing() {
        ///cout << " Посадка " << endl;
        if (altitude > 0) {
            if (getDeltaTime() < 1)
            {
                consumptionFuel = consumptionFuel - 6 * getDeltaTime();
                if (attakAngle < 5)	attakAngle = attakAngle + 0.125 * getDeltaTime();
                if (attakAngle > 5)	attakAngle = attakAngle - 0.125 * getDeltaTime();
                else altitude = altitude - 0.5 * getDeltaTime();
                if (altitude < 0) altitude = 0;
                computeFuelLevel();
            }
            else {
                if (consumptionFuel > 2900) consumptionFuel = consumptionFuel - 6;
                if (attakAngle < 5)	attakAngle = attakAngle + 0.125;
                if (attakAngle > 5)	attakAngle = attakAngle - 0.125;
                if (altitude > 25) computeAltitude(0);
                else altitude = altitude - 0.5;
                if (altitude < 0) altitude = 0;
                computeFuelLevel();
            }
        }
        else {
            computeFuelLevel();
            if (getDeltaTime() >= 1)	consumptionFuel = consumptionFuel - 10;
            else consumptionFuel = consumptionFuel - 10 * getDeltaTime();
            attakAngle = 0;
            altitude = 0;
            if (fuelLevel < 600) {
                fuelLevel = 600;
                consumptionFuel = 0;
            }
        }
    };

void PlaneDataGenerator::computeFuelLevel() {
        if (getDeltaTime() < 1) fuelLevel = fuelLevel - ((consumptionFuel / 3600.0) * getDeltaTime());			// ЕСЛИ deltaTime < 1
        else fuelLevel = fuelLevel - (consumptionFuel / 3600.0);
    };
void PlaneDataGenerator::computeConsumptionFuel(int situation) {
        switch (situation) {
        case 1:
            if (getDeltaTime() < 1) consumptionFuel = consumptionFuel - 6 * getDeltaTime();
            else {
                if (consumptionFuel > 3000) consumptionFuel = consumptionFuel - 6;
                if (consumptionFuel < 3000) consumptionFuel = consumptionFuel + 6;
            }
            break;
        case 2:
            if (getDeltaTime() < 1) consumptionFuel = consumptionFuel - 6 * getDeltaTime();
            else if (consumptionFuel < 3100) consumptionFuel = consumptionFuel + 6;
            break;
        case 3:
            if (getDeltaTime() < 1) consumptionFuel = consumptionFuel - 6 * getDeltaTime();
            else if (consumptionFuel > 3000) consumptionFuel = consumptionFuel - 6;
            break;
        default:
            if (getDeltaTime() < 1) consumptionFuel = consumptionFuel - 6 * getDeltaTime();
            else if (consumptionFuel > 2900) consumptionFuel = consumptionFuel - 6;
            break;
        }
    };
void PlaneDataGenerator::computeAttakAngle(int situation) {
        double deltaAttakAngle;
        static double target = 0;
        switch (situation) {
        case 1:
            if (int(getTime()) % 10 == 0) target = 0 + rand() % 11 / 10.0;
            if (altitude - echelon > 50) target = -1;
            if (echelon - altitude > 50) target = 1;
            deltaAttakAngle = 0.3;
            break;
        case 2:  // резкий взлет
            target = 15;
            break;
        case 3:		// умеренный взлет
            target = 10;
            break;
        case 4:	// плавный взлет
            target = 5;
            break;
        case 5:	// резкое снижение
            target = -15;
            break;
        case 6:	// умеренное снижение
            target = -10;
            break;
        case 7:	// плавный снижение
            target = -5;
            break;
        }

        if (target <= attakAngle) deltaAttakAngle = 0.003 * pow((-attakAngle + 16), 2) + 0.2;	// если опускаем нос
        if (target >= attakAngle) deltaAttakAngle = 0.003 * pow((attakAngle + 16), 2) + 0.2;	//если поднимаем нос
        if (attakAngle < -15) deltaAttakAngle = 0.3;   // на случай когда самолет резко пикирует. можно вызвать только пользователем
        if (deltaAttakAngle > 0.3) deltaAttakAngle = 0.3;		//ограничений резкой смены угла
        if (deltaAttakAngle < -0.3) deltaAttakAngle = -0.3;		//ограничений резкой смены угла

        if (getDeltaTime() < 1) deltaAttakAngle = deltaAttakAngle * getDeltaTime();
        if (attakAngle < target) attakAngle = attakAngle + deltaAttakAngle;
        if (attakAngle > target) attakAngle = attakAngle - deltaAttakAngle;
    };
void PlaneDataGenerator::computeAltitude(int situation) {
        double deltaAltitude;
        if (((1 < situation) && (situation < 4)) || (attakAngle > 0)) {
            if (2970 > consumptionFuel) deltaAltitude = deltaAltitude = (220 + 27 * (5 - attakAngle)) *(sin(attakAngle * 3.14 / 180) / sin((90 - attakAngle)*3.14 / 180));
            if ((2970 <= consumptionFuel) && (consumptionFuel< 3030)) deltaAltitude = (220 + 23 * (10 - attakAngle)) *(sin(attakAngle * 3.14 / 180) / sin((90 - attakAngle)*3.14 / 180));
            if (3030 <= consumptionFuel) deltaAltitude = (220 + 20 * (15 - attakAngle)) *(sin(attakAngle * 3.14 / 180) / sin((90 - attakAngle)*3.14 / 180));
            if (attakAngle < 0) deltaAltitude = (200 + 20 * (-attakAngle)) *(sin(attakAngle * 3.14 / 180) / sin((90 - attakAngle)*3.14 / 180));
        }
        else deltaAltitude = (400 * (sin(attakAngle * 3.14 / 180) / sin((90 - attakAngle)*3.14 / 180)));
        deltaAltitude = (deltaAltitude / 3600.0) * 1000;
        if ((((situation == 0) && (deltaAltitude > -3))) && (altitude > 50)) deltaAltitude = -3;
        if ((((situation == 0) && (deltaAltitude > -1))) && (altitude < 50)) deltaAltitude = -1;
        if (getDeltaTime() < 1) deltaAltitude = deltaAltitude * getDeltaTime();
        ///cout << "Приращение высоты: " << deltaAltitude << "\t";
        altitude = altitude + deltaAltitude;
    };

int PlaneDataGenerator::analysis() {
        if (int(getTime()) % 1200 == 0) {  //смена эшелона каждые 20 минут
            echelon = rand() % 4000 + 5000;
            while (int(echelon) % 100 != 0) echelon--; // целое число, кратное ста
        }
        if (fuelLevel < 2000) {
            ///cout << "Снижение на посадку." << endl;
            echelon = 50;
            if (altitude < 200) return 0;
            else {
                if (9000 < altitude) return 5;									// резкий подъем
                if (7000 < altitude) return 6;									// умеренный подъем
                if (altitude < 5000) return 7;									// плавный подъем
            }
        }									// если мало топлива запускается "посадка"
        if ((echelon - 150 <= altitude) && (altitude <= echelon + 150)) return 1;		//самолет попадает в эшелон. держим эту высоту
        if (altitude + 150 < echelon) {												// высота меньше, чем эшелон, поднимаемся
            if (2000 <  echelon - altitude) return 2;										// резкий подъем
            if ((500 <= echelon - altitude) && (echelon - altitude < 2000)) return 3;		// умеренный подъем
            if (150 <= echelon - altitude < 500) return 4;									// плавный подъем
        }
        if (altitude - 150 > echelon) {														// высота больше, чем эшелон, снижаемся
            if (2000 < altitude - echelon) return 5;										// резкий подъем
            if ((500 <= altitude - echelon) && (altitude - echelon) <2000) return 6;		// умеренный подъем
            if (150 <= altitude - echelon < 500) return 7;									// плавный подъем
        }
    };
void PlaneDataGenerator::synchronization() {
        static int situation;
        if (situation != 10) {    // если врезался все параметры обнуляются, анализ ситуации больше не запускается
            situation = analysis();
        }
        if (((situation != 0) && (altitude < 0)) || (situation == 10)) {  // если самолет врезался в землю.
            altitude = 0;
            consumptionFuel = 0;
            fuelLevel = 0;
            attakAngle = 0;
            situation = 10;
        }
        else {
            if (situation == 0) {
                landing();
            }
            else {
                computeConsumptionFuel(situation);
                computeFuelLevel();
                computeAttakAngle(situation);
                computeAltitude(situation);
            }
        }
    /*	cout << "Время: " << getTime() << "\t";
        cout << "Ситуация: " << situation << "\t";								//отладочная строка
        cout << "Расход: " << consumptionFuel << "\t";							//отладочная строка
        cout << " Уровень топлива: " << fuelLevel << "\t";						//отладочная строка
        cout << "Угол атаки: " << attakAngle << "\t";							//отладочная строка
        cout << "Высота: " << altitude << "\t";									//отладочная строка
        cout << "Эшелон: " << echelon << endl << endl;							//отладочная строка */
        if (getDeltaTime() < 1) setTime(getTime() + getDeltaTime());
        else setTime(getTime() + 1);
    };

double PlaneDataGenerator::getFuelLevel() {
        return fuelLevel;
    };
double PlaneDataGenerator::getAltitude() {
        return altitude;
    };
double PlaneDataGenerator::getAttakAngle() {
        return attakAngle;
    };
double PlaneDataGenerator::getConsumptionFuel() {
        return consumptionFuel;
    };

PlaneDataGenerator::PlaneDataGenerator(double deltaTime) {
        srand(std::time(NULL));
        setTime(0);
        setDeltaTime(deltaTime);
        fuelLevel = rand() % 19000 + 1000;  //от 1000 до 20000
        altitude = rand() % 12000 + 1000;   // от 1000 до 13000
        attakAngle = rand() % 30 - 15;     // от -15 до 15
        echelon = rand() % 4000 + 5000;
        while (int(echelon) % 100 != 0) echelon--; // целое число, кратное ста
        consumptionFuel = rand() % 200 + 2900;
    };
PlaneDataGenerator::PlaneDataGenerator(double deltaTime, double fuelLevel, double altitude, double attakAngle) {
        srand(std::time(NULL));
        setTime(0);
        setDeltaTime(deltaTime);
        this->fuelLevel = fuelLevel;  //от 2000 до 20000
        this->altitude = altitude;   // от 1000 до 13000
        this->attakAngle = attakAngle;     // от -15 до 15
        echelon = rand() % 4000 + 5000;
        while (int(echelon) % 100 != 0) echelon--; // целое число, кратное ста
        consumptionFuel = rand() % 200 + 2900;
    };
PlaneDataGenerator::PlaneDataGenerator(double deltaTime, double minFuelLevel, double maxFuelLevel, double minAltitude, double maxAltitude, double minAttakAngle, double maxAttakAngle){
    srand(std::time(NULL));
    setTime(0);
    setDeltaTime(deltaTime);
    fuelLevel = minFuelLevel + rand() % int(maxFuelLevel - minFuelLevel);
    altitude = minAltitude + rand() % int(maxAltitude - minAltitude);
    attakAngle = minAttakAngle + rand() % int(maxAttakAngle - minAttakAngle);
    echelon = rand() % 4000 + 5000;
    while (int(echelon) % 100 != 0) echelon--; // целое число, кратное ста
    consumptionFuel = rand() % 200 + 2900;
};

void PlaneDataGenerator::compute() {
    if (getDeltaTime() < 1) synchronization();
    else {
        for (int i = 0; i < getDeltaTime(); i++)
        {
            synchronization();
        }
    }
};
PlaneDataGenerator::~PlaneDataGenerator() {};
