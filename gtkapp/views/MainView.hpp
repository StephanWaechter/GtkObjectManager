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
    struct Impl;
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

        Gtk::Button* Add;
        Gtk::Button* Delete;
        Gtk::Button* Clear;
        Gtk::Entry* New_item_entry;
        Gtk::ListBox* ListBox;

    private:
        std::vector<sigc::connection> connections;
        std::map<models::Item::Id, Gtk::ListBoxRow*> ListItems_;
        viewmodels::MainViewModel* DataContext;
    };
} // namespace gtkapp
