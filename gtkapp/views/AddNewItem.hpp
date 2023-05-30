#pragma once
#include <gtkmm.h>
#include <gtkapp/types/common.hpp>
#include <gtkapp/widgets/ItemWidget.hpp>

namespace gtkapp::views
{
	struct AddNewItem : public Gtk::Box
	{
		AddNewItem();
		~AddNewItem();

		widgets::ItemWidget Item;
		Gtk::Button Create;
		Gtk::Button Cancel;

		sigc::signal<void(types::Item& item)> signal_create_new_item;
		virtual void on_create_new_item(types::Item item);
		sigc::signal<void(void)> signal_cancel;
		virtual void on_cancel();

	private:
		void on_create_clicked();
		void on_cancel_clicked();
	};
}