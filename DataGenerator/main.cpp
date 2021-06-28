#include <iostream>
#include <cmath>
#include <ctime>
#include <Windows.h>

using namespace std;

class DataGenerator
{
    int time;
    int deltaTime;
    char identity;

protected:
    void setTime(int time) {
        this->time = time;
    }
    virtual void compute() = 0;

public:
    void setDeltaTime(int deltaTime)
    {
        this->deltaTime = deltaTime;
    }
    void setIdentity(char identity)
    {
        this->identity = identity;
    }

    int getDeltaTime()
    {
        return deltaTime;
    }
    int getTime()
    {
        return time;
    }
    char getIdentity()
    {
        return identity;
    }
     virtual ~DataGenerator() = 0;
};
DataGenerator::~DataGenerator() {};

class HarmonicMotionDataGenerator : public DataGenerator {
    double amplitude;
    double ciclicFrequency;
    double phase;
    double x;

public:
    HarmonicMotionDataGenerator(int deltaTime) {
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

    void setAmplitude(double amplitude)
    {
        this->amplitude = amplitude;
    }
    void setCiclicFrequency(double ciclicFrequency)
    {
        this->ciclicFrequency = ciclicFrequency;
    }
    void setPhase(double phase)
    {
        this->phase = phase;
    }
    void setX(double x) {
        this->x = x;
    }

    double getAmplitude()
    {
        return amplitude;
    }
    double getCiclicFrequency() {
        return ciclicFrequency;
    }
    double getPhase() {
        return phase;
    }
    double getX() {
        return x;
    }

    void compute() override {
        setX(getAmplitude() * sin(getCiclicFrequency() * getTime() + getPhase()));
       setTime(getTime() + getDeltaTime());
    }

     ~HarmonicMotionDataGenerator()override {}
};

int main()
{
    srand(std::time(NULL));
    HarmonicMotionDataGenerator f(1);
    DataGenerator* first = &f;
    cout <<"ampl: " << f.getAmplitude() << "\t";
    cout <<"chastota: " << f.getCiclicFrequency() << "\t";
    cout << "phasa: " << f.getPhase() << endl << endl;
    for (int i = 0; i < 10; i++)
    {
        f.compute();
        cout << " X: " << f.getX() << endl;
    }
    return 0;
}

