#include "PimplItemDemo.hpp"

using namespace std;
using namespace gtkapp::models;

gtkapp::models::PimplItemDemo::PimplItemDemo() : PimplItemDemo{ "<Default>" }
{
	cout << "New " << *this << endl;
}

gtkapp::models::PimplItemDemo::PimplItemDemo(std::string const& name) : pimpl{ std::make_unique<Pimpl>(name) }
{
	cout << "New " << *this << endl;
}

gtkapp::models::PimplItemDemo::PimplItemDemo(PimplItemDemo&& other) noexcept
{
	std::swap(pimpl, other.pimpl);
	cout << "Move " << *this << endl;
}

PimplItemDemo& gtkapp::models::PimplItemDemo::operator=(PimplItemDemo&& other) noexcept
{
	std::swap(pimpl, other.pimpl);
	cout << "=Move " << *this << endl;
	return *this;
}

gtkapp::models::PimplItemDemo::~PimplItemDemo()
{
	if (pimpl)
	{
		cout << "Delete " << *this << endl;
		pimpl.reset();
	}
}
