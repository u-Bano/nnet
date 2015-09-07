#ifndef WGTINIT_H
#define WGTINIT_H

#include "help.h"
#include <cmath>
#include <map>
#include <memory>
#include <string>

using namespace std;

class WeightInitialization {
public:
    virtual double generateWeight(const size_t &inputsNumber) = 0;
};

class BroadWeightInitialization : public WeightInitialization {
public:
    virtual double generateWeight(const size_t &inputsNumber) override {
        return Random::getInstance()->normalDistribution<double>(
            0.0, 
            1.0);
    }
};

class SharpWeightInitialization : public WeightInitialization {
public:
    virtual double generateWeight(const size_t &inputsNumber) override {
        return Random::getInstance()->normalDistribution<double>(
            0.0, 
            invert(sqrt(inputsNumber)));
    }
};

inline const map<string, shared_ptr<WeightInitialization>> *getWeightInitializations() {
    static const map<string, shared_ptr<WeightInitialization>> WEIGHT_INITIALIZATIONS = {
        {"broad", newInstance<BroadWeightInitialization>()}, 
        {"sharp", newInstance<SharpWeightInitialization>()}, 
    };
    return &WEIGHT_INITIALIZATIONS;
}

#endif
