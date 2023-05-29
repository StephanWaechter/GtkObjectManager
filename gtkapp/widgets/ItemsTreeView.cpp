#include "ItemsTreeView.hpp"

namespace gtkapp::widgets
{
    ItemsTreeView::ItemsTreeView()
    {
        ItemList_ = Gtk::ListStore::create(Columns_);
        get_selection()->set_mode(Gtk::SelectionMode::SINGLE);
        set_model(ItemList_);
        append_column("name", Columns_.name);
    }

    models::Item * ItemsTreeView::get_selected_item()
    {
        auto row = get_selection()->get_selected();
        return (*row)[Columns_.item];
    }

    void ItemsTreeView::add_item(models::Item & item)
    {
        auto id = item.get_Id();
        std::cout << "add " << item << " to view" << std::endl;
        auto row = ItemList_->append();
        Item_to_row_[id] = row;
        (*row)[Columns_.name] = item.get_Name();
        (*row)[Columns_.item] = &item;
    }

    void ItemsTreeView::remove_item(models::Item const& item)
    {
        auto id = item.get_Id();
        auto& row = Item_to_row_[id];
        ItemList_->erase(row);
        Item_to_row_.erase(id);
    }
    
    void ItemsTreeView::update_selection(models::Item const* item)
    {
        if (item != nullptr)
        {
            select_item(*item);
        }
        else
        {
            clear_selection();
        }
    }

    Glib::SignalProxy<void(void)> ItemsTreeView::signal_selection_changed()
    {
        return get_selection()->signal_changed();
    }

    void ItemsTreeView::select_item(models::Item const& item)
    {
        auto id = item.get_Id();
        auto& row = Item_to_row_[id];
        get_selection()->select(row);
    }

    void ItemsTreeView::clear_selection()
    {
        get_selection()->unselect_all();
    }
}