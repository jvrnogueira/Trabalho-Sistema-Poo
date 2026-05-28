# Trabalho-Sistema-Poo

Nome: João Victor Ribeiro Nogueira

Matricula: 20250019053

## Descrição
  Este projeto irá simular o funcionamento de um **"inventario"** (semelhante a uma mochila de um personagem), onde é possivel guardar,organizar e interagir com diferentes tipos de itens.

## Diagrama UML
## Relações de Classes: Composição e Agregação

O sistema implementa relações estruturais rigorosas para garantir o gerenciamento correto da memória e refletir a lógica do domínio. Abaixo está a representação UML dessas relações:

```mermaid
classDiagram
    class item_stats {
        - int power_
        + item_stats(int power)
        + ~item_stats()
    }

    class item {
        - string name_
        - item_stats* stats_
        + item(string name, int power)
        + ~item()
        + get_name() string
    }

    class inventory {
        - string owner_name_
        - vector~item*~ items_list_
        + inventory(string owner_name)
        + ~inventory()
        + add_item(item* new_item) void
    }

    item *-- item_stats : (◆) Composição
    inventory o-- item : (◇) Agregação

## Smart Pointers

A gerência de memória do projeto foi modernizada substituindo *raw pointers* (`*`) por *smart pointers* (`<memory>`), visando segurança e eliminando a necessidade de desalocação manual (`delete`).

* **Composição (`item` ◆ `item_stats`):** Utilizei `std::unique_ptr` porque a classe `item` tem posse exclusiva sobre seus atributos de status, garantindo que o ciclo de vida do dependente acabe exatamente junto com o dono.
* **Agregação (`inventory` ◇ `item`):** Utilizei `std::shared_ptr` porque os itens são recursos genuinamente compartilhados (podem pertencer a um inventário, existir no ambiente ou pertencer a múltiplos gerenciadores) e sobrevivem à destruição do inventário.
