#pragma once
#include <gtkapp/MainWindow.hpp>
#include <gtkapp/controllers/Controller.hpp>
#include <gtkapp/views/AddNewItem.hpp>

namespace gtkapp::controllers
{
	struct AddNewItem : public views::AddNewItem
	{
		AddNewItem(gtkapp::MainWindow& navigation, Controller& controller);

		void on_create_new_item(models::Item item) override;
		void on_cancel() override;

	private:
		gtkapp::MainWindow& m_navigation;
		Controller& m_controller;
	};
}