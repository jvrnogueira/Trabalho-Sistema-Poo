#include <iostream>
#include <string>
#include <vector>

class item_stats {
private:
    int power_;
public:
    // Construtor
    item_stats(int power) : power_(power) {
        std::cout << " item_stats(" << power_ << ") criado" << std::endl;
    }
    
    ~item_stats() {
        std::cout << " ~item_stats(" << power_ << ") destruido" << std::endl;
    }
    
    // get
    int get_power() const { return power_; }
};

class item {
private:
    int id_;
    std::string name_;
    double weight_;
    item_stats* stats_;
public:
    // Construtor
    item(int id, std::string name, double weight, int power)
        : id_(id), name_(name), weight_(weight) {
        std::cout << " item(\"" << name_ << "\") criado" << std::endl;
        stats_ = new item_stats(power);
    }

    ~item() {
        delete stats_;
        std::cout << " ~item (\"" << name_ << "\") destruido" << std::endl;
    }

    // getters
    int get_id() const { return id_; }
    std::string get_name() const { return name_; }
    double get_weight() const { return weight_; }
};

class equipment {
private:
    std::string name_;
    int durability_;

public:
    equipment(std::string name, int durability)
        : name_(name), durability_(durability) {}

    std::string get_name() const { return name_; }
    int get_durability() const { return durability_; }

    void take_damage(int damage) {
        durability_ -= damage;
        if (durability_ < 0) {
            durability_ = 0;
        }
    }
};

class consumable {
private:
    std::string name_;
    int quantity_;

public:
    consumable(std::string name, int quantity)
        : name_(name), quantity_(quantity) {}

    std::string get_name() const { return name_; }
    int get_quantity() const { return quantity_; }

    bool consume() {
        if (quantity_ > 0) {
            quantity_--;
            return true;
        }
        return false;
    }
};

class inventory {
private:
    std::string owner_name_;
    std::vector<item*> items_list_;
    double max_capacity_;
    double current_weight_;

public:
    inventory(std::string owner_name)
        : owner_name_(owner_name), max_capacity_(100.0), current_weight_(0.0) {
        std::cout << "[SYSTEM] inventory do " << owner_name_ << " criado." << std::endl;
    }

    ~inventory() {
        std::cout << "[SYSTEM] inventory destruido. Itens preservados devido a agregacao." << std::endl;
    }

    double get_max_capacity() const { return max_capacity_; }
    double get_current_weight() const { return current_weight_; }

    void add_item(item* new_item) {
        items_list_.push_back(new_item);
        current_weight_ += new_item->get_weight();
        std::cout << "[SYSTEM] Item " << new_item->get_name() << " adicionado ao inventario." << std::endl;
    }
};

int main() {
    std::cout << "=== (1) CRIANDO ITENS INDEPENDENTES ===" << std::endl;

    item* potion = new item(1, "Health Potion", 0.5, 10);
    item* sword = new item(2, "Iron Sword", 3.0, 55);

    std::cout << "\n=== (2) INICIANDO ESCOPO DO INVENTARIO (AGREGACAO) ===" << std::endl;
    {
        inventory hero_bag("Hero");
        
        hero_bag.add_item(potion);
        hero_bag.add_item(sword);
        
        std::cout << "\nSaindo do escopo do inventario (destrutor sera chamado):" << std::endl;
    } 

    std::cout << "\n=== (3) DESTRUICAO MANUAL DOS ITENS (COMPOSICAO) ===" << std::endl;
    std::cout << "Como a agregacao preservou os itens, podemos deleta-los agora:" << std::endl;

    delete potion;
    delete sword;

    std::cout << "\nFim da execucao." << std::endl;
    return 0;
}
