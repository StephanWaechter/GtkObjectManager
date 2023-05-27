#pragma once
#include <string>
#include <list>
#include <memory>
namespace gtkapp
{
    enum class State
    {
        Active,
        Inactive
    };

    class Item
    {
    public:
        using Id = void const* const;
        Id get_Id() const { return this; }
        Item() = default;
        Item(std::string const& name) : Name(name) {}
        inline std::string const& get_Name() const { return Name; }

        private:
            std::string Name;
    };
    inline bool operator==(const Item& lhs, const Item& rhs) { return lhs.get_Id() == rhs.get_Id(); }
    inline bool operator!=(const Item& lhs, const Item& rhs) { return !(lhs == rhs); }
    inline bool operator< (const Item& lhs, const Item& rhs) { return lhs.get_Id() <  rhs.get_Id(); }
    inline bool operator> (const Item& lhs, const Item& rhs) { return lhs.get_Id() >  rhs.get_Id(); }
    inline bool operator<=(const Item& lhs, const Item& rhs) { return !(lhs > rhs); }
    inline bool operator>=(const Item& lhs, const Item& rhs) { return !(lhs < rhs); }
    
    using Items = std::list<Item>;
} // namespace gtkapp
