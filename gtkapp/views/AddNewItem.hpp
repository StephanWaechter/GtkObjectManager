#pragma once
#include <gtkmm.h>
#include <gtkapp/models/common.hpp>
#include <gtkapp/widgets/ItemWidget.hpp>
#include <gtkapp/controllers/Controller.hpp>
#include <gtkapp/MainWindow.hpp>

namespace gtkapp::views
{
	struct AddNewItem : public Gtk::Box
	{
		AddNewItem();
		~AddNewItem();

		widgets::ItemWidget Item;
		Gtk::Button Create;
		Gtk::Button Cancel;

		sigc::signal<void(models::Item& item)> signal_create_new_item;
		sigc::signal<void(void)> signal_cancel;

	private:
		void on_create_clicked();
		void on_cancel_clicked();
		controllers::Controller* DataContext;
	};

	void bind(MainWindow& mainWindow, controllers::Controller& controller, AddNewItem& view);
}