#include "Controller.hpp"

using namespace gtkapp::models;

namespace gtkapp::controllers
{
    Controller::Controller()
    {
        m_Items.emplace_back(Item("Stephan"));
        m_Items.emplace_back(Item("Florian"));
        m_Items.emplace_back(Item("Benedikt"));
    }
    
    Controller::~Controller()
    {
    }

    sigc::signal<void(models::State const&)> Controller::signal_state_changed() const
    {
        return signal_state_changed_;
    }

    models::State const& Controller::get_State() const
    {
        return m_State;
    }

    void Controller::set_State(models::State const& value)
    {
        OnPropertyChanged(value, m_State, signal_state_changed_);
    }

    models::Items& Controller::get_Items()
    {
        return m_Items;
    }

    sigc::signal<void(models::Item&)> Controller::signal_item_added() const
    {
        return signal_item_added_;
    }

    sigc::signal<void(models::Item const&)> Controller::signal_item_removed() const
    {
        return signal_item_removed_;
    }

    void Controller::add_Item(models::Item item)
    {
        m_Items.push_back(std::move(item));
        signal_item_added_.emit(m_Items.back());
    }

    void Controller::remove_Item(models::Item const& item)
    {
        signal_item_removed_.emit(item);
        m_Items.remove(item);
    }

    models::Item const* Controller::get_selected_item() noexcept
    {
        return m_selected_item;
    }
    
    sigc::signal<void(models::Item const* item)> Controller::signal_item_selected() const
    {
        return signal_item_selected_;
    }

    void Controller::select_item(Item const* item)
    {
        if (item != m_selected_item)
        {
            m_selected_item = item;
            if (item == nullptr)
            {
                std::cout << "Selection Cleared" << std::endl;
                signal_item_selected_.emit(nullptr);
                return;
            }
            else 
            {
                std::cout << "Selected:  " << *item << std::endl;
                signal_item_selected_.emit(item);
            }
        }
    }
}