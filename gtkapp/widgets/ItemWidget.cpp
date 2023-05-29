#include "ItemWidget.hpp"
namespace gtkapp::widgets
{
	ItemWidget::ItemWidget()
	{
		set_orientation(Gtk::Orientation::VERTICAL);
		append(
			*Gtk::make_managed<Gtk::Label>("Name")
		);

		append(Name);

		Name.signal_changed().connect(sigc::mem_fun(*this, &ItemWidget::update_is_valid_item));
	}

	sigc::signal<void(bool)> ItemWidget::signal_is_valid_item_changed()
	{
		return signal_is_valid_item_changed_;
	}

	bool ItemWidget::is_valid_item()
	{
		return false;
	}

	models::Item ItemWidget::create_item()
	{
		return models::Item(Name.get_text());
	}

	void ItemWidget::set_item_values(const models::Item& item)
	{
		Name.set_text( item.get_Name() );
	}

	void ItemWidget::update_is_valid_item()
	{
		bool is_valid;
		is_valid = Name.get_text().size() > 0;
		if (is_valid_item_ != is_valid)
		{
			is_valid_item_ = is_valid;
			signal_is_valid_item_changed_.emit(is_valid_item_);
		}
	}
}