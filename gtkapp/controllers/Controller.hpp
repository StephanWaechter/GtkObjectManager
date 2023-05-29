#pragma once
#include <gtkapp/models/common.hpp>
#include <sigc++/sigc++.h>
#include <string>
#include <iostream>
#include <optional>

namespace gtkapp::controllers
{
    class Controller : public sigc::trackable
    {
    private:
        
    public:
        Controller();
        ~Controller();

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
        sigc::signal<void(models::State const&)> signal_state_changed_;
    public:
        sigc::signal<void(models::State const&)> signal_state_changed() const;
        models::State const& get_State() const;
        void set_State(models::State const& value);

    private:
        models::Items m_Items;
        sigc::signal<void(models::Item&)> signal_item_added_;
        sigc::signal<void(models::Item const&)> signal_item_removed_;

    public:
        models::Items& get_Items();
        sigc::signal<void(models::Item &)> signal_item_added() const;
        sigc::signal<void(models::Item const&)> signal_item_removed() const;
        void add_Item(models::Item item);
        void remove_Item(models::Item const& item);      

    private:
        models::Item const* m_selected_item{ nullptr };
        sigc::signal<void(models::Item const* item)> signal_item_selected_;
    
    public:
        models::Item const* get_selected_item() noexcept;
        sigc::signal<void(models::Item const* item)> signal_item_selected() const;
        void select_item(models::Item const* item = nullptr);
    };
} // namespace gtkapp
