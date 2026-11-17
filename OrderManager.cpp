#include "OrderManager.h"
#include "LoggingProxy.h"
#include <iostream>
#include <algorithm>

// конструктор менеджера заказов
OrderManager::OrderManager(int maxActiveOrders)
    : turnover_(0.0), maxActiveOrders_(maxActiveOrders), activeOrdersCount_(0), paidOrdersCount_(0), nextOrderId_(1) {}

// создание нового заказа с проверкой лимита и подпиской на события
std::shared_ptr<Order> OrderManager::createOrder(const std::string& customer, const std::vector<std::shared_ptr<Product>>& items) {
    if (activeOrdersCount_ >= maxActiveOrders_) {
        std::cout << "Превышен лимит активных заказов (" << maxActiveOrders_ << ")\n";
        return nullptr;
    }

    auto newOrder = std::make_shared<Order>(nextOrderId_++, customer, items);
    newOrder->subscribe(this);

    orders_.push_back(newOrder);
    activeOrdersCount_++;

    if (std::find(customers_.begin(), customers_.end(), customer) == customers_.end()) {
        customers_.push_back(customer);
    }

    LoggingProxy::log("MANAGER", "создан заказ #" + std::to_string(newOrder->getId()) + " (" + customer + "), активных: " + std::to_string(activeOrdersCount_));
    return newOrder;
}

// обработка событий изменения статуса заказа
void OrderManager::onOrderEvent(const OrderEvent& event) {
    if (event.getNewStatus() == OrderStatus::Paid) {
        for (const auto& order : orders_) {
            if (order != nullptr && order->getId() == event.getOrderId()) {
                turnover_ += order->getTotalPrice();
                paidOrdersCount_++;
                std::cout << "Заказ #" << event.getOrderId() << " оплачен. Оборот: " << turnover_
                          << " руб., оплачено заказов: " << paidOrdersCount_ << "\n";
                break;
            }
        }
    }
    else if (event.getNewStatus() == OrderStatus::Cancelled || event.getNewStatus() == OrderStatus::Delivered) {
        if (activeOrdersCount_ > 0) {
            activeOrdersCount_--;
        }
        std::cout << "Заказ #" << event.getOrderId() << " закрыт. Активных заказов: "
                  << activeOrdersCount_ << "/" << maxActiveOrders_ << "\n";
    }

    if (activeOrdersCount_ >= maxActiveOrders_) {
        std::cout << "Достигнут лимит активных заказов (" << activeOrdersCount_ << "/" << maxActiveOrders_ << ")\n";
    }
}

// изменение статуса заказа через менеджер
void OrderManager::updateStatus(std::shared_ptr<Order> order, OrderStatus newStatus) {
    if (order != nullptr) {
        order->setStatus(newStatus);
    }
}

double OrderManager::getTurnover() const {
    return turnover_;
}

int OrderManager::getCustomerCount() const {
    return static_cast<int>(customers_.size());
}

int OrderManager::getActiveOrdersCount() const {
    return activeOrdersCount_;
}
