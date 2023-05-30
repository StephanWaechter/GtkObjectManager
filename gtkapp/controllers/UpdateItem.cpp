#pragma once
#include <gtkapp/types/common.hpp>
#include "UpdateItem.hpp"

namespace gtkapp::controllers
{
    UpdateItem::UpdateItem(
        gtkapp::MainWindow& navigation,
        Model& model,
        types::Item& item)
        :
        views::UpdateItem(),
        m_item_ref{ item },
        m_navigation{ navigation },
        m_model{ model}
    {
        Item.set_item_values(m_item_ref);
    }

    void UpdateItem::on_cancel()
    {
        m_navigation.OpenMainView();
    }

    void UpdateItem::on_update_item(types::Item& item)
    {
        m_model.update_item(m_item_ref, item);
        m_navigation.OpenMainView();
    }
}