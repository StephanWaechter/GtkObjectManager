#include "MainViewModel.hpp"

namespace gtkapp::viewmodels
{
    MainViewModel::MainViewModel()
    {
        m_Items.emplace_back(Item("Stephan"));
        m_Items.emplace_back(Item("Florian"));
        m_Items.emplace_back(Item("Benedikt"));
    }
    
    MainViewModel::~MainViewModel()
    {
    }

    void MainViewModel::select_item(Item* item)
    {
        if (item != m_selected_item)
        {
            if (item == nullptr)
            {
                std::cout << "Selection Cleared" << std::endl;
                signal_item_selected.emit(nullptr);
                return;
            }
            else {
                m_selected_item = item;
                std::cout << "Selected:  " << *item << std::endl;
                signal_item_selected.emit(item);
            }
        }
    }
}