#include "OrderEvent.h"

// конструктор события изменения статуса заказа
OrderEvent::OrderEvent(int orderId, OrderStatus oldStatus, OrderStatus newStatus, const std::string& timestamp)
    : orderId(orderId), oldStatus(oldStatus), newStatus(newStatus), timestamp(timestamp) {}

int OrderEvent::getOrderId() const { return orderId; }
OrderStatus OrderEvent::getOldStatus() const { return oldStatus; }
OrderStatus OrderEvent::getNewStatus() const { return newStatus; }
std::string OrderEvent::getTimestamp() const { return timestamp; }
