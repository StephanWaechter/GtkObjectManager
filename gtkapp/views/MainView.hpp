#pragma once
#include <gtkapp/models/common.hpp>
#include <gtkapp/widgets/ItemsTreeView.hpp>
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

        Gtk::Button Add;
        Gtk::Button Delete;
        Gtk::Button Clear;
        widgets::ItemsTreeView ItemsView;
        
    private:
        void on_selection_changed(models::Item const* item);
        viewmodels::MainViewModel* DataContext;
    };
} // namespace gtkapp
