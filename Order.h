#pragma once
#include <vector>
#include <string>
#include <memory>
#include "IObservable.h"
#include "Product.h"
#include "OrderStatus.h"
#include <iostream>

class Delivery;
class Discount;

class Order : public IObservable {
private:
    int id_;
    std::string customer_;
    std::vector<std::shared_ptr<Product>> items_;
    OrderStatus status_;
    std::shared_ptr<Delivery> delivery_;
    std::vector<std::shared_ptr<Discount>> discounts_;

    double totalPrice_;
    double deliveryCost_;
    std::vector<IObserver*> observers_;

public:
    Order(int id, const std::string& customer, const std::vector<std::shared_ptr<Product>>& items);
    // конструкторы копирования и перемещения по правилу пяти
    Order(const Order& other) = default;
    Order& operator=(const Order& other) = default;
    Order(Order&& other) noexcept = default;
    Order& operator=(Order&& other) noexcept = default;

    int getId() const;
    std::string getCustomer() const;
    OrderStatus getStatus() const;
    double getTotalPrice() const;
    double getDeliveryCost() const;
    double getTotalWeight() const;
    std::shared_ptr<Delivery> getDelivery() const;
    const std::vector<std::shared_ptr<Product>>& getItems() const;

    void setStatus(OrderStatus newStatus);
    void setTotalPrice(double price);
    void setDeliveryCost(double cost);
    void setDelivery(std::shared_ptr<Delivery> delivery);
    void addDiscount(std::shared_ptr<Discount> discount);
    void applyDiscount(const Discount& discount);
    void addItem(std::shared_ptr<Product> item);
    void removeItem(int productId);

    // методы паттерна наблюдатель 
    void subscribe(IObserver* observer) override;
    void unsubscribe(IObserver* observer) override;
    void notify(const OrderEvent& event) override;
};

Order& operator+(Order& order, const Discount& discount);
Order& operator<<(Delivery& delivery, Order& order);
std::ostream& operator<<(std::ostream& os, const Order& order);
bool operator==(const Order& left, const Order& right);
