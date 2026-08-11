#include <catch2/catch_test_macros.hpp>
#include "../src/items.hpp" // Ajuste o caminho se necessário

// (1) Teste de template e concept da Q1
TEST_CASE("Template Registry e Concepts") {
    registry<std::shared_ptr<item_base>> reg;
    reg.add(std::make_shared<weapon>(10, "Machado", 80));
    REQUIRE(reg.get_all().size() == 1);
    REQUIRE(reg.get_all()[0]->power() == 80);
}

// (2) Teste de tratamento de erro e optional da Q2
TEST_CASE("Tratamento de erro e Optional") {
    // REQUIRE_THROWS_AS pela exceção base
    REQUIRE_THROWS_AS([](){ throw invalid_item("Item quebrado"); }(), domain_error);
    
    std::vector<std::shared_ptr<item_base>> v;
    v.push_back(std::make_shared<consumable>(1, "Pocao", 20));
    
    // Optional
    REQUIRE(find_item(v, 1).has_value());
    REQUIRE_FALSE(find_item(v, 99).has_value());
}

// (3) e (4) Teste de Serialização Round-Trip e DIP da Q4
TEST_CASE("DIP e Serializacao Round-Trip sem tocar o disco") {
    memory_repository repo; // Implementação em memória (não afeta o disco)
    
    std::vector<std::shared_ptr<item_base>> original_items;
    original_items.push_back(std::make_shared<weapon>(1, "Espada", 50));
    app_state original_state{1, original_items};
    
    repo.save(original_state);
    auto loaded_state = repo.load();
    
    REQUIRE(loaded_state.version == original_state.version);
    REQUIRE(loaded_state.items.size() == original_state.items.size());
    REQUIRE(loaded_state.items[0]->name() == "Espada");
}