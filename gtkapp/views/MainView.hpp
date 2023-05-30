#pragma once
#include <gtkapp/types/common.hpp>
#include <gtkapp/widgets/ItemsTreeView.hpp>
#include <gtkmm.h>
#include <string>
#include <memory>

#include <gtkapp/MainWindow.hpp>

namespace gtkapp::views
{
    class MainView : public Gtk::Grid
    {
    public:
        MainView();
        ~MainView();

        widgets::ItemsTreeView ItemsView;
        
        sigc::signal<void(void)> signal_request_new_item;
        virtual void on_request_new_item();
        sigc::signal<void(const types::Item& item)> signal_delete_item;
        virtual void on_delete_item(const types::Item& item);
        sigc::signal<void(types::Item& item)> signal_update_item;
        virtual void on_update_item(types::Item& item);
        sigc::signal<void(const types::Item* item)> signal_selected_item_changed;
        virtual void on_selected_item_changed(types::Item* item);
        
        void set_selected_item(types::Item const* item);
    private:
        Gtk::Button Add;      
        Gtk::Button Update;
        Gtk::Button Delete;

        void on_add_clicked();
        void on_update_clicked();
        void on_delete_clicked();
        void on_items_view_selected_item_changed();
    };
} // namespace gtkapp
