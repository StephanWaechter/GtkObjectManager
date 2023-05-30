#include "MainWindow.hpp"
#include <gtkapp/controllers/MainView.hpp>
#include <gtkapp/controllers/AddNewItem.hpp>
#include <gtkapp/controllers/UpdateItem.hpp>

void gtkapp::MainWindow::OpenMainView()
{
    auto view = std::make_unique<controllers::MainView>
    (
        *this,
        m_Model
    );
    Open(std::move(view));
}

void gtkapp::MainWindow::OpenAddNewItem()
{
    auto view = std::make_unique<controllers::AddNewItem>
    (
        *this,
        m_Model
    );
    Open(std::move(view));
}

void gtkapp::MainWindow::OpenUpdateItem(models::Item & item)
{
    auto view = std::make_unique<controllers::UpdateItem>
        (
            *this,
            m_Model,
            item
            );
    Open(std::move(view));
}