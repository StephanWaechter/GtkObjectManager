#pragma once
#include <gtkapp/controllers/Controller.hpp>
#include <gtkapp/MainWindow.hpp>
#include <gtkapp/views/UpdateItem.hpp>

namespace gtkapp::controllers
{
	struct UpdateItem : public views::UpdateItem
	{
		UpdateItem(gtkapp::MainWindow& navigation, Controller& controller, models::Item& item);

		void on_update_item(models::Item& item);
		void on_cancel() override;

	private:
		models::Item& m_item_ref;
		gtkapp::MainWindow& m_navigation;
		Controller& m_controller;
	};
}