#pragma once
#include <gtkmm.h>

namespace gtkapp
{
	class NavigationWindow : public Gtk::ApplicationWindow
	{
	public:
		NavigationWindow();

		void Open(std::unique_ptr<Gtk::Widget> widget);

	private:
		Gtk::Stack Stack_;
		std::unique_ptr<Gtk::Widget> CurrentView_{ nullptr };
	};
}