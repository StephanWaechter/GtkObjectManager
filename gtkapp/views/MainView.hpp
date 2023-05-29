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
        sigc::signal<void(const models::Item& item)> signal_request_delete_item;
        sigc::signal<void(const models::Item& item)> signal_request_update_item;
        sigc::signal<void(const models::Item* item)> signal_selected_item_changed;
        
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

    void bind(MainWindow& mainWindow, controllers::Controller& controller, MainView& view);
} // namespace gtkapp
