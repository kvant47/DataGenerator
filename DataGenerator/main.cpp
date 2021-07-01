#include <iostream>
#include <cmath>
#include <ctime>
#include "DataGenerator.h"
#include "HarmonicMotionDataGenerator.h"
using namespace std;


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

