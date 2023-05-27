#pragma once
#include <iostream>
#include <string>
#include <memory>

namespace gtkapp::models
{
    class PimplItemDemo
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
        PimplItemDemo();
        PimplItemDemo(std::string const& name);

        PimplItemDemo(PimplItemDemo&& other) noexcept;
        PimplItemDemo& operator= (PimplItemDemo&& other) noexcept;
        ~PimplItemDemo();
        inline std::string const& get_Name() const { return pimpl->Name; }
        inline PimplItemDemo Clone(const PimplItemDemo& other)
        {
            PimplItemDemo pimp;
            pimp.pimpl = std::make_unique<Pimpl>(*other.pimpl);
            return pimp;
        }
    };
    inline std::ostream& operator<< (std::ostream& os, const PimplItemDemo& item)
    {
        os << "PimplItemDemo " << item.get_Name() << "(" << item.get_Id() << ")";
        return os;
    }
    inline bool operator==(const PimplItemDemo& lhs, const PimplItemDemo& rhs) { return lhs.get_Id() == rhs.get_Id(); }
    inline bool operator!=(const PimplItemDemo& lhs, const PimplItemDemo& rhs) { return !(lhs == rhs); }
    inline bool operator< (const PimplItemDemo& lhs, const PimplItemDemo& rhs) { return lhs.get_Id() < rhs.get_Id(); }
    inline bool operator> (const PimplItemDemo& lhs, const PimplItemDemo& rhs) { return lhs.get_Id() > rhs.get_Id(); }
    inline bool operator<=(const PimplItemDemo& lhs, const PimplItemDemo& rhs) { return !(lhs > rhs); }
    inline bool operator>=(const PimplItemDemo& lhs, const PimplItemDemo& rhs) { return !(lhs < rhs); }
}