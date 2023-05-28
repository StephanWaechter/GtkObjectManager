#include "MainView.hpp"
#include <map>
#include <thread>

using namespace std::chrono_literals;

namespace gtkapp::views
{


    MainView::MainView()
        : 
        DataContext{nullptr},
        Add{"Add"},
        Delete{"Delete"},
        Clear{"Clear"}
    {
        std::cout << "MainView" << std::endl;
        auto list_title = Gtk::make_managed<Gtk::Label>("Items");
        auto scroller = Gtk::make_managed<Gtk::ScrolledWindow>();

        Add.set_sensitive(true);
        Add.set_vexpand(false);
        Delete.set_vexpand(false);
        Clear.set_vexpand(false);
        scroller->set_expand(true);
        ItemsView.set_expand(true);
        scroller->set_child(ItemsView);

        attach(*list_title, 0, 0, 3);
        attach(*scroller  , 0, 1, 3);
        attach(Add        , 0, 2);
        attach(Delete     , 1, 2);
        attach(Clear      , 2, 2);      

        show();
    }
    
    MainView::~MainView()
    {
        std::cout << "~MainView" << std::endl;
    }

    void MainView::on_selection_changed(models::Item const* item)
    {
        ItemsView.update_selection(item);
        Delete.set_sensitive(item != nullptr);
        Clear.set_sensitive(item != nullptr);
    }


    void MainView::bind(viewmodels::MainViewModel* dataContext)
    {
        DataContext = dataContext;
        for(auto & item : DataContext->get_Items())
        {
            ItemsView.add_item(item);
        }
        on_selection_changed(DataContext->get_selected_item());

        ItemsView.signal_selection_changed().connect(
            sigc::track_obj(
                [&]
                {
                    auto item = ItemsView.get_selected_item();
                    if (item == nullptr) return;
                    DataContext->select_item(item);
                },
                *this
            )
        );

        Delete.signal_clicked().connect(
            [&]
            {
                auto item = ItemsView.get_selected_item();
                if (item == nullptr) return;
                DataContext->remove_Item(*item);
            }
        );

        Add.signal_clicked().connect(
            [&] { DataContext->on_create_new_item(); }
         );

        Clear.signal_clicked().connect(
            [&] { DataContext->select_item(nullptr); }
        );

        DataContext->signal_item_selected().connect(
            sigc::mem_fun(*this, &MainView::on_selection_changed)
        );

        DataContext->signal_item_added().connect(
            sigc::mem_fun(ItemsView, &widgets::ItemsTreeView::add_item)
        );

        DataContext->signal_item_removed().connect(
            sigc::mem_fun(ItemsView, &widgets::ItemsTreeView::remove_item)
        );
    }
}