#include "Items.hpp"


void activate_item(const IUsable& item) {
    item.use();
}

int main() {
    std::cout << "=== (Q1/Q2) CRIANDO VETOR (POLIMORFISMO) ===\n";
    
    std::vector<std::unique_ptr<ItemBase>> inventory; 
    
    
    inventory.push_back(std::make_unique<Weapon>("Iron Sword", 55));
    inventory.push_back(std::make_unique<Consumable>("Health Potion", 20));
    inventory.push_back(std::make_unique<Weapon>("Magic Staff", 80));

    std::cout << "\n=== ITERANDO ITENS (DESPACHO VIRTUAL) ===\n";
    for (const auto& item : inventory) {
        item->display(); 
    }

    std::cout << "\n=== FUNCAO LIVRE (MAIOR VALOR) ===\n";
    const ItemBase* strongest = get_strongest_item(inventory);
    if (strongest) {
        std::cout << "Maior poder: " << strongest->get_name() << " com " << strongest->get_power() << "\n";
    }

    std::cout << "\n=== (Q3) INTERFACE PURA POR REFERENCIA ===\n";
    Consumable elixir("Elixir Supremo", 150);
    activate_item(elixir); 

    std::cout << "\n=== SAINDO DO ESCOPO (TESTE DE DESTRUICAO) ===\n";
    inventory.clear(); 

    return 0;
}
