#pragma once
#include <gtkapp/Model.hpp>
#include <gtkapp/MainWindow.hpp>
#include <gtkapp/views/AddNewItem.hpp>

namespace gtkapp::controllers
{
	struct AddNewItem : public views::AddNewItem
	{
		AddNewItem(gtkapp::MainWindow& navigation, Model& model);

		void on_create_new_item(types::Item item) override;
		void on_cancel() override;

	private:
		gtkapp::MainWindow& m_navigation;
		Model& m_model;
	};
}