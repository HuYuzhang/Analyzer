#pragma once
#include<string>
using namespace std;
class DeepApplyer
{
private:
    string modelName;
    string deployName;
public:
    DeepApplyer(string model, string deploy);
    ~DeepApplyer();
};

