#include "MainView.hpp"
#include <map>
#include <thread>

using namespace std::chrono_literals;

namespace gtkapp::views
{
    struct MainView::Impl : public Gtk::Grid
    {
        struct MyListRow : public Gtk::ListBoxRow
        {
            MyListRow(Item & _item)
            : label{_item.get_Name()}, item{_item}
            {
                set_child(label);
                set_halign(Gtk::Align::START);
                label.set_size_request(150); 
                show();
            }

            Gtk::Label label;
            Item & item;
        };

        Gtk::Label Label{"New Item"};
        Gtk::Label Title{"Items"};
        Gtk::Entry Entry;
        Gtk::Button Add{"Add"};
        Gtk::Button Delete{"Delete"};
        Gtk::Button Clear{"Clear"};
        Gtk::ScrolledWindow Scroller;
        Gtk::ListBox ListBox;
        std::map<Item::Id , std::shared_ptr<MyListRow>> ListItems;
        Impl()
        {
            Add.set_sensitive(false);
            Add.set_hexpand(true);
            Delete.set_sensitive(false);
            Delete.set_expand(false);
            Label.set_hexpand(true);
            Entry.set_hexpand(true);
            Scroller.set_vexpand(true);
            Scroller.set_hexpand(true);
            
            attach(Label, 0, 0); attach(Entry , 1, 0, 2); attach(Add, 3, 0);
            
            Scroller.set_child(ListBox);
            attach(Title, 0, 1, 4);
            attach(Scroller, 0, 2, 4);
            
            attach(Delete, 0, 3, 2);
            attach(Clear , 2, 3, 2);


            show();
        }

        void add_item(Item & item)
        {
            auto id = item.get_Id();
            auto row = std::make_shared<MyListRow>(item);
            std::cout << "add " << item << " to view" << std::endl;

            ListItems[id] = row;
            ListBox.append(*row);
            row->show();
        }

        void select_item(Item & item)
        {
            auto& row = ListItems[item.get_Id()];
            ListBox.select_row(*row);
        }

        void clear_selection()
        {
            ListBox.unselect_all();
        }

        void remove_item(Item const& item)
        {
            auto& row = ListItems[item.get_Id()];
            ListBox.remove(*row);
            row->show();
        }

    };

    MainView::MainView() : pimpl{std::make_unique<MainView::Impl>()}
    {
        set_child(*pimpl);
    }
    
    MainView::~MainView()
    {
    }
    
    void MainView::bind(std::unique_ptr<viewmodels::MainViewModel> dataContext)
    {
        DataContext.reset(dataContext.release());
        for(auto & item : DataContext->get_Items())
        {
            pimpl->add_item(item);
        }

        auto user_row_selected = pimpl->ListBox.signal_selected_rows_changed().connect(
            [&]
            {
                auto row = (Impl::MyListRow*) pimpl->ListBox.get_selected_row();
                if(row != nullptr) DataContext->select_item(&(row->item));
                else DataContext->select_item();
            }
        );

        DataContext->signal_item_selected.connect(
            [&, user_row_selected] (Item * item) mutable
            {
                user_row_selected.block(true);
                if(item != nullptr)
                {
                    pimpl->select_item(*item);
                    pimpl->Delete.set_sensitive(true);
                    pimpl->Clear.set_sensitive(true);
                }
                else
                {
                    pimpl->clear_selection();
                    pimpl->Delete.set_sensitive(false);
                    pimpl->Clear.set_sensitive(false);
                }
                user_row_selected.block(false);
            }
        );

        pimpl->Delete.signal_clicked().connect(
            [&]
            {
                auto row = (Impl::MyListRow*) pimpl->ListBox.get_selected_row();
                DataContext->remove_Item(row->item);
            }
        );

        pimpl->Add.signal_clicked().connect(
            [&] 
            {
                auto item = Item(pimpl->Entry.get_text());
                DataContext->add_Item(std::move(item));
                pimpl->Entry.set_text("");
            }
        );

        pimpl->Clear.signal_clicked().connect(
            [&]
            {
                DataContext->select_item();
            }
        );

        pimpl->Entry.signal_changed().connect(
            [&] 
            {
                bool notext = pimpl->Entry.get_text().size() == 0;
                pimpl->Add.set_sensitive(!notext);
            }
        );

        DataContext->signal_item_added.connect(
            [&] (Item & item)
            {
                pimpl->add_item(item);
            }
        );

        DataContext->signal_item_removed.connect(
            [&] (Item const& item)
            {
                pimpl->remove_item(item);
            }
        );
    }
}