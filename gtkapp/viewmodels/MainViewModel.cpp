#include "MainViewModel.hpp"

namespace gtkapp::viewmodels
{
    MainViewModel::MainViewModel()
    {
        m_Items.emplace_back(Item("Stephan"));
        m_Items.emplace_back(Item("Florian"));
        m_Items.emplace_back(Item("Benedikt"));
        std::cout << m_Items.size() << std::endl;
    }
    
    MainViewModel::~MainViewModel()
    {
    }
}