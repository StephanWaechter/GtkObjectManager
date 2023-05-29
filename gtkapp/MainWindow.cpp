#include "MainWindow.hpp"
#include <gtkapp/views/MainView.hpp>
#include <gtkapp/views/AddNewItem.hpp>
#include <gtkapp/views/UpdateItem.hpp>

void gtkapp::MainWindow::OpenMainView()
{
    auto view = std::make_unique<gtkapp::views::MainView>();
    bind(*this, DataContext, *view);
    Open(std::move(view));
}

void gtkapp::MainWindow::OpenAddNewItem()
{
    auto view = std::make_unique<gtkapp::views::AddNewItem>();
    bind(*this, DataContext, *view);
    Open(std::move(view));
}

void gtkapp::MainWindow::OpenUpdateItem(models::Item & item)
{
    auto view = std::make_unique<gtkapp::views::UpdateItem>(item);
    bind(*this, DataContext, *view);
    Open(std::move(view));
}