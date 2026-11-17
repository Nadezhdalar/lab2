#pragma once


class Order;

// абстрактный класс для всех акций и скидок
class Discount {
public:
    virtual ~Discount() = default;

    virtual void apply(Order& order) const = 0;
};
