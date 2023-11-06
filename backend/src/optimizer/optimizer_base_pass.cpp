
#include "optimizer/optimizer_base_pass.hpp"
#include "optimizer/optimizer_pass_statistic.hpp"

using namespace ast;
using namespace optimizer;

void BasePass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

std::shared_ptr<PassStatistic> BasePass::statistic() {

    return collected_statistic;

}