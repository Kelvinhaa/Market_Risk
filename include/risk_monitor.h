#pragma once

#include "issubscriber.h"

class RiskMonitor : public ISubscriber{
public:
    RiskMonitor(const std::string& name, 
                double risk_free_rate=0.0);
    
private:
    std::string name_;
    double risk_free_rate_;
    double price
};  