#include "ProductType.h"

std::unordered_map<std::string, std::shared_ptr<ProductType>> ProductType::pool_;

// конструктор типа товара
ProductType::ProductType(const std::string& category, double baseWeight, double basePrice)
    : category_(category), baseWeight_(baseWeight), basePrice_(basePrice) {}

// создание или получение типа товара из пула по параметрам
std::shared_ptr<ProductType> ProductType::getProductType(const std::string& category, double baseWeight, double basePrice) {
    if (pool_.find(category) == pool_.end()) {
        pool_[category] = std::shared_ptr<ProductType>(new ProductType(category, baseWeight, basePrice));
    }
    return pool_[category];
}

// получение типа товара из пула по категории
std::shared_ptr<ProductType> ProductType::getType(const std::string& category) {
    if (pool_.find(category) != pool_.end()) {
        return pool_[category];
    }

    pool_[category] = std::shared_ptr<ProductType>(new ProductType(category, 1.0, 100.0));
    return pool_[category];
}

std::string ProductType::getCategory() const {
    return category_;
}

double ProductType::getBaseWeight() const {
    return baseWeight_;
}

double ProductType::getBasePrice() const {
    return basePrice_;
}
