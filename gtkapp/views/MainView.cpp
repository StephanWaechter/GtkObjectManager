#include "MainView.hpp"
#include <map>
#include <thread>

using namespace std::chrono_literals;

namespace gtkapp::views
{


    MainView::MainView() :
        Add{"Add"},
        Update{"Update"},
        Delete{"Delete"}
    {
        std::cout << "MainView" << std::endl;
        auto list_title = Gtk::make_managed<Gtk::Label>("Items");
        auto scroller = Gtk::make_managed<Gtk::ScrolledWindow>();

        Add.set_sensitive(true);
        Add.set_vexpand(false);
        Delete.set_vexpand(false);
        Update.set_vexpand(false);
        scroller->set_expand(true);
        ItemsView.set_expand(true);
        scroller->set_child(ItemsView);

        attach(*list_title, 0, 0, 3);
        attach(*scroller  , 0, 1, 3);
        attach(Add        , 0, 2);
        attach(Update     , 1, 2);
        attach(Delete     , 2, 2);

        Add.signal_clicked().connect(
            sigc::mem_fun(*this, &MainView::on_add_clicked)
        );

        Delete.signal_clicked().connect(
            sigc::mem_fun(*this, &MainView::on_delete_clicked)
        );

        Update.signal_clicked().connect(
            sigc::mem_fun(*this, &MainView::on_update_clicked)
        );

        ItemsView.signal_selection_changed().connect(
            sigc::mem_fun(*this, &MainView::on_items_view_selected_item_changed)
        );

        show();
    }
    
    MainView::~MainView()
    {
        std::cout << "~MainView" << std::endl;
    }

    void MainView::set_selected_item(models::Item const* item)
    {
        ItemsView.update_selection(item);
        Delete.set_sensitive(item != nullptr);
        Update.set_sensitive(item != nullptr);
    }

    void MainView::on_add_clicked()
    {
        signal_request_new_item.emit();
    }

    void MainView::on_delete_clicked()
    {
        auto item = ItemsView.get_selected_item();
        if (item == nullptr) return;
        signal_request_delete_item.emit(*item);
    }

    void MainView::on_update_clicked()
    {
        auto item = ItemsView.get_selected_item();
        if (item == nullptr) return;
        signal_request_update_item.emit(*item);
    }

    void MainView::on_items_view_selected_item_changed()
    {
        auto item = ItemsView.get_selected_item();
        signal_selected_item_changed.emit(item);
    }

    void bind(MainWindow& mainWindow, controllers::Controller& controller, MainView& view)
    {
        for(auto & item : controller.get_Items())
        {
            view.ItemsView.add_item(item);
        }

        view.set_selected_item(
            controller.get_selected_item()
        );

        view.signal_request_new_item.connect(
            [&] { mainWindow.OpenAddNewItem(); }
        );

        view.signal_request_update_item.connect(
            [&] (auto& item) { mainWindow.OpenUpdateItem(item); }
        );

        view.signal_request_delete_item.connect(
            [&] (auto& item) { controller.remove_Item(item); }
        );

        view.signal_selected_item_changed.connect(
            [&] (auto* item) { controller.select_item(item); }
        );

        controller.signal_item_selected().connect(
            sigc::mem_fun(view, &MainView::set_selected_item)
        );

        controller.signal_item_added().connect(
            sigc::mem_fun(view.ItemsView, &widgets::ItemsTreeView::add_item)
        );

        controller.signal_item_removed().connect(
            sigc::mem_fun(view.ItemsView, &widgets::ItemsTreeView::remove_item)
        );
    }
}