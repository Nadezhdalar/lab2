#pragma once
#include "Discount.h"
#include "Product.h"
#include <memory>

class GiftDiscount : public Discount {
private:
    std::shared_ptr<Product> giftProduct_; 

public:
    GiftDiscount(std::shared_ptr<Product> giftProduct);
    void apply(Order& order) const override;
};
