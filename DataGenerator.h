#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

class DataGenerator{
    int time;
    double deltaTime;
    char identity;

protected:
    void setTime(int);

public:
    void setDeltaTime(double);
    void setIdentity(char);

    double getDeltaTime();
    int getTime();
    char getIdentity();
    virtual void compute() = 0;
    virtual ~DataGenerator() = 0;
};
#endif // DATAGENERATOR_H
