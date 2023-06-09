#pragma once
#include <gtkapp/types/common.hpp>
#include "UpdateItem.hpp"

namespace gtkapp::views
{
    UpdateItem::UpdateItem() : Update { "Update" }, Cancel{ "Cancel" }
    {
        std::cout << "UpdateItem" << std::endl;
        set_orientation(Gtk::Orientation::VERTICAL);
        auto frame = Gtk::make_managed<Gtk::Frame>();
        frame->set_child(Item);
        append(*frame);
        frame->set_expand(true);
        Update.set_hexpand(true);
        Cancel.set_hexpand(true);
        auto box = Gtk::make_managed<Gtk::Box>();
        box->set_orientation(Gtk::Orientation::HORIZONTAL);
        box->append(Update);
        box->append(Cancel);
        append(*box);

        Item.signal_is_valid_item_changed().connect(
            sigc::track_obj(
                [&](bool is_valid)-> void
                {
                    Update.set_sensitive(is_valid);
                },
                *this
            )
        );

        Update.signal_clicked().connect(
            sigc::mem_fun(*this, &UpdateItem::on_update_clicked)
        );

        Cancel.signal_clicked().connect(
            sigc::mem_fun(*this, &UpdateItem::on_cancel_clicked)
        );

        show();
    }

    UpdateItem::~UpdateItem()
    {
        std::cout << "~UpdateItem" << std::endl;
    }

    void UpdateItem::on_update_clicked()
    {
        on_update_item(
            Item.create_item()
        );
    }

    void UpdateItem::on_update_item(types::Item& item)
    {
        signal_update_item.emit(item);
    }

    void UpdateItem::on_cancel_clicked()
    {
        on_cancel();
    }
    

    void UpdateItem::on_cancel()
    {
        signal_cancel.emit();
    }
}