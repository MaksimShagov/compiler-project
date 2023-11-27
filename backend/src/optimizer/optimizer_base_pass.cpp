
#include "optimizer/optimizer_base_pass.hpp"
#include "optimizer/optimizer_pass_statistic.hpp"

using namespace ast;
using namespace optimizer;

bool BasePass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    bool optimized = this->compute(node, ctx);

    // statistic calculaton logic

    return optimized;
}

std::shared_ptr<PassStatistic> BasePass::statistic() {

    return collectedStatistic;

}