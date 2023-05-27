#pragma once
#include <gtkapp/models/common.hpp>
#include <gtkapp/viewmodels/MainViewModel.hpp>
#include <gtkmm.h>
#include <string>
#include <memory>

namespace gtkapp::views
{
    class MainView : public Gtk::Window
    {
    struct Impl;
    public:
        MainView();
        ~MainView();
        void bind(std::unique_ptr<viewmodels::MainViewModel> dataContext);

    private:
        std::unique_ptr<viewmodels::MainViewModel> DataContext;
        std::unique_ptr<Impl> pimpl;
    };
} // namespace gtkapp
