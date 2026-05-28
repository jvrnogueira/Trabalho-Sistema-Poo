#include <iostream>
#include <string>
#include <vector>
#include <memory>


class item_stats {
private:
    int power_;

public:
    item_stats(int power) : power_(power) {
        std::cout << "    item_stats(" << power_ << ") criado" << std::endl;
    }

    ~item_stats() {
        std::cout << "    ~item_stats(" << power_ << ") destruido" << std::endl;
    }
    
    int get_power() const { return power_; }
};


class item {
private:
    std::string name_;
    std::unique_ptr<item_stats> stats_; 

public:
    item(std::string name, int power) : name_(name) {
        std::cout << "  Item(\"" << name_ << "\") criado" << std::endl;
        stats_ = std::make_unique<item_stats>(power); 
    }

    ~item() {

        std::cout << "  ~Item(\"" << name_ << "\") destruido" << std::endl;
    }

    std::string get_name() const { return name_; }
};


class inventory {
private:
    std::string owner_name_;
    std::vector<std::shared_ptr<item>> items_list_; 

public:
    inventory(std::string owner_name) : owner_name_(owner_name) {
        std::cout << "Inventory(\"" << owner_name_ << "\") criado" << std::endl;
    }

    ~inventory() {
        std::cout << "~Inventory(\"" << owner_name_ << "\") destruido (itens estao a salvo na memoria)" << std::endl;
    }

    void add_item(std::shared_ptr<item> new_item) {
        items_list_.push_back(new_item);
        std::cout << "-> " << new_item->get_name() << " guardado no inventario." << std::endl;
    }
};


int main() {
    std::cout << "=== (1) CRIANDO ITENS INDEPENDENTES ===" << std::endl;
    std::shared_ptr<item> potion = std::make_shared<item>("Health Potion", 10);
    std::shared_ptr<item> sword = std::make_shared<item>("Iron Sword", 55);

    std::cout << "\n=== (2) INICIANDO ESCOPO DO INVENTARIO (AGREGACAO) ===" << std::endl;
    {
        inventory hero_bag("Hero");
        
        hero_bag.add_item(potion);
        hero_bag.add_item(sword);
        
        std::cout << "\nSaindo do escopo do inventario (destrutor sera chamado):" << std::endl;
    }
    
    std::cout << "\n=== (3) DESTRUICAO DOS ITENS (COMPOSICAO) ===" << std::endl;
    std::cout << "Como a agregacao preservou os itens, podemos limpa-los agora:" << std::endl;

    potion.reset();
    sword.reset();

    std::cout << "\nFim da execucao." << std::endl;
    return 0;
}