#include <gtkmm.h>
#include <gtkapp/types/common.hpp>

namespace gtkapp::widgets
{
    class ItemsTreeView :public Gtk::TreeView
    {
        struct ItemColumn : public Gtk::TreeModelColumnRecord
        {
            ItemColumn()
            {
                add(name);
                add(item);
            }
            Gtk::TreeModelColumn<std::string> name;
            Gtk::TreeModelColumn<types::Item *> item;
        };
    public:
        ItemsTreeView();
        types::Item * get_selected_item();
        void add_item(types::Item & item);
        void remove_item(types::Item const& item);
        void update_selection(types::Item const* item);
        Glib::SignalProxy<void(void)> signal_selection_changed();

    private:
        void select_item(types::Item const& item);
        void clear_selection();

        ItemColumn Columns_;
        std::map <types::Item::Id, Gtk::TreeModel::iterator> Item_to_row_;
        Glib::RefPtr<Gtk::ListStore> ItemList_;
    };
}