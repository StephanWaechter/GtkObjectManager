#include "MainView.hpp"
#include <map>
#include <thread>

using namespace std::chrono_literals;

namespace gtkapp::views
{
    void MainView::add_item(models::Item& item)
    {
        auto id = item.get_Id();
        std::cout << "add " << item << " to view" << std::endl;
        auto row = ItemList_->append();
        Item_to_row[id] = row;
        (*row)[ItemColumn_.name] = item.get_Name();
        (*row)[ItemColumn_.item] = &item;

    }

    void MainView::select_item(models::Item& item)
    {
        auto id = item.get_Id();
        auto& row = Item_to_row[id];
        ItemsView.get_selection()->select(row);
    }

    void MainView::clear_selection()
    {
        ItemsView.get_selection()->unselect_all();
    }

    void MainView::remove_item(models::Item const& item)
    {
        auto id = item.get_Id();
        auto& row = Item_to_row[id];
        ItemList_->erase(row);
        Item_to_row.erase(id);
    }

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

        ItemList_ = Gtk::ListStore::create(ItemColumn_);
        ItemsView.set_model(ItemList_);
        ItemsView.append_column("name", ItemColumn_.name);

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

    void MainView::bind(viewmodels::MainViewModel* dataContext)
    {
        DataContext = dataContext;
        Delete.signal_clicked().connect(
            [&]
            {
                auto row = ItemsView.get_selection()->get_selected();
                auto item = (*row)[ItemColumn_.item];
                if (item == nullptr) return;
                DataContext->remove_Item(*item);
            }
        );

        Add.signal_clicked().connect(
            [&]
            {
                DataContext->CreateNewItem();
            }
        );

        for(auto & item : DataContext->get_Items())
        {
            add_item(item);
        }

        auto selected_item = DataContext->get_selected_item();
        
        if (selected_item != nullptr)
        {
            std::cout << "selected_item: " << *selected_item << std::endl;
            Delete.set_sensitive(true);
            select_item(*selected_item);
        }
        else
        {
            std::cout << "selected_item: <null>" << std::endl;
            Delete.set_sensitive(false);
            clear_selection();
        }

        row_changed = ItemsView.get_selection()->signal_changed().connect(
            sigc::track_obj(
                [&]
                {
                    auto row = ItemsView.get_selection()->get_selected();
                    auto item = (*row)[ItemColumn_.item];
                    if (item == nullptr) return;
                    DataContext->select_item(item);
                },
                *this
            )
        );

        DataContext->signal_item_selected().connect(
            sigc::track_obj(
                [&](models::Item* item) mutable
                {
                    row_changed.block(true);
                    if (item != nullptr)
                    {
                        select_item(*item);
                        Delete.set_sensitive(true);
                        Clear.set_sensitive(true);
                    }
                    else
                    {
                        clear_selection();
                        Delete.set_sensitive(false);
                        Clear.set_sensitive(false);
                    }
                    row_changed.block(false);
                },
                *this
            )
        );

        Clear.signal_clicked().connect(
            sigc::track_obj(
                [&]
                {
                    DataContext->select_item();
                },
                *this
            )
        );

        DataContext->signal_item_added().connect(
            sigc::track_obj(
                [&](models::Item& item)
                {
                    add_item(item);
                },
                *this
            )
        );

        DataContext->signal_item_removed().connect(
            sigc::track_obj(
                [&] (models::Item const& item)
                {
                    remove_item(item);
                }
                ,
                *this
            )
        );
    }
}