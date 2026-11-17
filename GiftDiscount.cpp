#include "GiftDiscount.h"
#include "Order.h"
#include <iostream>

GiftDiscount::GiftDiscount(std::shared_ptr<Product> giftProduct)
    : giftProduct_(giftProduct) {}

void GiftDiscount::apply(Order& order) const {
    if (giftProduct_ != nullptr) {
        // бесплатный экземпляр подарочного товара 
        auto freeGift = std::make_shared<Product>(
            giftProduct_->getId(),
            giftProduct_->getQuantity(),
            0.0,
            giftProduct_->getType()
        );
        order.addItem(freeGift);
        std::cout << "Подарок: В заказ #" << order.getId() << " добавлен бесплатный товар\n";
    }
}
