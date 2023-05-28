#include <gtkmm.h>
#include <gtkapp/models/common.hpp>

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
            Gtk::TreeModelColumn<models::Item const *> item;
        };
    public:
        ItemsTreeView();
        models::Item const* get_selected_item();
        void add_item(models::Item const& item);
        void remove_item(models::Item const& item);
        void update_selection(models::Item const* item);
        Glib::SignalProxy<void(void)> signal_selection_changed();

    private:
        void select_item(models::Item const& item);
        void clear_selection();

        ItemColumn Columns_;
        std::map <models::Item::Id, Gtk::TreeModel::iterator> Item_to_row_;
        Glib::RefPtr<Gtk::ListStore> ItemList_;
    };
}