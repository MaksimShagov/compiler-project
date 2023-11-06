#pragma once

#include <memory>
#include <ast/syntax_tree.hpp>
#include "backend/optimizer/optimizer_passes_dict.hpp"
#include "backend/optimizer/optimizer_base_pass.hpp"

namespace optimizer {

    class BranchRootPass: public BasePass
    {
        PassesDict::PassesAggregation branchRootPasses;
    public:
        BranchRootPass(PassesDict::PassesAggregation &desc);
        ~BranchRootPass() = default;

        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

} // namespace optimizer
