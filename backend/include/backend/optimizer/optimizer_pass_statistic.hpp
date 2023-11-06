#pragma once

#include <ast/functions_table.hpp>
#include <ast/node.hpp>
#include <ast/variables_table.hpp>

#include "backend/optimizer/optimizer_context.hpp"

namespace optimizer {

    class PassStatistic {
    public:
        PassStatistic() = default;
        PassStatistic(const PassStatistic&) = default;
        ~PassStatistic() = default;

        int i = 0;
    };

} // namespace optimizer
