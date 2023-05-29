#pragma once
#include <gtkapp/controllers/Controller.hpp>
#include <gtkapp/NavigationWindow.hpp>
#include <gtkmm.h>
#include <string>
#include <memory>

namespace gtkapp
{
    class MainWindow : public gtkapp::NavigationWindow
    {
    public:
        void OpenMainView();
        void OpenAddNewItem();
        void OpenUpdateItem(models::Item & item);

    private:
        controllers::Controller DataContext;
    };
} // namespace gtkapp
