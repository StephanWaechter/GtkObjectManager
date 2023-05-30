#pragma once
#include <gtkapp/types/common.hpp>
#include <sigc++/sigc++.h>
#include <string>
#include <iostream>
#include <optional>

namespace gtkapp
{
    class Model : public sigc::trackable
    {
    private:
        
    public:
        Model();
        ~Model();

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
        types::State m_State{ types::State::Inactive };
        sigc::signal<void(types::State const&)> signal_state_changed_;

    public:
        sigc::signal<void(types::State const&)> signal_state_changed() const;
        types::State const& get_State() const;
        void set_State(types::State const& value);

    private:
        types::Items m_Items;
        sigc::signal<void(types::Item&)> signal_item_updated_;
        sigc::signal<void(types::Item&)> signal_item_added_;
        sigc::signal<void(types::Item const&)> signal_item_removed_;

    public:
        types::Items& get_Items();
        sigc::signal<void(types::Item&)> signal_item_updated() const;
        sigc::signal<void(types::Item&)> signal_item_added() const;
        sigc::signal<void(types::Item const&)> signal_item_removed() const;
        void update_item(types::Item & item, types::Item const& new_values);
        void add_Item(types::Item item);
        void remove_Item(types::Item const& item);

    private:
        types::Item const* m_selected_item{ nullptr };
        sigc::signal<void(types::Item const* item)> signal_item_selected_;
    
    public:
        types::Item const* get_selected_item() noexcept;
        sigc::signal<void(types::Item const* item)> signal_item_selected() const;
        void select_item(types::Item const* item = nullptr);
    };
} // namespace gtkapp
