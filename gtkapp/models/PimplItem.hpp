#pragma once
#include <iostream>
#include <string>
#include <memory>

namespace gtkapp
{
    class PimplItem
    {
    private:
        struct Pimpl
        {
            Pimpl(std::string const& name) : Name{ name } {}
            std::string Name;
        };
        std::unique_ptr<Pimpl> pimpl;

    public:
        using Id = void const* const;
        Id get_Id() const { return pimpl.get(); }
        PimplItem() {};
        PimplItem(std::string const& name) : pimpl{ std::make_unique<Pimpl>(name) } {};

        inline std::string const& get_Name() const { return pimpl->Name; }
        inline PimplItem Clone(const PimplItem& other)
        {
            PimplItem pimp;
            pimp.pimpl = std::make_unique<Pimpl>(*other.pimpl);
            return pimp;
        }
    };
    inline std::ostream& operator<< (std::ostream& os, const PimplItem& item)
    {
        os << "PimplItem " << item.get_Name() << "(" << item.get_Id() << ")";
        return os;
    }
    inline bool operator==(const PimplItem& lhs, const PimplItem& rhs) { return lhs.get_Id() == rhs.get_Id(); }
    inline bool operator!=(const PimplItem& lhs, const PimplItem& rhs) { return !(lhs == rhs); }
    inline bool operator< (const PimplItem& lhs, const PimplItem& rhs) { return lhs.get_Id() < rhs.get_Id(); }
    inline bool operator> (const PimplItem& lhs, const PimplItem& rhs) { return lhs.get_Id() > rhs.get_Id(); }
    inline bool operator<=(const PimplItem& lhs, const PimplItem& rhs) { return !(lhs > rhs); }
    inline bool operator>=(const PimplItem& lhs, const PimplItem& rhs) { return !(lhs < rhs); }
}