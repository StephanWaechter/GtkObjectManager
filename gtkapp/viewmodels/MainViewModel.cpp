#include "MainViewModel.hpp"

using namespace gtkapp::models;

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

    sigc::signal<void(models::State const&)> MainViewModel::signal_state_changed() const
    {
        return signal_state_changed_;
    }

    models::State const& MainViewModel::get_State() const
    {
        return m_State;
    }

    void MainViewModel::set_State(models::State const& value)
    {
        OnPropertyChanged(value, m_State, signal_state_changed_);
    }

    models::Items& MainViewModel::get_Items()
    {
        return m_Items;
    }

    sigc::signal<void(models::Item&)> MainViewModel::signal_item_added() const
    {
        return signal_item_added_;
    }

    sigc::signal<void(models::Item const&)> MainViewModel::signal_item_removed() const
    {
        return signal_item_removed_;
    }

    void MainViewModel::add_Item(models::Item item)
    {
        m_Items.push_back(std::move(item));
        signal_item_added_.emit(m_Items.back());
    }

    void MainViewModel::remove_Item(models::Item const& item)
    {
        signal_item_removed_.emit(item);
        m_Items.remove(item);
    }

    models::Item* MainViewModel::get_selected_item() noexcept
    {
        return m_selected_item;
    }
    
    sigc::signal<void(models::Item* item)> MainViewModel::signal_item_selected() const
    {
        return signal_item_selected_;
    }

    void MainViewModel::select_item(Item* item)
    {
        if (item != m_selected_item)
        {
            if (item == nullptr)
            {
                std::cout << "Selection Cleared" << std::endl;
                signal_item_selected_.emit(nullptr);
                return;
            }
            else {
                m_selected_item = item;
                std::cout << "Selected:  " << *item << std::endl;
                signal_item_selected_.emit(item);
            }
        }
    }
}