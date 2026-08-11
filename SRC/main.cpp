#include "items.hpp"

// Restrição por Concept (Q1-D)
template <usable_item T>
void activate_concept(const T& item) {
    item.use();
}

// Busca com Optional (Q2-B)
std::optional<std::shared_ptr<item_base>> find_item(const std::vector<std::shared_ptr<item_base>>& v, int id) {
    for (const auto& i : v) {
        if (i->id() == id) return i;
    }
    return std::nullopt;
}

int main() {
    std::cout << "=== (Q1) TEMPLATES E CRTP ===\n";
    registry<std::shared_ptr<item_base>> item_registry;
    registry<std::string> string_registry; // Instanciado com 2 tipos (Q1-A)
    
    auto sword = std::make_shared<weapon>(1, "Iron Sword", 55);
    auto potion = std::make_shared<consumable>(2, "Health Potion", 20);
    auto staff = std::make_shared<weapon>(3, "Magic Staff", 150);
    
    std::vector<std::shared_ptr<item_base>> inventory = {sword, potion, staff};
    
    std::cout << "Armas ativas (CRTP): " << weapon::alive() << "\n";
    std::cout << "Consumiveis ativos (CRTP): " << consumable::alive() << "\n";

    std::cout << "\n=== (Q1) RANGES (C++20) ===\n";
    namespace rv = std::ranges::views;
    auto strong_items = inventory 
        | rv::filter([](const auto& i) { return i->power() > 50; })
        | rv::transform([](const auto& i) { return i->name(); });
    
    std::cout << "Itens com poder > 50: ";
    for (const auto& name : strong_items) std::cout << name << " ";
    std::cout << "\n";

    std::cout << "\n=== (Q2) TRATAMENTO DE ERROS ===\n";
    try {
        throw invalid_item("Arma corrompida!");
    } catch (const domain_error& e) { // Captura pela base
        std::cerr << "Excecao capturada: " << e.what() << '\n';
    }

    auto found = find_item(inventory, 2);
    if (found.has_value()) std::cout << "Optional: Encontrou " << (*found)->name() << "\n";
    
    auto not_found = find_item(inventory, 999);
    if (!not_found.has_value()) std::cout << "Optional: Item 999 nao encontrado (nullopt).\n";

    // Variant (Q2-C)
    using result_var = std::variant<std::shared_ptr<item_base>, std::string>;
    result_var res = "Erro: Slot de inventario vazio";
    std::visit([](const auto& x) {
        using T = std::decay_t<decltype(x)>;
        if constexpr (std::is_same_v<T, std::string>) std::cout << "Variant msg: " << x << "\n";
    }, res);

    std::cout << "\n=== (Q3) STL E CONCORRENCIA ===\n";
    // Containers
    std::map<int, std::shared_ptr<item_base>> map_items;
    for(auto& i : inventory) map_items[i->id()] = i;
    std::unordered_set<std::string> tags = {"rare", "epic", "legendary"};

    // Algoritmos e Lambda com captura
    int threshold = 30;
    auto count = std::count_if(inventory.begin(), inventory.end(), 
        [threshold](const auto& i) { return i->power() > threshold; });
    std::cout << "Algoritmo (count_if): " << count << " itens acima de " << threshold << " de poder.\n";

    // Concorrência e Mutex
    std::mutex mtx;
    int total_power = 0;
    std::vector<std::future<int>> futures;
    
    for (const auto& item : inventory) {
        futures.push_back(std::async(std::launch::async, [&item]() {
            // Simulando um processamento demorado
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            return item->power();
        }));
    }
    
    for (auto& f : futures) {
        int partial = f.get();
        std::lock_guard<std::mutex> lock(mtx);
        total_power += partial;
    }
    std::cout << "Poder total calculado em paralelo: " << total_power << "\n";

    std::cout << "\n=== (Q4) DIP E SERIALIZACAO ===\n";
    memory_repository test_repo; // Usando implementacao de teste
    app_state state{1, inventory};
    test_repo.save(state);
    
    auto loaded_state = test_repo.load();
    json j;
    j["version"] = loaded_state.version;
    j["items"] = json::array();
    for (const auto& item : loaded_state.items) {
        json item_j;
        to_json(item_j, *item);
        j["items"].push_back(item_j);
    }
    std::cout << "Estado serializado:\n" << j.dump(2) << "\n";

    return 0;
}
