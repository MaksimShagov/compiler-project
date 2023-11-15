
#include "optimizer/optimizer_base_aggregator_pass.hpp"
#include "optimizer/optimizer_pass_statistic.hpp"

using namespace ast;
using namespace optimizer;

void BaseAggregationPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

std::shared_ptr<PassStatistic> BaseAggregationPass::statistic() {

    return collectedStatistic;

}

void BaseAggregationPass::addPass(const BaseAggregationPass::PassDescription &desc) {
    if (passesAggregator.find(desc.first) == passesAggregator.end()) {
        passesAggregator.emplace(
            desc.first,
            std::vector<BasePass*>{desc.second}
        );

    } else {
        passesAggregator[desc.first].push_back(desc.second);
    }
}
