#include "ValueItemDemo.hpp"

using namespace std;

gtkapp::ValueItemDemo::ValueItemDemo() : ValueItemDemo{ "<Default>" }
{
	cout << "New " << *this << endl;
}

gtkapp::ValueItemDemo::ValueItemDemo(std::string const& name) : Name(name)
{
	cout << "New " << *this << endl;
}

gtkapp::ValueItemDemo::ValueItemDemo(ValueItemDemo&& other) noexcept
{
	std::swap(Name, other.Name);
	cout << "Move " << *this << endl;
}

gtkapp::ValueItemDemo& gtkapp::ValueItemDemo::operator=(ValueItemDemo&& other) noexcept
{
	std::swap(Name, other.Name);
	cout << "=Move " << *this << endl;
	return *this;
}

gtkapp::ValueItemDemo::~ValueItemDemo()
{
	cout << "Delete " << *this << endl;
}

gtkapp::ValueItemDemo::ValueItemDemo(const ValueItemDemo& other)
{
	Name = other.Name;
	cout << "Copy" << *this << endl;
}


