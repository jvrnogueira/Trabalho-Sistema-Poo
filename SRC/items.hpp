#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <optional>
#include <variant>
#include <concepts>
#include <ranges>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <mutex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ==========================================
// Q2: Tratamento de Erros
// ==========================================
class domain_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class item_not_found : public domain_error {
public:
    explicit item_not_found(const std::string& msg) : domain_error("item nao encontrado: " + msg) {}
};

class invalid_item : public domain_error {
public:
    explicit invalid_item(const std::string& msg) : domain_error("item invalido: " + msg) {}
};

// ==========================================
// Q1(C/D): Concept C++20
// ==========================================
template <typename T>
concept usable_item = requires(const T& t) {
    { t.use() } -> std::convertible_to<void>;
};

// ==========================================
// Q1(B): CRTP
// ==========================================
template <typename Derived>
class counted_item {
    static inline int count_ = 0;
public:
    counted_item() { ++count_; }
    ~counted_item() { --count_; }
    static int alive() { return count_; }
};

// ==========================================
// DOMÍNIO BÁSICO (Adaptado para o TP3)
// ==========================================
class item_base {
protected:
    int id_;
    std::string name_;
    int power_;
public:
    item_base(int id, std::string name, int power) : id_(id), name_(std::move(name)), power_(power) {}
    virtual ~item_base() = default;
    
    int id() const { return id_; }
    std::string name() const { return name_; }
    int power() const { return power_; }
    
    virtual std::string type_name() const = 0;
    virtual void use() const = 0;
};

class weapon : public item_base, public counted_item<weapon> {
public:
    weapon(int id, std::string name, int power) : item_base(id, std::move(name), power) {}
    std::string type_name() const override { return "weapon"; }
    void use() const override { std::cout << "Atacando com " << name_ << "!\n"; }
};

class consumable : public item_base, public counted_item<consumable> {
public:
    consumable(int id, std::string name, int power) : item_base(id, std::move(name), power) {}
    std::string type_name() const override { return "consumable"; }
    void use() const override { std::cout << "Consumindo " << name_ << "!\n"; }
};

// ==========================================
// Q4: Serialização JSON
// ==========================================
void to_json(json& j, const item_base& p) {
    j = json{{"type", p.type_name()}, {"id", p.id()}, {"name", p.name()}, {"power", p.power()}};
}

// ==========================================
// Q1(A): Template Genérico
// ==========================================
template <typename T>
class registry {
    std::vector<T> items_;
public:
    void add(T item) { items_.push_back(std::move(item)); }
    const std::vector<T>& get_all() const { return items_; }
};


struct app_state {
    int version = 1;
    std::vector<std::shared_ptr<item_base>> items;
};

class repository {
public:
    virtual void save(const app_state& state) = 0;
    virtual app_state load() = 0;
    virtual ~repository() = default;
};

class memory_repository : public repository {
    app_state mem_state_;
public:
    void save(const app_state& state) override { mem_state_ = state; }
    app_state load() override { return mem_state_; }
};
