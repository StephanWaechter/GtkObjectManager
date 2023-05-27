#include "ValueItemDemo.hpp"

using namespace std;
using namespace gtkapp::models;

gtkapp::models::ValueItemDemo::ValueItemDemo() : ValueItemDemo{ "<Default>" }
{
	cout << "New " << *this << endl;
}

gtkapp::models::ValueItemDemo::ValueItemDemo(std::string const& name) : Name(name)
{
	cout << "New " << *this << endl;
}

gtkapp::models::ValueItemDemo::ValueItemDemo(ValueItemDemo&& other) noexcept
{
	std::swap(Name, other.Name);
	cout << "Move " << *this << endl;
}

ValueItemDemo& gtkapp::models::ValueItemDemo::operator=(ValueItemDemo&& other) noexcept
{
	std::swap(Name, other.Name);
	cout << "=Move " << *this << endl;
	return *this;
}

gtkapp::models::ValueItemDemo::~ValueItemDemo()
{
	cout << "Delete " << *this << endl;
}

gtkapp::models::ValueItemDemo::ValueItemDemo(const ValueItemDemo& other)
{
	Name = other.Name;
	cout << "Copy" << *this << endl;
}


