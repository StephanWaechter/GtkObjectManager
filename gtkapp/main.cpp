#include "MainWindow.hpp"
#include <thread>

using namespace std::chrono_literals;

int main(int argc, const char* argv[])
{
    std::unique_ptr<gtkapp::MainWindow> mainWindow;
    auto app = Gtk::Application::create();

    app->signal_activate().connect(
        [&]
        {
            mainWindow = std::make_unique<gtkapp::MainWindow>();
            mainWindow->OpenMainView();
            mainWindow->set_size_request(320, 480);
            mainWindow->show(); // <-- this still calls signal_selected_rows_changed on views::MainView::ListBox very annoying 

            app->add_window(*mainWindow);
        }
    );

    return app->run();
}