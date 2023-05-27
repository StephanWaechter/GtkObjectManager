#pragma once
#include <iostream>
#include <string>
#include <ostream>

namespace gtkapp::models
{
    class ValueItemDemo
    {
    public:
        using Id = void const* const;
        ValueItemDemo();
        ValueItemDemo(std::string const& name);
        ValueItemDemo(ValueItemDemo&& other) noexcept;
        ValueItemDemo& operator= (const ValueItemDemo& other) = delete;
        ValueItemDemo& operator= (ValueItemDemo&& other) noexcept;
        ~ValueItemDemo();
        inline Id get_Id() const { return this; }
        inline std::string const& get_Name() const { return Name; }

        // Items are unique hide copy constructor behind 
        // Clone function to prevent accidental copies
        inline ValueItemDemo Clone(const ValueItemDemo& other)
        {
            return other;
        }
    private:
        ValueItemDemo(const ValueItemDemo& other);


        std::string Name;
    };
    inline std::ostream& operator<< (std::ostream& os, const ValueItemDemo& item)
    {
        os << "ValueItemDemo " << item.get_Name() << "(" << item.get_Id() << ")";
        return os;
    }
    inline bool operator==(const ValueItemDemo& lhs, const ValueItemDemo& rhs) { return lhs.get_Id() == rhs.get_Id(); }
    inline bool operator!=(const ValueItemDemo& lhs, const ValueItemDemo& rhs) { return !(lhs == rhs); }
    inline bool operator< (const ValueItemDemo& lhs, const ValueItemDemo& rhs) { return lhs.get_Id() < rhs.get_Id(); }
    inline bool operator> (const ValueItemDemo& lhs, const ValueItemDemo& rhs) { return lhs.get_Id() > rhs.get_Id(); }
    inline bool operator<=(const ValueItemDemo& lhs, const ValueItemDemo& rhs) { return !(lhs > rhs); }
    inline bool operator>=(const ValueItemDemo& lhs, const ValueItemDemo& rhs) { return !(lhs < rhs); }
}