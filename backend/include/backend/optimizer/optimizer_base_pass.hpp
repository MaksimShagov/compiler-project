#pragma once

#include <memory>
#include <ast/syntax_tree.hpp>

#include "backend/optimizer/optimizer_pass_statistic.hpp"
#include "backend/optimizer/optimizer_abstract_pass.hpp"

namespace optimizer {

    class BasePass: public IAbstractPass
    {
    public:
        BasePass() = default;
        ~BasePass() = default;

        virtual bool procces(ast::Node::Ptr &node, OptimizerContext &ctx) override;
        virtual std::shared_ptr<PassStatistic> statistic() override;
    protected:
        virtual bool compute(ast::Node::Ptr &node, OptimizerContext &ctx) = 0;
        std::shared_ptr<PassStatistic> collectedStatistic;
    };

    using BasePassPtr = std::shared_ptr<BasePass>;
} // namespace optimizer




