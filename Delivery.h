#pragma once
#include <string>

class Order;

// абстрактный класс для всех способов доставки
class Delivery {
public:
    virtual ~Delivery() = default;

    virtual double getCost(const Order& order) const = 0;
    virtual std::string getEstimatedTime() const = 0;
    virtual bool isAvailable(const Order& order) const = 0;
};
