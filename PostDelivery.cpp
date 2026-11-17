#include "PostDelivery.h"
#include "Order.h"


double PostDelivery::getCost(const Order& order) const {
    return 200.0;
}

std::string PostDelivery::getEstimatedTime() const {
    return "5-10 дней";
}


bool PostDelivery::isAvailable(const Order& order) const {
    double weight = order.getTotalWeight();
    return weight >= 0.0 && weight <= 10.0;
}
