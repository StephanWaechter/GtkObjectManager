#pragma once
#include <list>
#include "ValueItem.hpp"
#include "ValueItemDemo.hpp"
#include "PimplItem.hpp"
#include "PimplItemDemo.hpp"

namespace gtkapp
{
    enum class State
    {
        Active,
        Inactive
    };

    using Item = PimplItemDemo;
    using Items = std::list<Item>;
} // namespace gtkapp
