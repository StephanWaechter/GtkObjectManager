#pragma once
#include <list>
#include "Item.hpp"

namespace gtkapp::types
{
    enum class State
    {
        Active,
        Inactive
    };

    using Items = std::list<Item>;
} // namespace gtkapp
