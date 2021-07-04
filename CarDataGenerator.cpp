#include <iostream>
#include <cmath>
#include <ctime>
#include "DataGenerator.h"
#include "CarDataGenerator.h"

using namespace std;


void CarDataGenerator::findGear() {
    if (speed == 0) gear = 0;
    else
        if ((0 < speed) && (speed < 20)) {
            gear = 1;
        }
        else
            if ((20 <= speed) && (speed < 40)) {
                gear = 2;
            }
            else
                if ((40 <= speed) && (speed < 60)) {
                    gear = 3;
                }
                else
                    if ((60 <= speed) && (speed < 80)) {
                        gear = 4;
                    }
                    else
                        if (80 <= speed) {
                            gear = 5;
                        }
};
void CarDataGenerator::findRotationalSpeed(int nextGear) {
    switch (gear) {
    case 1:
        rotationalSpeed = 130 * speed;
        if (rotationalSpeed < 800) rotationalSpeed = (rand() % 100) + 800; // не очень красивый выход ситуации, когда машина трогается. Обороты не могут быть ниже 700
        break;
    case 2:
        rotationalSpeed = 85 * speed;
        break;
    case 3:
        rotationalSpeed = 50 * speed;
        break;
    case 4:
        rotationalSpeed = 35 * speed;
        break;
    case 5:
        rotationalSpeed = 30 * speed;
        break;
    }
    if (nextGear == 1) {   //на повышенную
        switch (gear) {
        case 0:
            rotationalSpeed = 130 * speed;
            if (speed == 0) rotationalSpeed = 800;
            if (rotationalSpeed < 800) rotationalSpeed = (rand() % 100) + 800; // не очень красивый выход ситуации, когда машина трогается. Обороты не могут быть ниже 700
            break;
        case 1:
            rotationalSpeed = 85 * speed + 100;
            break;
        case 2:
            rotationalSpeed = 50 * speed + 100;
            break;
        case 3:
            rotationalSpeed = 35 * speed + 100;
            break;
        case 4:
            rotationalSpeed = 30 * speed;
            break;
        }
    }
    if (nextGear == 2) {   //на пониженную
        switch (gear) {
        case 2:
            rotationalSpeed = 130 * speed - 100;
            if (rotationalSpeed < 800) rotationalSpeed = rand() % 100 + 800; // не очень красивый выход ситуации, когда машина трогается. Обороты не могут быть ниже 700
            break;
        case 3:
            rotationalSpeed = 85 * speed - 110;
            break;
        case 4:
            rotationalSpeed = 50 * speed - 100;
            break;
        case 5:
            rotationalSpeed = 35 * speed - 100;
            break;
        }
    }
    if (nextGear == 3) rotationalSpeed = int(6001 * cos(0.065 * consumptionFuel + 4.72));
};

