#pragma once
#include <gtkapp/types/common.hpp>
#include "AddNewItem.hpp"

namespace gtkapp::controllers
{
    AddNewItem::AddNewItem(
        gtkapp::MainWindow& navigation,
        Model& model) 
        : 
        views::AddNewItem(),
        m_navigation{ navigation },
        m_model{ model }
    {
    }

    void AddNewItem::on_cancel()
    {
        m_navigation.OpenMainView();
    }

    void AddNewItem::on_create_new_item(types::Item item)
    {
        m_model.add_Item(std::move(item));
        m_navigation.OpenMainView();
    }
}