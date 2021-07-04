#include "DataGenerator.h"

void DataGenerator::setTime(double time)
{
    this->time = time;
};
void DataGenerator::setDeltaTime(double deltaTime)
{
    this->deltaTime = deltaTime;
};
void DataGenerator::setIdentity(char identity)
{
    this->identity = identity;
}

double DataGenerator::getDeltaTime()
{
    return deltaTime;
}
double DataGenerator::getTime()
{
    return time;
}
char DataGenerator::getIdentity()
{
    return identity;
}
DataGenerator::~DataGenerator() {};
