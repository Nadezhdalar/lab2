#include "PickupDelivery.h"
#include "Order.h"


double PickupDelivery::getCost(const Order& order) const {
    return 0.0;
}


std::string PickupDelivery::getEstimatedTime() const {
    return "1-3 дня";
}


bool PickupDelivery::isAvailable(const Order& order) const {
    return true;
}
