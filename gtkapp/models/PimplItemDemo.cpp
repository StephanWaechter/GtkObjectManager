#include "PimplItemDemo.hpp"

using namespace std;

gtkapp::PimplItemDemo::PimplItemDemo() : PimplItemDemo{ "<Default>" }
{
	cout << "New " << *this << endl;
}

gtkapp::PimplItemDemo::PimplItemDemo(std::string const& name) : pimpl{ std::make_unique<Pimpl>(name) }
{
	cout << "New " << *this << endl;
}

gtkapp::PimplItemDemo::PimplItemDemo(PimplItemDemo&& other) noexcept
{
	std::swap(pimpl, other.pimpl);
	cout << "Move " << *this << endl;
}

gtkapp::PimplItemDemo& gtkapp::PimplItemDemo::operator=(PimplItemDemo&& other) noexcept
{
	std::swap(pimpl, other.pimpl);
	cout << "=Move " << *this << endl;
	return *this;
}

gtkapp::PimplItemDemo::~PimplItemDemo()
{
	if (pimpl)
	{
		cout << "Delete " << *this << endl;
		pimpl.reset();
	}
}
