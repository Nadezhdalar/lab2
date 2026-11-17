#include "Order.h"
#include "Delivery.h"
#include "Discount.h"
#include "LoggingProxy.h"
#include <algorithm>

// конструктор заказа
Order::Order(int id, const std::string& customer, const std::vector<std::shared_ptr<Product>>& items)
    : id_(id), customer_(customer), items_(items), status_(OrderStatus::Pending), delivery_(nullptr), deliveryCost_(0.0) {
    totalPrice_ = 0.0;
    for (const auto& item : items_) {
        if (item != nullptr) {
            totalPrice_ += item->getTotalPrice();
        }
    }
}

int Order::getId() const {
    return id_;
}

std::string Order::getCustomer() const {
    return customer_;
}

OrderStatus Order::getStatus() const {
    return status_;
}

double Order::getTotalPrice() const {
    return totalPrice_;
}

double Order::getDeliveryCost() const {
    return deliveryCost_;
}

// подсчет общего веса товаров в заказе
double Order::getTotalWeight() const {
    double weight = 0.0;
    for (const auto& item : items_) {
        if (item != nullptr) {
            weight += item->getWeight();
        }
    }
    return weight;
}

std::shared_ptr<Delivery> Order::getDelivery() const {
    return delivery_;
}

const std::vector<std::shared_ptr<Product>>& Order::getItems() const {
    return items_;
}

// смена статуса и отправка уведомления наблюдателям
void Order::setStatus(OrderStatus newStatus) {
    if (status_ != newStatus) {
        OrderStatus oldStatus = status_;
        status_ = newStatus;
        OrderEvent event(id_, oldStatus, newStatus, "2026-11-16 20:28");
        LoggingProxy::log("ORDER", "заказ " + std::to_string(id_) + " статус: " + statusToString(oldStatus) + " -> " + statusToString(newStatus));
        notify(event);
    }
}

void Order::setTotalPrice(double price) {
    totalPrice_ = (price < 0.0) ? 0.0 : price;
}

// обновление стоимости доставки и пересчет итоговой суммы
void Order::setDeliveryCost(double cost) {
    totalPrice_ -= deliveryCost_;
    deliveryCost_ = (cost < 0.0) ? 0.0 : cost;
    totalPrice_ += deliveryCost_;
}

// назначение способа доставки
void Order::setDelivery(std::shared_ptr<Delivery> delivery) {
    delivery_ = delivery;
    if (delivery_ != nullptr) {
        setDeliveryCost(delivery_->getCost(*this));
    }
}

void Order::addDiscount(std::shared_ptr<Discount> discount) {
    if (discount != nullptr) {
        discounts_.push_back(discount);
        discount->apply(*this);
    }
}

void Order::applyDiscount(const Discount& discount) {
    discount.apply(*this);
}

// добавление товара в заказ
void Order::addItem(std::shared_ptr<Product> item) {
    if (item != nullptr) {
        items_.push_back(item);
        totalPrice_ += item->getTotalPrice();
    }
}

// удаление товара из заказа по id
void Order::removeItem(int productId) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        if (*it != nullptr && (*it)->getId() == productId) {
            totalPrice_ -= (*it)->getTotalPrice();
            if (totalPrice_ < 0.0) {
                totalPrice_ = 0.0;
            }
            items_.erase(it);
            break;
        }
    }
}

// подписка наблюдателя
void Order::subscribe(IObserver* observer) {
    observers_.push_back(observer);
}

// отписка наблюдателя
void Order::unsubscribe(IObserver* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

// оповещение всех наблюдателей о событии
void Order::notify(const OrderEvent& event) {
    for (IObserver* observer : observers_) {
        if (observer != nullptr) {
            observer->onOrderEvent(event);
        }
    }
}

// применение скидки через оператор +
Order& operator+(Order& order, const Discount& discount) {
    discount.apply(order);
    return order;
}

// назначение доставки через оператор <<
Order& operator<<(Delivery& delivery, Order& order) {
    std::shared_ptr<Delivery> deliveryPtr(&delivery, [](Delivery*) {});
    order.setDelivery(deliveryPtr);
    return order;
}

// вывод информации о заказе в поток
std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Заказ #" << order.getId() << "\n"
       << "Клиент: " << order.getCustomer() << "\n"
       << "Статус: " << statusToString(order.getStatus()) << "\n"
       << "Товаров: " << order.getItems().size() << ", вес: " << order.getTotalWeight() << " кг\n"
       << "Доставка: " << order.getDeliveryCost() << " руб.\n"
       << "Итого: " << order.getTotalPrice() << " руб.\n";
    return os;
}

// сравнение заказов по id
bool operator==(const Order& left, const Order& right) {
    return left.getId() == right.getId();
}
