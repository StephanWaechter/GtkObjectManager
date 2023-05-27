#pragma once
#include <gtkapp/models/common.hpp>
#include <sigc++/sigc++.h>
#include <string>
#include <iostream>
#include <optional>

namespace gtkapp::viewmodels
{
    class MainViewModel
    {
    private:
        
    public:
        MainViewModel();
        ~MainViewModel();

    private:
        template<typename T> static void OnPropertyChanged(T const& value, T& ref_value, sigc::signal<void(T const&)>& signal)
        {
            if(value != ref_value)
            {
                ref_value = value;
                signal.emit(ref_value);
            }
        }

    private:
        State m_State{ State::Inactive };
    public:
        sigc::signal<void(State const&)> signal_state_changed;
        inline State const& get_State() const { return m_State; }
        inline void set_State(State const& value)
        {
            OnPropertyChanged(value, m_State, signal_state_changed);
        }

    private:
        Items m_Items;
    public:
        inline Items & get_Items() { return m_Items; }
        sigc::signal<void(Item &)> signal_item_added;
        inline void add_Item(Item item)
        {
            m_Items.push_back(std::move(item));
            signal_item_added.emit(m_Items.back());
        }
        sigc::signal<void(Item const&)> signal_item_removed;
        inline void remove_Item(Item const& item)
        {
            signal_item_removed.emit(item);
            m_Items.remove(item);
        }

    private:
        Item* m_selected_item{ nullptr };
    
    public:
        inline Item* get_selected_item() noexcept
        {
            return m_selected_item;
        }

        sigc::signal<void(Item* item)> signal_item_selected;
        void select_item(Item* item = nullptr);
    };
} // namespace gtkapp
