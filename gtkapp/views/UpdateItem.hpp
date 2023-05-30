#pragma once
#include <gtkmm.h>
#include <gtkapp/types/common.hpp>
#include <gtkapp/widgets/ItemWidget.hpp>
#include <gtkapp/Model.hpp>
#include <gtkapp/MainWindow.hpp>

namespace gtkapp::views
{
	struct UpdateItem : public Gtk::Box
	{
		UpdateItem();
		~UpdateItem();

		widgets::ItemWidget Item;
		Gtk::Button Update;
		Gtk::Button Cancel;

		sigc::signal<void(types::Item& item)> signal_update_item;
		virtual void on_update_item(types::Item& item);
		sigc::signal<void(void)> signal_cancel;
		virtual void on_cancel();

	private:
		
		void on_update_clicked();
		void on_cancel_clicked();
	};
}