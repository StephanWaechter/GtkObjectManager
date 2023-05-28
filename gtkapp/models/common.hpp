#pragma once
#include <list>
#include "Item.hpp"

namespace gtkapp::models
{
    enum class State
    {
        Active,
        Inactive
    };

    using Items = std::list<Item>;
} // namespace gtkapp
