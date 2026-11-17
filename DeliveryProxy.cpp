#include "DeliveryProxy.h"
#include "Order.h"
#include "LoggingProxy.h"
#include <iostream>

DeliveryProxy::DeliveryProxy(std::shared_ptr<Delivery> realDelivery, const std::string& region)
    : realDelivery_(realDelivery), region_(region) {}

double DeliveryProxy::getCost(const Order& order) const {
    if (realDelivery_ == nullptr) {
        LoggingProxy::log("DELIVERY", "Ошибка: реальный способ доставки не задан!");
        return 0.0;
    }

    int orderId = order.getId();
    double cost = realDelivery_->getCost(order);
    LoggingProxy::log("DELIVERY", "Расчёт доставки для заказа #" + std::to_string(orderId) + ": " + std::to_string(cost) + " руб.");

    return cost;
}


std::string DeliveryProxy::getEstimatedTime() const {
    if (realDelivery_ == nullptr) {
        return "Неизвестно";
    }
    return realDelivery_->getEstimatedTime();
}

bool DeliveryProxy::isAvailable(const Order& order) const {
    if (realDelivery_ == nullptr) {
        return false;
    }

    LoggingProxy::log("DELIVERY", "Проверка доступности доставки для заказа #" + std::to_string(order.getId()) + " (Регион: " + region_ + ", Вес: " + std::to_string(order.getTotalWeight()) + " кг)");

    //  проверка региона перед делегированием
    if (region_ == "Отдалённый регион" || region_.empty()) {
        LoggingProxy::log("DELIVERY", "Отказ: доставка в регион '" + region_ + "' не поддерживается!");
        return false;
    }

    // предварительная проверка веса
    double weight = order.getTotalWeight();
    if (weight <= 0.0 || weight > 100.0) {
        LoggingProxy::log("DELIVERY", "Отказ: некорректный общий вес заказа (" + std::to_string(weight) + " кг)!");
        return false;
    }

    // делегируем проверку реальному способу доставки
    return realDelivery_->isAvailable(order);
}
