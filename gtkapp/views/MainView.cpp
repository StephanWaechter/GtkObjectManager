#include "MainView.hpp"
#include <map>
#include <thread>

using namespace std::chrono_literals;

namespace gtkapp::views
{
    struct MyListRow : public Gtk::ListBoxRow
    {
        MyListRow(models::Item& _item)
            : label{ _item.get_Name() }, item{ _item }
        {
            set_child(label);
            set_halign(Gtk::Align::FILL);
            label.set_hexpand(true);

            show();
        }

        Gtk::Label label;
        models::Item& item;
    };

    void MainView::add_item(models::Item& item)
    {
        auto id = item.get_Id();
        auto row = Gtk::make_managed<MyListRow>(item);
        std::cout << "add " << item << " to view" << std::endl;

        ListItems_[id] = row;
        ListBox.append(*row);
        row->show();
    }

    void MainView::select_item(models::Item& item)
    {
        auto& row = ListItems_[item.get_Id()];
        ListBox.select_row(*row);
    }

    void MainView::clear_selection()
    {
        ListBox.unselect_all();
    }

    void MainView::remove_item(models::Item const& item)
    {
        auto id = item.get_Id();
        auto row = ListItems_[id];
        ListBox.remove(*row);
        ListItems_.erase(id);
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

        Add.set_sensitive(true);
        Add.set_vexpand(false);
        Delete.set_vexpand(false);
        Clear.set_vexpand(false);
        scroller->set_expand(true);
        ListBox.set_expand(true);
        scroller->set_child(ListBox);

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
                auto row = (MyListRow*)ListBox.get_selected_row();
            DataContext->remove_Item(row->item);
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
            ListBox.select_row(
                *ListItems_[selected_item->get_Id()]
            );
        }
        else
        {
            std::cout << "selected_item: <null>" << std::endl;
            ListBox.unselect_all();
            Delete.set_sensitive(false);
        }

        row_changed = ListBox.signal_selected_rows_changed().connect(
            sigc::track_obj(
                [&]
                {
                    auto row = (MyListRow*) ListBox.get_selected_row();
                    if(row != nullptr) DataContext->select_item(&(row->item));
                    else DataContext->select_item();
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