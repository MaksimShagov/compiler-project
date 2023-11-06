#pragma once
#include <memory>

#include <ast/functions_table.hpp>
#include <ast/node.hpp>
#include <ast/variables_table.hpp>

#include "backend/optimizer/optimizer_context.hpp"
#include "backend/optimizer/optimizer_pass_statistic.hpp"

namespace optimizer {

    class IAbstractPass {
    public:
        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) = 0;
        virtual std::shared_ptr<PassStatistic> statistic() = 0;
    };

} // namespace optimizer
