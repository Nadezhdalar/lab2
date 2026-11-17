#pragma once
#include <vector>
#include <string>
#include <memory>
#include "IObserver.h"
#include "Order.h"
#include "Product.h"
#include "OrderStatus.h"

class OrderManager : public IObserver {
private:
    std::vector<std::shared_ptr<Order>> orders_; // список всех заказов
    std::vector<std::string> customers_;         
    double turnover_;                            
    int maxActiveOrders_;                        
    int activeOrdersCount_;                     
    int paidOrdersCount_;                        
    int nextOrderId_;                            

public:
    OrderManager(int maxActiveOrders = 5);

    // создание заказа с проверкой лимита и подпиской на события
    std::shared_ptr<Order> createOrder(const std::string& customer, const std::vector<std::shared_ptr<Product>>& items);

    // метод интерфейса реакция на изменение статуса заказа
    void onOrderEvent(const OrderEvent& event) override;

    // вспомогательный метод для смены статуса через менеджер
    void updateStatus(std::shared_ptr<Order> order, OrderStatus newStatus);

    double getTurnover() const;
    int getCustomerCount() const;
    int getActiveOrdersCount() const;
};
