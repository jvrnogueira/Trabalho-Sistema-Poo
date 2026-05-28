# Trabalho-Sistema-Poo

Nome: João Victor Ribeiro Nogueira

Matricula: 20250019053

##Descrição
  Este projeto irá simular o funcionamento de um **"inventario"** (semelhante a uma mochila de um personagem), onde é possivel guardar,organizar e interagir com diferentes tipos de itens.

##Diagram UML
```mermaid
classDiagram
  class Item{
    #int id
    #string nome
    #double peso
    #string raridade
    +Item(int id, string nome, double peso, string raridade)
    +virtual ~Item()
}

class Equipamento{
  -int durabilidade
  -int bonusDefesa
  -int bonusAtaque
  +Equipamento(int id, string nome, double peso, string raridade, inst durabilidade, int ataque, int defesa)
}
class Inventario {
  -int capacidadeMaxima
  -double pesoMaximo
  -vector ~Item*~itens
  +Inventario(int capacidade, double pesoMax)
  ~Inventario()
}

Item <-- Equipamento: Herança
Item <-- Consumivel: Herança
Inventario "1" o--"*"Item:Agregação/Composição por ponteiros
