#pragma once
#include <gtkapp/models/common.hpp>
#include "AddNewItem.hpp"

namespace gtkapp::views
{
    AddNewItem::AddNewItem() : DataContext{ nullptr }, Create{ "Create" }, Cancel{ "Cancel" }
    {
        std::cout << "AddNewItem" << std::endl;
        set_orientation(Gtk::Orientation::VERTICAL);
        auto frame = Gtk::make_managed<Gtk::Frame>();
        frame->set_child(Item);
        append(*frame);
        frame->set_expand(true);
        Create.set_hexpand(true);
        Cancel.set_hexpand(true);
        auto box = Gtk::make_managed<Gtk::Box>();
        box->set_orientation(Gtk::Orientation::HORIZONTAL);
        box->append(Create);
        box->append(Cancel);
        append(*box);

        Item.signal_is_valid_item_changed().connect(
            sigc::track_obj(
                [&](bool is_valid)-> void
                {
                    Create.set_sensitive(is_valid);
                }
            )
        );
    }

    AddNewItem::~AddNewItem()
    {
        std::cout << "~AddNewItem" << std::endl;
    }

    void AddNewItem::bind(viewmodels::MainViewModel* dataContext)
    {
        DataContext = dataContext;

        Create.signal_clicked().connect( 
            sigc::track_obj(
                [&]() -> void
                {
                    DataContext->add_Item(Item.create_item());
                    DataContext->RetrunMain();
                },
                *this
            )
        );

        Cancel.signal_clicked().connect(
            sigc::track_obj(
                [&]() -> void
                {
                    DataContext->RetrunMain();
                }
                , *this
            )
        );

    }
}