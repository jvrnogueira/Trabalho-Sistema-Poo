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


## Programação Genérica (Q1)
* **Template Abstraído:** Foi criado um template `registry<T>` que atua como um contêiner genérico para armazenar qualquer tipo de objeto (itens, personagens, etc.), promovendo reuso.
* **CRTP vs Herança Virtual:** O CRTP foi utilizado na classe `counted_item` para injetar comportamento estático (contagem de instâncias) nas classes derivadas (como `weapon` e `consumable`). Isso evita o custo de tempo de execução (vtable) associado à herança virtual clássica.
* **Ranges Pipeline:** Antes, a filtragem de itens caros exigia um laço `for` verboso com `if` interno e um vetor temporário. Com o pipeline de ranges do C++20 (`views::filter` | `views::transform`), a operação tornou-se declarativa, lazy (avaliada sob demanda) e muito mais legível.

## Princípios SOLID (Q4)
* **SRP (Princípio da Responsabilidade Única):** A lógica de persistência (salvar/carregar) foi removida da classe `inventory` e movida para classes dedicadas de repositório.
* **OCP (Princípio Aberto/Fechado):** O sistema suporta novos tipos de itens derivando de `item_base` sem precisar alterar as funções que calculam o dano total.
* **LSP (Princípio da Substituição de Liskov):** Qualquer função que aceita a abstração `repository` funciona perfeitamente tanto com `memory_repository` quanto com `json_repository`.
* **ISP (Princípio da Segregação de Interface):** (Não se aplica fortemente nesta versão simplificada, mas evitamos criar interfaces infladas dividindo repositórios de leitura e escrita, se necessário).
* **DIP (Princípio da Inversão de Dependência):** A classe principal agora depende da abstração `repository` (injetada no construtor) e não de implementações concretas de manipulação de arquivos.
* **Agregação (`inventory` ◇ `item`):** Utilizei `std::shared_ptr` porque os itens são recursos genuinamente compartilhados (podem pertencer a um inventário, existir no ambiente ou pertencer a múltiplos gerenciadores) e sobrevivem à destruição do inventário.
