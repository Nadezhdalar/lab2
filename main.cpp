#include <iostream>
#include <vector>
#include <memory>
#include <clocale>

#include "OrderManager.h"
#include "ProductType.h"
#include "Product.h"
#include "Order.h"
#include "CourierDelivery.h"
#include "PickupDelivery.h"
#include "PostDelivery.h"
#include "DeliveryProxy.h"
#include "PercentDiscount.h"
#include "CashbackDiscount.h"
#include "FreeDeliveryDiscount.h"
#include "GiftDiscount.h"

void scenario1(OrderManager& manager) {
    std::cout << "\nСценарий 1. Создание заказа и скидка\n";

    auto electronics = ProductType::getProductType("Электроника", 1.5, 15000.0);
    auto accessories = ProductType::getProductType("Аксессуары", 0.2, 1000.0);

    auto laptop = std::make_shared<Product>(101, 1, 50000.0, electronics);
    auto mouse = std::make_shared<Product>(102, 1, 2000.0, accessories);

    auto order = manager.createOrder("Иван Иванов", { laptop });
    if (!order) return;

    order->addItem(mouse);
    std::cout << "После добавления товаров:\n" << *order;

    PercentDiscount discount10(10.0);
    *order + discount10;

    std::cout << "После скидки 10%:\n" << *order;

        auto secondOrder = manager.createOrder("Петр Петров", { mouse });
    if (secondOrder) {
        if (*order == *secondOrder) {
            std::cout << "Заказы совпадают\n";
        } else {
            std::cout << "Сравнение заказов (==): заказы имеют разные id\n";
        }
    }

}

void scenario2(OrderManager& manager) {
    std::cout << "\nСценарий 2. Доставка и DeliveryProxy\n";

    auto appliances = ProductType::getProductType("Бытовая техника", 15.0, 25000.0);
    auto washer = std::make_shared<Product>(201, 1, 25000.0, appliances);

    auto order = manager.createOrder("Анна Смирнова", { washer });
    if (!order) return;

    DeliveryProxy postProxy(std::make_shared<PostDelivery>(), "Санкт-Петербург");
    std::cout << "Проверка почты (вес 15 кг):\n";
    if (!postProxy.isAvailable(*order)) {
        std::cout << "Почта недоступна, выбираем курьера\n";
    }

    DeliveryProxy courierProxy(std::make_shared<CourierDelivery>(), "Санкт-Петербург");
    if (courierProxy.isAvailable(*order)) {
        std::cout << "Курьер доступен, срок: " << courierProxy.getEstimatedTime() << "\n";
        courierProxy << *order;
        std::cout << "Повторный расчет цены: " << courierProxy.getCost(*order) << " руб.\n";
    }

    std::cout << *order;

        DeliveryProxy badRegionProxy(std::make_shared<CourierDelivery>(), "Отдалённый регион");
    if (!badRegionProxy.isAvailable(*order)) {
        std::cout << "Проверка региона в DeliveryProxy: недоступный регион отклонен\n";
    }

}

void scenario3(OrderManager& manager) {
    std::cout << "\nСценарий 3. Статусы, Observer и оборот\n";

    std::cout << "Оборот до заказа: " << manager.getTurnover() << " руб., клиентов: " << manager.getCustomerCount() << "\n";

    auto bookType = ProductType::getProductType("Книги", 0.5, 1200.0);
    auto book = std::make_shared<Product>(301, 2, 1200.0, bookType);

    auto order = manager.createOrder("Дмитрий Козлов", { book });
    if (!order) return;

    CourierDelivery courier;
    courier << *order;

    FreeDeliveryDiscount freeDel;
    CashbackDiscount cashback(5.0);
    auto mugType = ProductType::getProductType("Сувениры", 0.3, 300.0);
    auto mug = std::make_shared<Product>(999, 1, 300.0, mugType);
    GiftDiscount gift(mug);

    *order + freeDel;
    *order + cashback;
    *order + gift;

    std::cout << *order;

    order->setStatus(OrderStatus::Paid);
    order->setStatus(OrderStatus::Shipped);
    order->setStatus(OrderStatus::Delivered);

    std::cout << "Итоговый оборот: " << manager.getTurnover() << " руб., клиентов: " << manager.getCustomerCount() << "\n";
    order->unsubscribe(&manager);
    std::cout << "Менеджер отписан от уведомлений заказа #" << order->getId() << "\n";

}

void scenario4(OrderManager& manager) {
    std::cout << "\nСценарий 4. Несколько скидок на один заказ\n";

    auto gadgetType = ProductType::getProductType("Гаджеты", 0.8, 10000.0);
    auto watch = std::make_shared<Product>(401, 1, 10000.0, gadgetType);

    auto order = manager.createOrder("Елена Соколова", { watch });
    if (!order) return;

    CourierDelivery courier;
    courier << *order;
    std::cout << "Начальная сумма с доставкой: " << order->getTotalPrice() << " руб.\n";

    FreeDeliveryDiscount freeDel;
    PercentDiscount discount10(10.0);
    CashbackDiscount cashback5(5.0);
    auto giftType = ProductType::getProductType("Подарки", 0.1, 500.0);
    auto giftCase = std::make_shared<Product>(402, 1, 500.0, giftType);
    GiftDiscount gift(giftCase);

    *order + freeDel + discount10 + cashback5 + gift;

    std::cout << "Сумма после всех акций: " << order->getTotalPrice() << " руб.\n";
    std::cout << *order;
}

void scenario5() {
    std::cout << "\nСценарий 5. Отмена заказа и лимит\n";

    OrderManager localManager(2);

    auto itemType = ProductType::getProductType("Одежда", 0.5, 3000.0);
    auto jacket = std::make_shared<Product>(501, 1, 3000.0, itemType);

    auto order1 = localManager.createOrder("Олег Морозов", { jacket });
    auto order2 = localManager.createOrder("Олег Морозов", { jacket });

    std::cout << "Клиентов: " << localManager.getCustomerCount() << ", активных заказов: " << localManager.getActiveOrdersCount() << "\n";

    auto order3 = localManager.createOrder("Мария Волкова", { jacket });

    order1->setStatus(OrderStatus::Cancelled);

    order3 = localManager.createOrder("Мария Волкова", { jacket });

    std::cout << "Клиентов: " << localManager.getCustomerCount() << ", активных заказов: " << localManager.getActiveOrdersCount() << "\n";
}

int main() {
    std::setlocale(LC_ALL, ".UTF8");

    OrderManager manager(5);
    int choice = -1;

    while (choice != 0) {
        std::cout << "\nМеню:\n"
                  << "1. Сценарий 1 (заказ и скидка)\n"
                  << "2. Сценарий 2 (доставка и прокси)\n"
                  << "3. Сценарий 3 (статусы и оборот)\n"
                  << "4. Сценарий 4 (несколько скидок)\n"
                  << "5. Сценарий 5 (отмена и лимит)\n"
                  << "0. Выход\n"
                  << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                scenario1(manager);
                break;
            case 2:
                scenario2(manager);
                break;
            case 3:
                scenario3(manager);
                break;
            case 4:
                scenario4(manager);
                break;
            case 5:
                scenario5();
                break;
            case 0:
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Неверный пункт.\n";
                break;
        }
    }

    return 0;
}
