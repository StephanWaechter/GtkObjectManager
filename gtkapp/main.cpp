#include "NavigationWindow.hpp"
#include <gtkapp/views/MainView.hpp>
#include <gtkapp/views/AddNewItem.hpp>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, const char* argv[])
{
    std::unique_ptr<gtkapp::NavigationWindow> mainWindow;
    std::unique_ptr<gtkapp::viewmodels::MainViewModel> mainViewModel;
    auto app = Gtk::Application::create();

    app->signal_activate().connect(
        [&]
        {
            mainWindow = std::make_unique<gtkapp::NavigationWindow>();
            mainViewModel = std::make_unique<gtkapp::viewmodels::MainViewModel>();

            mainViewModel->RetrunMain = [&]
            {
                auto view = std::make_unique<gtkapp::views::MainView>();
                auto& ref_view = *view;
                mainWindow->Open( std::move(view) );
                ref_view.bind( mainViewModel.get() );
            };

            mainViewModel->CreateNewItem = [&]
            {
                auto view = std::make_unique<gtkapp::views::AddNewItem>();
                auto& ref_view = *view;
                mainWindow->Open( std::move(view) );
                ref_view.bind( mainViewModel.get() );
            };
            mainViewModel->RetrunMain();

            mainWindow->set_size_request(320, 480);
            mainWindow->show(); // <-- this still calls signal_selected_rows_changed on views::MainView::ListBox very annoying 

            app->add_window(*mainWindow);
        }
    );

    return app->run();
}