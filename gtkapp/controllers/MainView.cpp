#include "MainView.hpp"
#include <map>
#include <thread>

namespace gtkapp::controllers
{
    MainView::MainView(
        gtkapp::MainWindow& navigation,
        Model& model)
        :
        views::MainView(),
        m_navigation{ navigation },
        m_model{ model }
    {
        for (auto& item : m_model.get_Items())
        {
            ItemsView.add_item(item);
        }

        set_selected_item(
            m_model.get_selected_item()
        );

        m_model.signal_item_selected().connect(
            sigc::mem_fun(*this, &MainView::set_selected_item)
        );

        m_model.signal_item_added().connect(
            sigc::mem_fun(this->ItemsView, &widgets::ItemsTreeView::add_item)
        );

        m_model.signal_item_removed().connect(
            sigc::mem_fun(this->ItemsView, &widgets::ItemsTreeView::remove_item)
        );
    }
    
    void MainView::on_request_new_item()
    {
        m_navigation.OpenAddNewItem();
    }

    void MainView::on_delete_item(const types::Item& item)
    {
        m_model.remove_Item(item);
    }

    void MainView::on_update_item(types::Item& item)
    {
        m_navigation.OpenUpdateItem(item);
    }

    void  MainView::on_selected_item_changed(types::Item* item)
    {
        m_model.select_item(item);
    }
}