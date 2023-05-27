#pragma once
#include <string>
#include <ostream>

namespace gtkapp
{
    // Same as normal Item but without "noisy" Constructors
    class ValueItem
    {
    public:
        using Id = void const* const;
        ValueItem() {};
        ValueItem(std::string const& name) : Name{ name } {};
        inline Id get_Id() const { return this; }
        inline std::string const& get_Name() const { return Name; }

        // Items are unique hide copy constructor behind 
        // Clone function to prevent accidental copies
        inline ValueItem Clone(const ValueItem& other) {
            return ValueItem(other);
        }
        ValueItem(ValueItem&& other) = default;
    private:
        ValueItem(const ValueItem& other) = default;
        std::string Name;
    };
    inline std::ostream& operator<< (std::ostream& os, const ValueItem& item)
    {
        os << "ValueItem " << item.get_Name() << "(" << item.get_Id() << ")";
        return os;
    }
    inline bool operator==(const ValueItem& lhs, const ValueItem& rhs) { return lhs.get_Id() == rhs.get_Id(); }
    inline bool operator!=(const ValueItem& lhs, const ValueItem& rhs) { return !(lhs == rhs); }
    inline bool operator< (const ValueItem& lhs, const ValueItem& rhs) { return lhs.get_Id() < rhs.get_Id(); }
    inline bool operator> (const ValueItem& lhs, const ValueItem& rhs) { return lhs.get_Id() > rhs.get_Id(); }
    inline bool operator<=(const ValueItem& lhs, const ValueItem& rhs) { return !(lhs > rhs); }
    inline bool operator>=(const ValueItem& lhs, const ValueItem& rhs) { return !(lhs < rhs); }
}