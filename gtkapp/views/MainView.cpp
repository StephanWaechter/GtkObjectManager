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
            set_halign(Gtk::Align::START);
            label.set_size_request(150);
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
        ListBox->append(*row);
        row->show();
    }

    void MainView::select_item(models::Item& item)
    {
        auto& row = ListItems_[item.get_Id()];
        ListBox->select_row(*row);
    }

    void MainView::clear_selection()
    {
        ListBox->unselect_all();
    }

    void MainView::remove_item(models::Item const& item)
    {
        auto id = item.get_Id();
        auto row = ListItems_[id];
        ListBox->remove(*row);
        ListItems_.erase(id);
    }

    MainView::MainView() : DataContext{nullptr}
    {
        auto new_label = Gtk::make_managed<Gtk::Label>( "New Item" );
        auto list_title = Gtk::make_managed<Gtk::Label>("Items");
        auto scroller = Gtk::make_managed<Gtk::ScrolledWindow>();

        New_item_entry = Gtk::make_managed<Gtk::Entry>();
        Add = Gtk::make_managed<Gtk::Button>( "Add" );
        Delete = Gtk::make_managed<Gtk::Button>( "Delete" );
        Clear = Gtk::make_managed<Gtk::Button>("Clear");
        ListBox = Gtk::make_managed<Gtk::ListBox>();

        Add->set_sensitive(false);
        Add->set_hexpand(true);
        Delete->set_sensitive(false);
        Delete->set_expand(false);
        new_label->set_hexpand(true);
        New_item_entry->set_hexpand(true);
        scroller->set_vexpand(true);
        scroller->set_hexpand(true);
        ListBox->set_hexpand(true);
        ListBox->set_vexpand(true);
        scroller->set_child(*ListBox);

        New_item_entry->signal_changed().connect(
            [&]
            {
                bool notext = New_item_entry->get_text().size() == 0;
                Add->set_sensitive(!notext);
            }
        );

        Delete->signal_clicked().connect(
            [&]
            {
                auto row = (MyListRow*)ListBox->get_selected_row();
                DataContext->remove_Item(row->item);
            }
            );

        Add->signal_clicked().connect(
            [&]
            {
                auto item = models::Item(New_item_entry->get_text());
                DataContext->add_Item(std::move(item));
                New_item_entry->set_text("");
            }
        );

        attach(*new_label, 0, 0); attach(*New_item_entry, 1, 0, 2); attach(*Add, 3, 0);
        attach(*list_title, 0, 1, 4);
        attach(*scroller, 0, 2, 4);

        attach(*Delete, 0, 3, 2);
        attach(*Clear, 2, 3, 2);

        show();
    }
    
    MainView::~MainView()
    {
        for (auto& con : connections)
        {
            con.disconnect();
        }
    }
    
    void MainView::bind(viewmodels::MainViewModel* dataContext)
    {
        DataContext = dataContext;
        for(auto & item : DataContext->get_Items())
        {
            add_item(item);
        }

        auto user_row_selected = ListBox->signal_selected_rows_changed().connect(
            [&]
            {
                auto row = (MyListRow*) ListBox->get_selected_row();
                if(row != nullptr) DataContext->select_item(&(row->item));
                else DataContext->select_item();
            }
        );
        connections.push_back(user_row_selected);

        sigc::connection connection;
        connection = DataContext->signal_item_selected().connect(
            [&, user_row_selected](models::Item* item) mutable
            {
                user_row_selected.block(true);
                if (item != nullptr)
                {
                    select_item(*item);
                    Delete->set_sensitive(true);
                    Clear->set_sensitive(true);
                }
                else
                {
                    clear_selection();
                    Delete->set_sensitive(false);
                    Clear->set_sensitive(false);
                }
                user_row_selected.block(false);
            }
        );
        connections.push_back(connection);

        connection = Clear->signal_clicked().connect(
            [&]
            {
                DataContext->select_item();
            }
        );
        connections.push_back(connection);

        connection = DataContext->signal_item_added().connect(
            [&] (models::Item & item)
            {
                add_item(item);
            }
        );
        connections.push_back(connection);

        connection = DataContext->signal_item_removed().connect(
            [&] (models::Item const& item)
            {
                remove_item(item);
            }
        );
        connections.push_back(connection);
    }
}