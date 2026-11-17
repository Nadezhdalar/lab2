#pragma once
#include <memory>
#include "ProductType.h"

class Product {
private:
    int id_;
    int quantity_;
    double currentPrice_;
    std::shared_ptr<ProductType> type_;

public:
    Product(int id, int quantity, double currentPrice, std::shared_ptr<ProductType> type);

    int getId() const;
    int getQuantity() const;
    double getCurrentPrice() const;
    std::shared_ptr<ProductType> getType() const;

    double getWeight() const;
    double getTotalPrice() const;
    void changeQuantity(int delta);
};
