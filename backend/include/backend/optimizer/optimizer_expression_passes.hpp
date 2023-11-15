#pragma once

#include <memory>
#include <ast/syntax_tree.hpp>
#include "backend/optimizer/optimizer_base_pass.hpp"
#include "backend/optimizer/optimizer_base_aggregator_pass.hpp"
#include "backend/optimizer/optimizer_utils.hpp"

namespace optimizer {

    class ExpressionPass: public BaseAggregationPass
    {
    public:
        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

    class BinaryOperatorPass: public BaseAggregationPass
    {
    public:
        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

    class VariableDefenitonPass: public BaseAggregationPass
    {
    public:
        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

    class ConstantFoldingPass: public BasePass
    {
    public:
        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    private:
        template<class T>
        T calculateOperation(T lhs, T rhs, ast::BinaryOperation operation) {
            switch (operation) {
                case BinaryOperation::Add:
                    return lhs + rhs;
                case BinaryOperation::Sub:
                    return lhs - rhs;
                case BinaryOperation::Mult:
                    return lhs * rhs;
                case BinaryOperation::Div:
                    return lhs / rhs;
                case BinaryOperation::Equal:
                    return lhs == rhs;
                case BinaryOperation::And:
                    return lhs && rhs;
                case BinaryOperation::Or:
                    return lhs || rhs;
                case BinaryOperation::Greater:
                    return lhs > rhs;
                case BinaryOperation::GreaterEqual:
                    return lhs >= rhs;
                case BinaryOperation::Less:
                    return lhs < rhs;
                case BinaryOperation::LessEqual:
                    return lhs <= rhs;
                case BinaryOperation::NotEqual:
                    return lhs != rhs;
                default:
                    throw std::runtime_error("Unsupported oparation");
            }
        };
    };

    class ConstantPropagationPass: public BasePass
    {
    public:
        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

} // namespace optimizer
