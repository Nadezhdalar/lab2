#include "CourierDelivery.h"
#include "Order.h"

double CourierDelivery::getCost(const Order& order) const {
    return 500.0; 
}

std::string CourierDelivery::getEstimatedTime() const {
    return "1-2 days";
}

bool CourierDelivery::isAvailable(const Order& order) const {
    double weight = order.getTotalWeight();
    return weight >= 0.0 && weight <= 20.0;
}
