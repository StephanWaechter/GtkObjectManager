#pragma once
#include <gtkmm.h>
#include <gtkapp/types/common.hpp>

namespace gtkapp::widgets
{
	class ItemWidget :public Gtk::Box
	{
	public:
		ItemWidget();

		sigc::signal<void(bool)> signal_is_valid_item_changed();
		bool is_valid_item();
		types::Item create_item();

		void set_item_values(const types::Item& item);

	private:
		sigc::signal<void(bool)> signal_is_valid_item_changed_;
		bool is_valid_item_{ false };
		void update_is_valid_item();
		Gtk::Entry Name;
	};
}