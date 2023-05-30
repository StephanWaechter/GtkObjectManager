#pragma once
#include <gtkapp/models/common.hpp>
#include "UpdateItem.hpp"

namespace gtkapp::controllers
{
    UpdateItem::UpdateItem(
        gtkapp::MainWindow& navigation,
        Model& model,
        models::Item& item)
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

    void UpdateItem::on_update_item(models::Item& item)
    {
        m_model.update_item(m_item_ref, item);
        m_navigation.OpenMainView();
    }
}