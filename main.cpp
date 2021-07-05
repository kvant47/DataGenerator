#include <iostream>
#include <cmath>
#include <ctime>
#include "DataGenerator.h"
#include "CarDataGenerator.h"
#include "HarmonicMotionDataGenerator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    srand(std::time(NULL));
    CarDataGenerator f(5, 200, rand()%120-30, 20, 0);  // шаг, скорость, температура, расход, обороты.
        //f.setTime(339);
        DataGenerator *first = &f;
        for ( int i = 0; i < 15; i++)
        {
            first->compute();
            cout << endl;
            system("pause");
        }
    return 0;
}
