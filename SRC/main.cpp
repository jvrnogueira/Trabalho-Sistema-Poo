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

//Getters
int get_id() const{return id_;}
std::string get_name() const {return name_;}
double get_weight() const {return weight_:}
}
