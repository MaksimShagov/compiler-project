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
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

    class BinaryOperatorPass: public BaseAggregationPass
    {
    public:
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

    class VariableDefenitonPass: public BaseAggregationPass
    {
    public:
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    };

    class ConstantFoldingPass: public BasePass
    {
    public:
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    private:
        template<class T>
        T calculateOperation(T lhs, T rhs, ast::BinaryOperation operation) {
            switch (operation) {
                case BinaryOperation::Add:
                case BinaryOperation::FAdd:
                    return lhs + rhs;
                case BinaryOperation::Sub:
                case BinaryOperation::FSub:
                    return lhs - rhs;
                case BinaryOperation::Mult:
                case BinaryOperation::FMult:
                    return lhs * rhs;
                case BinaryOperation::Div:
                case BinaryOperation::FDiv:
                    return lhs / rhs;
                case BinaryOperation::Equal:
                case BinaryOperation::FEqual:
                    return lhs == rhs;
                case BinaryOperation::And:
                case BinaryOperation::FAnd:
                    return lhs && rhs;
                case BinaryOperation::Or:
                case BinaryOperation::FOr:
                    return lhs || rhs;
                case BinaryOperation::Greater:
                case BinaryOperation::FGreater:
                    return lhs > rhs;
                case BinaryOperation::GreaterEqual:
                case BinaryOperation::FGreaterEqual:
                    return lhs >= rhs;
                case BinaryOperation::Less:
                case BinaryOperation::FLess:
                    return lhs < rhs;
                case BinaryOperation::LessEqual:
                case BinaryOperation::FLessEqual:
                    return lhs <= rhs;
                case BinaryOperation::NotEqual:
                case BinaryOperation::FNotEqual:
                    return lhs != rhs;
                default:
                    throw std::runtime_error("Unsupported oparation");
            }
        };
    };

    class ConstantPropagationPass: public BasePass
    {
    public:
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    private:
        bool propagate(ast::Node::Ptr &node, OptimizerContext &ctx);
    };

    class TypeConversionPass: public BasePass
    {
    public:
        virtual std::shared_ptr<PassStatistic> statistic();
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) override;
    private:
        bool conversion(ast::Node::Ptr &node, OptimizerContext &ctx);
    };

} // namespace optimizer
