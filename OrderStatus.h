#pragma once
#include <string>

enum class OrderStatus {
    Pending,
    Paid,
    Shipped,
    Delivered,
    Cancelled
};

inline std::string statusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending:   return "Pending";
        case OrderStatus::Paid:      return "Paid";
        case OrderStatus::Shipped:   return "Shipped";
        case OrderStatus::Delivered: return "Delivered";
        case OrderStatus::Cancelled: return "Cancelled";
        default:                     return "Unknown";
    }
}
