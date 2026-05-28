#include <iostream>
#include <string>

class item{
private:
  int id_;
  std::string name_;
  double weight_;

public:
// Construtor
item(int id, std::string name, double weight)
  :id_(id), name_(name), weight_(weight) {}

// gettera
int get_id() const{return id_;}
std::string get_name() const {return name_;}
double get_weight() const {return weight_:}
}
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
    double max_capacity_;
    double current_weight_;

public:
    
    inventory(double max_capacity)
        : max_capacity_(max_capacity), current_weight_(0.0) {}

    
    ~inventory() {
        std::cout << "\n[SYSTEM] inventory destroyed. Resources freed." << std::endl;
    }

    double get_max_capacity() const { return max_capacity_; }
    double get_current_weight() const { return current_weight_; }

    bool add_weight(double weight) {
        if (current_weight_ + weight <= max_capacity_) {
            current_weight_ += weight;
            return true; 
        }
        return false;
    }
};
