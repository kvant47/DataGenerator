#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

class DataGenerator
{
    double time;
    double deltaTime;
    char identity;

protected:
    void setTime(double);

public:
    void setDeltaTime(double);
    void setIdentity(char);

    double getDeltaTime();
    double getTime();
    char getIdentity();
    virtual void compute() = 0;
    virtual ~DataGenerator() = 0;
};

#endif // DATAGENERATOR_H