void CarDataGenerator::computeFuelLevel() {
    if (getDeltaTime() < 1) fuelLevel = fuelLevel - ((consumptionFuel / 3600.0) * getDeltaTime());			// ЕСЛИ deltaTime < 1
    else fuelLevel = fuelLevel - (consumptionFuel / 3600.0);
};
void CarDataGenerator::optimalTempurure() {
    temperature = temperature + (rand() % 3 - 1) * ((rand() % 6) / 10.0);
    if (temperature < 88) temperature = temperature + 0.5;
    if (temperature > 92) temperature = temperature - 0.5;
};
void CarDataGenerator::computeTemperature() {
    if ((temperature > 85) && (temperature < 93))	 //проверяем начальную температуру двигателя.
    {
        optimalTempurure();		//если она оптимальная вызывается соответсвующий метод, который ее просто поддерживает
    }
    else {
        static bool dataByCreated = 0;
        static double conFuel = 1 + ((getConsumptionFuel() / 5) - 1) / 10.0;
        static int amplutude = 0;
        static int correction = 0;
        static double ciclicFrq;
        static double phasa;
        static int prevTemperatura;
        prevTemperatura = temperature;
        temperature = (amplutude * cos((ciclicFrq * getTime() * conFuel) + phasa)) + correction;
        if (abs(prevTemperatura - temperature) > 3) { // Костыль на тот случай когда машина стартует после остановки
            dataByCreated = 0;
            temperature = prevTemperatura;
        }

        if (!dataByCreated) {  //  проверка, были ли сгенерированы значения для графика. графиком роста температуры является гармоническая волна.
            if (temperature < 20) {		// если она меньше 20 все значения подбираются индивидуально после чего идет нагрев двиагетля.
                amplutude = -((90 - temperature) / 2.0);   //амплитуда
                correction = (90 + temperature) / 2;	// поднятие графика вверх, попправка
                if (temperature >= 10) 	ciclicFrq = 0.0064;		//набор значений влияющих на частоту (скорость нагрева), зависящую
                if ((0 <= temperature) && (temperature < 10))  ciclicFrq = 0.006;  // от начальной температуры(чем она меньше, тем холоднее на улице ->
                if ((-10 <= temperature) && (temperature < 0)) ciclicFrq = 0.0055; // -> больше времени нужно на прогрев)
                else { ciclicFrq = 0.0045; }
                phasa = 0;            //грфик для каждого параметра свой, начальная фаза не нужна.
            }
            if ((temperature >= 20) && (temperature < 87))
            {															 // если начальная температура от 20 до 85 все параметры
                amplutude = -35.0;										// считаются пренебрежима малыми. График один для всех наборов
                correction = 55;										// отличие в начальной фазе, зависящей от стартовой температуры
                ciclicFrq = 0.0064;
                phasa = acos((temperature - correction) / amplutude);
            }
            if (temperature > 95)    // температура больше 95. перегрев двигателя. постепеное снижение до приемлемого уровня
            {
                amplutude = 35;
                correction = 70;
                ciclicFrq = 0.005;
                phasa = 0;
            }
            dataByCreated = 1;
        }
        temperature = (amplutude * cos((ciclicFrq * getTime() * conFuel) + phasa)) + correction;
        ///	cout << "Время: " << getTime() <<"     Температура: " << temperature  << endl;					//отладочная строка
    }
};
void CarDataGenerator::computeSpeed(int gear) {
        switch (gear) {
        case 0:
            speed = 0;
            break;
        case 1:
            speed = rotationalSpeed / 130;
            break;
        case 2:
            speed = rotationalSpeed / 85;
            break;
        case 3:
            speed = rotationalSpeed / 50;
            break;
        case 4:
            speed = rotationalSpeed / 35;
            break;
        case 5:
            speed = rotationalSpeed / 30;
            break;
        }
};
void CarDataGenerator::computeRotationalSpeed(int nextGear) {
    int lastRotationalSpeed = rotationalSpeed;
    rotationalSpeed = int(6001 * cos(0.065 * consumptionFuel + 4.72));
    if (nextGear == 0) {
        if (getDeltaTime() >= 1) {
            switch (gear) {		  // ограничеваем резкую смен оборотов для каждой скорости индивидуально ПРИ ШАГЕ >= 1!!!!
            case 1:
                if ((rotationalSpeed - lastRotationalSpeed) > 1000) rotationalSpeed = lastRotationalSpeed + 1200;
                if ((rotationalSpeed - lastRotationalSpeed) < -1000) rotationalSpeed = lastRotationalSpeed - 500;
                break;
            case 2:
                if ((rotationalSpeed - lastRotationalSpeed) > 750) rotationalSpeed = lastRotationalSpeed + 760;
                if ((rotationalSpeed - lastRotationalSpeed) < -750) rotationalSpeed = lastRotationalSpeed - 370;
                break;
            case 3:
                if ((rotationalSpeed - lastRotationalSpeed) > 400) rotationalSpeed = lastRotationalSpeed + 450;
                if ((rotationalSpeed - lastRotationalSpeed) < -400) rotationalSpeed = lastRotationalSpeed - 200;
                break;
            case 4:
                if ((rotationalSpeed - lastRotationalSpeed) > 310) rotationalSpeed = lastRotationalSpeed + 300;
                if ((rotationalSpeed - lastRotationalSpeed) < -310) rotationalSpeed = lastRotationalSpeed - 160;
                break;
            case 5:
                if ((rotationalSpeed - lastRotationalSpeed) > 260) rotationalSpeed = lastRotationalSpeed + 250;
                if ((rotationalSpeed - lastRotationalSpeed) < -260) rotationalSpeed = lastRotationalSpeed - 150;
                break;
            }
        }
        else {
            switch (gear) {		  // ограничеваем резкую смен оборотов для каждой скорости индивидуально ПРИ ШАГЕ < 1!!!!
            case 1:
                if ((rotationalSpeed - lastRotationalSpeed) > (1000 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed + (1200 * getDeltaTime());
                if ((rotationalSpeed - lastRotationalSpeed) < -(1000 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed - (500 * getDeltaTime());
                break;
            case 2:
                if ((rotationalSpeed - lastRotationalSpeed) > (750 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed + (760 * getDeltaTime());
                if ((rotationalSpeed - lastRotationalSpeed) < -(750 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed - (370 * getDeltaTime());
                break;
            case 3:
                if ((rotationalSpeed - lastRotationalSpeed) > (400 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed + (450 * getDeltaTime());
                if ((rotationalSpeed - lastRotationalSpeed) < -(400 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed - (200 * getDeltaTime());
                break;
            case 4:
                if ((rotationalSpeed - lastRotationalSpeed) > (310 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed + (300 * getDeltaTime());
                if ((rotationalSpeed - lastRotationalSpeed) < (-310 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed - (160 * getDeltaTime());
                break;
            case 5:
                if ((rotationalSpeed - lastRotationalSpeed) > (260 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed + (250 * getDeltaTime());
                if ((rotationalSpeed - lastRotationalSpeed) < -(260 * getDeltaTime())) rotationalSpeed = lastRotationalSpeed - (150 * getDeltaTime());
                break;
            }
        }
    }
    static bool haveRotationalSpeed = 0;
    if (!haveRotationalSpeed) {					//при первом попадании в метод обороты "подхватываются" от скорости
        findRotationalSpeed(0);
        haveRotationalSpeed = 1;
    }
};
void CarDataGenerator::computeGear(int nextGear) {
    static bool gearGenerated = 0;
    if (!gearGenerated) {
        findGear();
        gearGenerated = 1;
    }	   //подбор стартовой передачи

    if (nextGear == 1) { gear++; } // переключение на повышенную
    if (nextGear == 2) { gear--; } //переключение на пониженную
    if (nextGear == 3) { gear = 0; }
};
void CarDataGenerator::computeConsumptionFuel(int nextGear) {
    static double deltaConsumptionFuel = rand() % 7 + (rand() % 10 / 10.0);
    static int  counter = 0;
    if (int(getTime()) % 20 == 0) {				//параметры обновляются раз в 15 секунд
        target = rand() % 25;
        if (gear == 5) 	counter++;
        do {
            deltaConsumptionFuel = rand() % 6 + (rand() % 10 / 10.0);
            if (getDeltaTime() < 1) deltaConsumptionFuel = deltaConsumptionFuel * getDeltaTime(); // Если deltaTime < 1
        } while (deltaConsumptionFuel == 0);
        if (counter > 0) { //если слишком долго едем на 5 скорости убавляем расход, чтобы было динамичнее
            target = 3;
            deltaConsumptionFuel = 2;
            counter = 0;
        }
    }
    if (target <= 2) deltaConsumptionFuel = 1; //делаем остановку чуть более реальной
    if (consumptionFuel > target) consumptionFuel = consumptionFuel - deltaConsumptionFuel;
    if (consumptionFuel < target) consumptionFuel = consumptionFuel + deltaConsumptionFuel;
    if (nextGear != 0) {						// высчитывание расхода ТОЛЬКО ПРИ ПЕРЕКЛЮЧЕНИИ ПЕРЕДАЧИ
        consumptionFuel = -((1000 / 69.0) * acos(rotationalSpeed / 6000.0) - 4700 / 69.0) / 10.0;
        consumptionFuel = consumptionFuel * 10;
        consumptionFuel = (int(consumptionFuel) / 10.0);
        consumptionFuel = consumptionFuel + 0.3;
        if (nextGear == 3) consumptionFuel = 2;
        if (((nextGear == 1) && (consumptionFuel < 7)) && (gear == 4)) consumptionFuel = 7; // 5 скорость "длиннее". модификатор только для нее
    }
    if (consumptionFuel >= 24) consumptionFuel = 24;  // защита от слишком больших оборотов
    if (((fuelLevel >= 1) && (speed != 0)) && ((consumptionFuel < 2) && (gear != 1)))  consumptionFuel = 2; //машина едет, водитель бросает газ. Чтобы она не заглохла.
    //cout << "Должно потребляться: " << target << "\t";
    //cout << "Шаг потребления: " << deltaConsumptionFuel << endl;
};

void CarDataGenerator::engineOff(double *startTemperature) {
    static double koefficient;
    if (*startTemperature > 20) *startTemperature = 10; // если изначально двигатель был прогрет, машина охлаждается до 10 градусов
    if (*startTemperature >= 10) koefficient = 0.02;
    if ((0 <= *startTemperature) && (*startTemperature < 10)) koefficient = 0.03;
    if ((-10 <= *startTemperature) && (*startTemperature < 0)) koefficient = 0.04;
    if (-10 > *startTemperature) koefficient = 0.06;
    if (int(temperature) > int(*startTemperature)) {
        if (getDeltaTime() < 1) koefficient = koefficient * getDeltaTime();		// ЕСЛИ deltaTime < 1
        temperature = temperature - koefficient;
    }
    gear = 0;
    consumptionFuel = 0;
    static int startSpeed;
    rotationalSpeed = 0;
    if (speed != 0) {
        startSpeed = speed;
        speed = startSpeed - 1.2;
        if (speed < 0) speed = 0;
    }
    if (getDeltaTime() < 1) speed = speed * getDeltaTime();
    ///printEverySecond();			//ОТЛАДОЧНАЯ СТРОКА
};
bool CarDataGenerator::engineOn() {
    static bool engineOn = 1;
    if ((fuelLevel < 1) || (consumptionFuel < 1.7)) engineOn = 0;
    if (((fuelLevel > 1) && (engineOn == 0)) && (getTime() > 0)) {
        if (int(getTime()) % 10 == 0) {
            engineOn = 1;
            consumptionFuel = 1.8;
            target = 10;
        }
    }
    return engineOn;
};
void CarDataGenerator::synchronization() {
    static double startTemperature = temperature;				// начальная температура, чтобы было к чему вернуться
    double *pStartTemperature = &startTemperature;
    static int nextGear;										// флаг о переключении скорости
    if (engineOn()) {
        static bool first = 0;

        if (first == 0) computeGear(0);
        if (nextGear != 0) {
            findRotationalSpeed(nextGear);
        }
        if (first) {											//в первый проход по методу, генерация не должна сработать
            computeConsumptionFuel(nextGear);					//не зависит ни от чего (только от передачи при переключении)
            computeTemperature();								//зависит от потребления топлива
            computeFuelLevel();									//зависит от потребления топлива
        }

        if (nextGear == 0) computeRotationalSpeed(nextGear);			//зависит от потребления топлива
        computeGear(nextGear);											//зависит от оборотов
        nextGear = 0;													//остаться на той же
        if ((gear == 0) && (consumptionFuel > 2)) { nextGear = 1; }		// старт
        if ((rotationalSpeed > 3100) && (gear < 5)) { nextGear = 1; }	//следующая скорость
        if ((rotationalSpeed < 1900) && (gear > 1)) { nextGear = 2; }	//предыдущая скорость
        if ((gear == 1) && (consumptionFuel < 2)) { nextGear = 3; }		//нейтраль, но двигатель работает
        if (first)	computeSpeed(gear);									//зависит от передачи и оборотов
        first = true;
        //printEverySecond();
    }
    else {
        engineOff(pStartTemperature);
    }
    if (getDeltaTime() < 1) setTime(getTime() + getDeltaTime());
    else setTime(getTime() + 1);
};

void CarDataGenerator::printEverySecond() {
    cout << endl;
    cout << "Время: " << getTime() << "\t";
    cout << "Температура: " << int(temperature) << "\t\t";					//отладочная строка
    cout << "Уровень топлива: " << int(fuelLevel) << "\t";					//отладочная строка
    cout << "Расход: " << consumptionFuel << "\t";							//отладочная строка
    cout << "Обороты: " << int(rotationalSpeed) << "\t";					//отладочная строка
    cout << "Скорость: " << int(speed) << "\t";								//отладочная строка
    cout << "Передача: " << gear << endl;									//отладочная строка
};
void CarDataGenerator::printFinalyValues() {
    cout << endl;
    cout << "							ИТОГОВЫЕ ЗНАЧЕНИЯ " << endl;
    cout << "Время: " << getTime() << "\t";
    cout << "Температура: " << int(temperature) << "\t\t";					//отладочная строка
    cout << "Уровень топлива: " << int(fuelLevel) << "\t";					//отладочная строка
    cout << "Расход: " << consumptionFuel << "\t";							//отладочная строка
    cout << "Обороты: " << int(rotationalSpeed) << "\t";					//отладочная строка
    cout << "Скорость: " << int(speed) << "\t";								//отладочная строка
    cout << "Передача: " << gear << endl;									//отладочная строка
    cout << endl;
};

void CarDataGenerator::setSpeed(double speed) {
    this->speed = speed;
};
void CarDataGenerator::setFuelLevel(double fuelLevel) {
        this->fuelLevel = fuelLevel;
};
void CarDataGenerator::setTemperatur(double temperature) {
    this->temperature = temperature;
};
void CarDataGenerator::setRotationalSpeed(double rotationalSpeed) {
    this->rotationalSpeed = rotationalSpeed;
};
void CarDataGenerator::setConsumptionFuel(double consumptionFuel) {
    this->consumptionFuel = consumptionFuel;
};
void CarDataGenerator::setGear(int gear) {
    this->gear = gear;
};

double CarDataGenerator::getSpeed() {
    return speed;
};
double CarDataGenerator::getFuelLevel() {
    return fuelLevel;
};
double CarDataGenerator::getTemperatur() {
    return temperature;
};
double CarDataGenerator::getRotationalSpeed() {
    return rotationalSpeed;
};
double CarDataGenerator::getConsumptionFuel() {
    return consumptionFuel;
};
int CarDataGenerator::getGear() {
    return gear;
};

CarDataGenerator::CarDataGenerator(double deltaTime) {
    srand(std::time(NULL));
    setTime(0);
    setDeltaTime(deltaTime);
    speed = rand() % 80;					// скорость до 200
    fuelLevel = rand() % 51;				// топливо до 50 литров
    temperature = rand() % 111 - 25;		// начальная температура дивгателя от -25 до 85
    consumptionFuel = 2 + (rand() % 20);	// начальный расход топлива л/час до 21.
    target = rand() % 22 + 2;
};
CarDataGenerator::CarDataGenerator(double deltaTime, double speed, double fuelLevel, double temperature, double rotationalSpeed) {
    setTime(0);
    setDeltaTime(deltaTime);
    this->speed = speed;
    this->fuelLevel = fuelLevel;
    this->temperature = temperature;
    consumptionFuel = 2 + (rand() % 20);
    target = rand() % 22 + 2;
    this->rotationalSpeed = rotationalSpeed;
};
CarDataGenerator::CarDataGenerator(double deltaTime, double minSpeed, double maxSpeed, double minFuelLevel, double maxFuelLevel, double minTemperature, double maxTemperature, double minRotationalSpeed, double maxRotationalSpeed) {
        srand(std::time(NULL));
        setTime(0);
        setDeltaTime(deltaTime);
        this->speed = minSpeed + rand() % int(maxSpeed - minSpeed);
        this->fuelLevel = minFuelLevel + rand() % int(maxFuelLevel - minFuelLevel);
        this->temperature = minTemperature + rand() % int(maxTemperature - minTemperature);
        consumptionFuel = 2 + (rand() % 20);
        this->rotationalSpeed = minRotationalSpeed + rand() % int(maxRotationalSpeed - minRotationalSpeed);
        target = rand() % 22 + 2;
    };

void CarDataGenerator::compute() {
    if (getDeltaTime() < 1) synchronization();
    else {
    for (int i = 0; i < getDeltaTime(); i++)
    {
        synchronization();
    }
}
    ///printFinalyValues();
};
CarDataGenerator::~CarDataGenerator() {};
