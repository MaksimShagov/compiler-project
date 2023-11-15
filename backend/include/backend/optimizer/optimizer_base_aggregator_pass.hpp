#pragma once

#include <map>
#include <memory>

#include <ast/syntax_tree.hpp>

#include "backend/optimizer/optimizer_pass_statistic.hpp"
#include "backend/optimizer/optimizer_base_pass.hpp"

namespace optimizer {

    class BaseAggregationPass: public BasePass
    {
    public:
        using PassDescription = std::pair<ast::NodeType, BasePass*>;
        using PassesAggregation = std::map<ast::NodeType, std::vector<BasePass*>>;

        BaseAggregationPass() = default;
        BaseAggregationPass(const PassesAggregation &aggregator);
        ~BaseAggregationPass() = default;

        virtual void procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual void addPass(const PassDescription &desc);
        virtual std::shared_ptr<PassStatistic> statistic() override;
    protected:
        virtual void compute(ast::Node::Ptr &node, OptimizerContext &ctx) = 0;
        PassesAggregation passesAggregator;
    };

} // namespace optimizer




