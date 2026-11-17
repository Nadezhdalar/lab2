#include "PercentDiscount.h"
#include "Order.h"
#include "LoggingProxy.h"

// конструктор процентной скидки
PercentDiscount::PercentDiscount(double percent)
    : percent_(percent) {}

// применение скидки к заказу
void PercentDiscount::apply(Order& order) const {
    double currentPrice = order.getTotalPrice();
    double discountAmount = currentPrice * (percent_ / 100.0);
    order.setTotalPrice(currentPrice - discountAmount);
    LoggingProxy::log("DISCOUNT", "скидка " + std::to_string(static_cast<int>(percent_)) + "% на заказ #" + std::to_string(order.getId()));
}
