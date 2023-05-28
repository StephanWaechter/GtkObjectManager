#include <gtkmm.h>

namespace gtkapp::widgets
{
	Gtk::Label* CreateLabel(std::string const& name)
	{
		return Gtk::make_managed<Gtk::Label>();
	}


}