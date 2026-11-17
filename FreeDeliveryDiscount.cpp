#include "FreeDeliveryDiscount.h"
#include "Order.h"
#include <iostream>
#include "LoggingProxy.h"

void FreeDeliveryDiscount::apply(Order& order) const {
    order.setDeliveryCost(0.0);
    LoggingProxy::log("DISCOUNT", "Применена бесплатная доставка к заказу #" + std::to_string(order.getId()));
    std::cout << "Акция: Для заказа #" << order.getId() << " применена бесплатная доставка\n";
}
