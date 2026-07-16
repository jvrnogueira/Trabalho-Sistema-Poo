#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>


class IUsable {
public:
    virtual void use() const = 0;
    virtual ~IUsable() = default; 
};


class ItemBase {
protected:
    std::string name_;
public:
    ItemBase(std::string name) : name_(name) {
        std::cout << "  ItemBase(\"" << name_ << "\") criado\n";
    }
    
    
    virtual ~ItemBase() {
        std::cout << "  ~ItemBase(\"" << name_ << "\") destruido (Base)\n";
    }

    
    virtual int get_power() const = 0; 

    
    virtual void display() const { 
        std::cout << "Item: " << name_ << " | Poder: " << get_power();
    }

    std::string get_name() const { return name_; }
};


class Weapon : public ItemBase {
private:
    int damage_;
public:
    Weapon(std::string name, int damage) : ItemBase(name), damage_(damage) {}
    
    ~Weapon() override {
        std::cout << "    ~Weapon(\"" << name_ << "\") destruido (Derivada)\n";
    }

    int get_power() const override { return damage_; }

    
    void display() const override {
        ItemBase::display(); 
        std::cout << " [Tipo: Arma]\n";
    }
};

class Consumable final : public ItemBase, public IUsable { 
private:
    int heal_amount_;
public:
    Consumable(std::string name, int heal_amount) : ItemBase(name), heal_amount_(heal_amount) {}
    
    ~Consumable() override {
        std::cout << "    ~Consumable(\"" << name_ << "\") destruido (Derivada)\n";
    }

    int get_power() const override { return heal_amount_; }

    void display() const override {
        std::cout << "Consumivel: " << name_ << " | Cura: " << heal_amount_ << "\n";
    }

    
    void use() const override {
        std::cout << "-> Usando " << name_ << " para recuperar " << heal_amount_ << " de HP!\n";
    }
};


inline const ItemBase* get_strongest_item(const std::vector<std::unique_ptr<ItemBase>>& items) {
    if (items.empty()) return nullptr;
    const ItemBase* strongest = items.front().get();
    for (const auto& item : items) {
        if (item->get_power() > strongest->get_power()) {
            strongest = item.get();
        }
    }
    return strongest;
}
