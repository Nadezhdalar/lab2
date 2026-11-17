#pragma once
#include "Discount.h"

class PercentDiscount : public Discount {
private:
    double percent_; 

public:
    PercentDiscount(double percent = 10.0);
    void apply(Order& order) const override;
};
