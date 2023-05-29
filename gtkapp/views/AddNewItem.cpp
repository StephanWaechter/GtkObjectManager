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
        signal_create_new_item.emit(
            Item.create_item()
        );
    }

    void AddNewItem::on_cancel_clicked()
    {
        signal_cancel.emit();
    }

    void bind(MainWindow& mainWindow, controllers::Controller& controller, AddNewItem& view)
    {
        view.signal_create_new_item.connect(
            [&](models::Item& item) {
                controller.add_Item(std::move(item));
                mainWindow.OpenMainView();
            }
        );

        view.signal_cancel.connect(
            [&] { mainWindow.OpenMainView(); }
        );
    }
}