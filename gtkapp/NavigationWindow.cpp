#include "NavigationWindow.hpp"

gtkapp::NavigationWindow::NavigationWindow()
{
	set_child(Stack_);
}

void gtkapp::NavigationWindow::Open(std::unique_ptr<Gtk::Widget> widget)
{
	Stack_.add(*widget);
	Stack_.set_visible_child(*widget);
	if (CurrentView_)
	{
		Stack_.remove(*CurrentView_);
	}
	CurrentView_.reset(widget.release());
}
