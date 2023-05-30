#include "Model.hpp"

using namespace gtkapp::types;

namespace gtkapp
{
    Model::Model()
    {
        m_Items.emplace_back(Item("Stephan"));
        m_Items.emplace_back(Item("Florian"));
        m_Items.emplace_back(Item("Benedikt"));
    }
    
    Model::~Model()
    {
    }

    sigc::signal<void(types::State const&)> Model::signal_state_changed() const
    {
        return signal_state_changed_;
    }

    types::State const& Model::get_State() const
    {
        return m_State;
    }

    void Model::set_State(types::State const& value)
    {
        OnPropertyChanged(value, m_State, signal_state_changed_);
    }

    types::Items& Model::get_Items()
    {
        return m_Items;
    }

    sigc::signal<void(types::Item&)> Model::signal_item_updated() const
    {
        return signal_item_updated_;
    }

    sigc::signal<void(types::Item&)> Model::signal_item_added() const
    {
        return signal_item_added_;
    }

    sigc::signal<void(types::Item const&)> Model::signal_item_removed() const
    {
        return signal_item_removed_;
    }

    void Model::update_item(types::Item& item, types::Item const & new_values)
    {
        item.Update(new_values);
    }

    void Model::add_Item(types::Item item)
    {
        m_Items.push_back(std::move(item));
        signal_item_added_.emit(m_Items.back());
    }

    void Model::remove_Item(types::Item const& item)
    {
        signal_item_removed_.emit(item);
        m_Items.remove(item);
    }

    types::Item const* Model::get_selected_item() noexcept
    {
        return m_selected_item;
    }
    
    sigc::signal<void(types::Item const* item)> Model::signal_item_selected() const
    {
        return signal_item_selected_;
    }

    void Model::select_item(Item const* item)
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