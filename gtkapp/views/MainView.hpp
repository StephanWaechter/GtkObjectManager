#pragma once
#include <gtkapp/models/common.hpp>
#include <gtkapp/viewmodels/MainViewModel.hpp>
#include <gtkmm.h>
#include <string>
#include <memory>

namespace gtkapp::views
{
    class MainView : public Gtk::Grid
    {
    public:
        MainView();
        MainView(viewmodels::MainViewModel* dataContext) : MainView()
        {
            bind(dataContext);
        }
        ~MainView();
        void bind(viewmodels::MainViewModel* dataContext);

        void add_item(models::Item& item);
        void select_item(models::Item& item);
        void clear_selection();
        void remove_item(models::Item const& item);

        Gtk::Button Add;
        Gtk::Button Delete;
        Gtk::Button Clear;
        Gtk::TreeView ItemsView;
        sigc::connection row_changed;
    private:
        struct ItemColumn : public Gtk::TreeModelColumnRecord
        {
            ItemColumn()
            {
                add(name);
                add(item);
            }
            Gtk::TreeModelColumn<std::string> name;
            Gtk::TreeModelColumn<models::Item*> item;
        };

        ItemColumn ItemColumn_;
        Glib::RefPtr<Gtk::ListStore> ItemList_;
        std::map <models::Item::Id, Gtk::TreeModel::iterator> Item_to_row;
        viewmodels::MainViewModel* DataContext;
    };
} // namespace gtkapp
