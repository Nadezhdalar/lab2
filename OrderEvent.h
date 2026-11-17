#pragma once
#include <string>
#include "OrderStatus.h"

class OrderEvent {
private:
    int orderId;
    OrderStatus oldStatus;
    OrderStatus newStatus;
    std::string timestamp;

public:
    OrderEvent(int orderId, OrderStatus oldStatus, OrderStatus newStatus, const std::string& timestamp);

    int getOrderId() const;
    OrderStatus getOldStatus() const;
    OrderStatus getNewStatus() const;
    std::string getTimestamp() const;
};
