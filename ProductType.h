#pragma once
#include <string>
#include <unordered_map>
#include <memory>

class ProductType {
private:
    std::string category_;
    double baseWeight_;
    double basePrice_;

    static std::unordered_map<std::string, std::shared_ptr<ProductType>> pool_;

    ProductType(const std::string& category, double baseWeight, double basePrice);

public:
    // создание или получение типа с полными параметрами
    static std::shared_ptr<ProductType> getProductType(const std::string& category, double baseWeight, double basePrice);

    // получение общего объекта из пула только по категории
    static std::shared_ptr<ProductType> getType(const std::string& category);

    std::string getCategory() const;
    double getBaseWeight() const;
    double getBasePrice() const;
};
