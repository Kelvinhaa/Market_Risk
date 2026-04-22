#pragma once
#include "issubscriber.h"

class Logger : public ISubscriber{
public:
    void on_price(const price_packet& p) override;
    std::string name() const override {return "Logger";};
};