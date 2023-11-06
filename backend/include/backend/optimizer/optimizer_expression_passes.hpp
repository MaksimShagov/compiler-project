#pragma once

#include <memory>
#include <ast/syntax_tree.hpp>
#include "backend/optimizer/optimizer_passes_dict.hpp"
#include "backend/optimizer/optimizer_base_pass.hpp"

namespace optimizer {

    class ExpressionPass: public BasePass
    {
        PassesDict::PassesAggregation expressionPasses;
    public:
        ExpressiontPass(PassesDict::PassesAggregation &desc);
        ~ExpressiontPass() = default;

        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

    class BinaryOperatorPass: public BasePass
    {
        PassesDict::PassesAggregation BinaryOperatorPasses;
    public:
        BinaryOperatorPass(PassesDict::PassesAggregation &desc);
        ~BinaryOperatorPass() = default;

        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

} // namespace optimizer
