#include "CashbackDiscount.h"
#include "Order.h"
#include <iostream>

CashbackDiscount::CashbackDiscount(double cashbackPercent)
    : cashbackPercent_(cashbackPercent) {}

void CashbackDiscount::apply(Order& order) const {
    double cashbackAmount = order.getTotalPrice() * (cashbackPercent_ / 100.0);
        std::cout << "Кешбэк Клиенту " << order.getCustomer()
              << " начислено " << cashbackAmount << " бонусных баллов ("
              << cashbackPercent_ << "% от заказа #" << order.getId() << ")\n";

}
