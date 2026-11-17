#pragma once
#include "Discount.h"

class CashbackDiscount : public Discount {
private:
    double cashbackPercent_; 

public:
    CashbackDiscount(double cashbackPercent = 5.0);
    void apply(Order& order) const override;
};
