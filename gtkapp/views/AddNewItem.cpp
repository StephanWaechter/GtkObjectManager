#pragma once
#include <gtkapp/models/common.hpp>
#include "AddNewItem.hpp"

namespace gtkapp::views
{
    AddNewItem::AddNewItem() : Create{ "Create" }, Cancel{ "Cancel" }
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
                },
                *this
            )
        );

        Create.signal_clicked().connect(
            sigc::mem_fun(*this, &AddNewItem::on_create_clicked)
        );

        Cancel.signal_clicked().connect(
            sigc::mem_fun(*this, &AddNewItem::on_cancel_clicked)
        );

        show();
    }

    AddNewItem::~AddNewItem()
    {
        std::cout << "~AddNewItem" << std::endl;
    }

    void AddNewItem::on_create_clicked()
    {
        on_create_new_item(
            Item.create_item()
        );
    }

    void AddNewItem::on_cancel_clicked()
    {
        on_cancel();
    }

    void AddNewItem::on_cancel()
    {
        signal_cancel.emit();
    }

    void AddNewItem::on_create_new_item(models::Item item)
    {
        signal_create_new_item.emit(
            item
        );
    }
}