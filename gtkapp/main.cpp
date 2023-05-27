#include <gtkapp/views/MainView.hpp>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, const char* argv[])
{
    std::unique_ptr<gtkapp::views::MainView> mainWindow;
    auto app = Gtk::Application::create();

    app->signal_activate().connect(
        [&]
        {
            mainWindow = std::make_unique<gtkapp::views::MainView>();
            auto mainViewModel = std::make_unique<gtkapp::viewmodels::MainViewModel>();

            mainWindow->bind(
                std::move(mainViewModel)
            );
            mainWindow->set_size_request(320, 480);



            mainWindow->show();

            app->add_window(*mainWindow);
        }
    );

    return app->run();
}