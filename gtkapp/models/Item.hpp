#pragma once
#include <iostream>
#include <string>
#include <memory>

namespace gtkapp::models
{
    class Item
    {
    private:
        struct ItemData
        {
            ItemData(std::string const& name) : Name{ name } {}
            std::string Name;
        };
        std::unique_ptr<ItemData> pimpl;

    public:
        using Id = void const* const;
        Id get_Id() const { return pimpl.get(); }
        Item() {};
        Item(std::string const& name) : pimpl{ std::make_unique<ItemData>(name) } {};

        inline std::string const& get_Name() const { return pimpl->Name; }
        inline Item Clone(const Item& other)
        {
            Item pimp;
            pimp.pimpl = std::make_unique<ItemData>(*other.pimpl);
            return pimp;
        }
    };
    inline std::ostream& operator<< (std::ostream& os, const Item& item)
    {
        os << "Item " << item.get_Name() << "(" << item.get_Id() << ")";
        return os;
    }
    inline bool operator==(const Item& lhs, const Item& rhs) { return lhs.get_Id() == rhs.get_Id(); }
    inline bool operator!=(const Item& lhs, const Item& rhs) { return !(lhs == rhs); }
    inline bool operator< (const Item& lhs, const Item& rhs) { return lhs.get_Id() < rhs.get_Id(); }
    inline bool operator> (const Item& lhs, const Item& rhs) { return lhs.get_Id() > rhs.get_Id(); }
    inline bool operator<=(const Item& lhs, const Item& rhs) { return !(lhs > rhs); }
    inline bool operator>=(const Item& lhs, const Item& rhs) { return !(lhs < rhs); }
}