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
        models::State m_State{ models::State::Inactive };
    public:
        sigc::signal<void(models::State const&)> signal_state_changed;
        inline models::State const& get_State() const { return m_State; }
        inline void set_State(models::State const& value)
        {
            OnPropertyChanged(value, m_State, signal_state_changed);
        }

    private:
        models::Items m_Items;
    public:
        inline models::Items & get_Items() { return m_Items; }
        sigc::signal<void(models::Item &)> signal_item_added;
        inline void add_Item(models::Item item)
        {
            m_Items.push_back(std::move(item));
            signal_item_added.emit(m_Items.back());
        }
        sigc::signal<void(models::Item const&)> signal_item_removed;
        inline void remove_Item(models::Item const& item)
        {
            signal_item_removed.emit(item);
            m_Items.remove(item);
        }

    private:
        models::Item* m_selected_item{ nullptr };
    
    public:
        inline models::Item* get_selected_item() noexcept
        {
            return m_selected_item;
        }

        sigc::signal<void(models::Item* item)> signal_item_selected;
        void select_item(models::Item* item = nullptr);
    };
} // namespace gtkapp
