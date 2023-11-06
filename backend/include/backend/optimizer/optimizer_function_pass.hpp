#pragma once

#include <memory>
#include <ast/syntax_tree.hpp>

#include "backend/optimizer/optimizer_base_pass.hpp"
#include "backend/optimizer/optimizer_passes_dict.hpp"
namespace optimizer {

    class FunctionPass: public BasePass
    {
        PassesDict::PassesAggregation functionRootPasses;
    public:
        FunctionPass(const PassesDict::PassesAggregation &desc);

        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic() override;
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

} // namespace optimizer
