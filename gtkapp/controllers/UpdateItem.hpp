#pragma once
#include <gtkapp/Model.hpp>
#include <gtkapp/MainWindow.hpp>
#include <gtkapp/views/UpdateItem.hpp>

namespace gtkapp::controllers
{
	struct UpdateItem : public views::UpdateItem
	{
		UpdateItem(gtkapp::MainWindow& navigation, Model& model, types::Item& item);

		void on_update_item(types::Item& item);
		void on_cancel() override;

	private:
		types::Item& m_item_ref;
		gtkapp::MainWindow& m_navigation;
		Model& m_model;
	};
}