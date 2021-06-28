#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

class DataGenerator{
    int time;
    int deltaTime;
    char identity;

protected:
    void setTime(int);
    virtual void compute() = 0;

public:
    void setDeltaTime(int);
    void setIdentity(char);

    int getDeltaTime();
    int getTime();
    char getIdentity();
    virtual ~DataGenerator() = 0;
};
#endif // DATAGENERATOR_H
