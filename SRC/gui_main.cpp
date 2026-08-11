#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include "items.hpp"

// Classe da Janela (Camada Fina)
class InventoryWindow : public QWidget {
    QListWidget* list_widget;
    memory_repository repo; // Usando a abstração para manter a GUI fina
    app_state state;

public:
    InventoryWindow() {
        state.version = 1;
        
        QVBoxLayout* layout = new QVBoxLayout(this);
        list_widget = new QListWidget(this);
        layout->addWidget(list_widget);

        QPushButton* btn_add = new QPushButton("Adicionar Arma Aleatória", this);
        QPushButton* btn_save = new QPushButton("Salvar Estado (Memória)", this);
        QPushButton* btn_load = new QPushButton("Carregar Estado", this);
        
        layout->addWidget(btn_add);
        layout->addWidget(btn_save);
        layout->addWidget(btn_load);

        // Disparar Ações (Sem regras de negócio aqui)
        connect(btn_add, &QPushButton::clicked, this, &InventoryWindow::add_random_item);
        connect(btn_save, &QPushButton::clicked, this, &InventoryWindow::save_state);
        connect(btn_load, &QPushButton::clicked, this, &InventoryWindow::load_state);
    }

private:
    void update_ui() {
        list_widget->clear();
        for (const auto& item : state.items) {
            QString info = QString::fromStdString(item->name() + " (Poder: " + std::to_string(item->power()) + ")");
            list_widget->addItem(info);
        }
    }

    void add_random_item() {
        int id = state.items.size() + 1;
        state.items.push_back(std::make_shared<weapon>(id, "Espada Qt", 100 + id));
        update_ui();
    }

    void save_state() {
        repo.save(state); // DIP em ação
        QMessageBox::information(this, "Sucesso", "Inventário salvo com sucesso!");
    }

    void load_state() {
        state = repo.load();
        update_ui();
        QMessageBox::information(this, "Sucesso", "Inventário carregado!");
    }
};

int main(int argc, char** argv) {
    QApplication qt(argc, argv);
    InventoryWindow window;
    window.setWindowTitle("Inventário - POO TP3");
    window.resize(300, 400);
    window.show();
    return qt.exec();
}
