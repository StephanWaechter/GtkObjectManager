#pragma once
#include <gtkmm.h>
#include <gtkapp/models/common.hpp>
#include <gtkapp/widgets/ItemWidget.hpp>
#include <gtkapp/viewmodels/MainViewModel.hpp>

namespace gtkapp::views
{
	struct AddNewItem : public Gtk::Box
	{
		AddNewItem();
		AddNewItem(viewmodels::MainViewModel* dataContext) : AddNewItem() { bind(dataContext); }
		~AddNewItem();

		widgets::ItemWidget Item;
		Gtk::Button Create;
		Gtk::Button Cancel;

		void bind(viewmodels::MainViewModel* dataContext);
	private:
		
		viewmodels::MainViewModel* DataContext;
	};
}