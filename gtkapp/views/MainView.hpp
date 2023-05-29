#pragma once
#include <gtkapp/models/common.hpp>
#include <gtkapp/widgets/ItemsTreeView.hpp>
#include <gtkmm.h>
#include <string>
#include <memory>

#include <gtkapp/controllers/Controller.hpp>
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
        sigc::signal<void(const models::Item& item)> signal_delete_item;
        virtual void on_delete_item(const models::Item& item);
        sigc::signal<void(models::Item& item)> signal_update_item;
        virtual void on_update_item(models::Item& item);
        sigc::signal<void(const models::Item* item)> signal_selected_item_changed;
        virtual void on_selected_item_changed(models::Item* item);
        
        void set_selected_item(models::Item const* item);
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
