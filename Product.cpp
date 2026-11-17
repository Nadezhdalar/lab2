#include "Product.h"

// Конструктор товара
Product::Product(int id, int quantity, double currentPrice, std::shared_ptr<ProductType> type)
    : id_(id), quantity_(quantity), currentPrice_(currentPrice), type_(type) {}

int Product::getId() const {
    return id_;
}

int Product::getQuantity() const {
    return quantity_;
}

double Product::getCurrentPrice() const {
    return currentPrice_;
}

std::shared_ptr<ProductType> Product::getType() const {
    return type_;
}


double Product::getWeight() const {
    if (type_ != nullptr) {
        return type_->getBaseWeight() * quantity_;
    }
    return 0.0;
}

double Product::getTotalPrice() const {
    return currentPrice_ * quantity_;
}

// изменение количества товара
void Product::changeQuantity(int delta) {
    quantity_ += delta;
    if (quantity_ < 0) {
        quantity_ = 0;
    }
}
