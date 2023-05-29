#pragma once
#include <gtkmm.h>
#include <gtkapp/models/common.hpp>
#include <gtkapp/widgets/ItemWidget.hpp>
#include <gtkapp/controllers/Controller.hpp>
#include <gtkapp/MainWindow.hpp>

namespace gtkapp::views
{
	struct UpdateItem : public Gtk::Box
	{
		UpdateItem(models::Item& item);
		~UpdateItem();

		widgets::ItemWidget Item;
		Gtk::Button Update;
		Gtk::Button Cancel;

		sigc::signal<void(models::Item& item)> signal_update_item;
		sigc::signal<void(void)> signal_cancel;
		
		models::Item& ItemRef;

	private:
		
		void on_update_clicked();
		void on_cancel_clicked();
	};

	void bind(MainWindow& mainWindow, controllers::Controller& controller, UpdateItem& view);
}