#include "MainView.hpp"
#include <map>
#include <thread>

namespace gtkapp::controllers
{
    MainView::MainView(
        gtkapp::MainWindow& navigation,
        Controller& controller)
        :
        views::MainView(),
        m_navigation{ navigation },
        m_controller{ controller }
    {
        for (auto& item : controller.get_Items())
        {
            ItemsView.add_item(item);
        }

        set_selected_item(
            controller.get_selected_item()
        );

        m_controller.signal_item_selected().connect(
            sigc::mem_fun(*this, &MainView::set_selected_item)
        );

        m_controller.signal_item_added().connect(
            sigc::mem_fun(this->ItemsView, &widgets::ItemsTreeView::add_item)
        );

        m_controller.signal_item_removed().connect(
            sigc::mem_fun(this->ItemsView, &widgets::ItemsTreeView::remove_item)
        );
    }
    
    void MainView::on_request_new_item()
    {
        m_navigation.OpenAddNewItem();
    }

    void MainView::on_delete_item(const models::Item& item)
    {
        m_controller.remove_Item(item);
    }

    void MainView::on_update_item(models::Item& item)
    {
        m_navigation.OpenUpdateItem(item);
    }

    void  MainView::on_selected_item_changed(models::Item* item)
    {
        m_controller.select_item(item);
    }
}