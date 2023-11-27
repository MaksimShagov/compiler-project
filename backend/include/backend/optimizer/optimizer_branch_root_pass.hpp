#pragma once

#include <memory>
#include <ast/syntax_tree.hpp>

#include "backend/optimizer/optimizer_base_aggregator_pass.hpp"

namespace optimizer {

    class BranchRootPass: public BaseAggregationPass
    {
    public:
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

} // namespace optimizer
