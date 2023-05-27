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
            std::thread(
                [vp = mainViewModel.get()]
                {
                    for(auto & item : vp->get_Items())
                    {
                        std::this_thread::sleep_for(1s);
                        vp->select_item(&item);
                    }
                    std::this_thread::sleep_for(1s);
                    vp->select_item();
                }
            ).detach();

            mainWindow->bind(
                std::move(mainViewModel)
            );



            mainWindow->show();

            app->add_window(*mainWindow);
        }
    );

    return app->run();
}