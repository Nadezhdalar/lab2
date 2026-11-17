#pragma once
#include "Delivery.h"
#include <memory>
#include <string>


class DeliveryProxy : public Delivery {
private:
    std::shared_ptr<Delivery> realDelivery_;
    std::string region_;
    

public:
    DeliveryProxy(std::shared_ptr<Delivery> realDelivery, const std::string& region = "Москва");
    double getCost(const Order& order) const override;
    std::string getEstimatedTime() const override;
    bool isAvailable(const Order& order) const override;
};
