
#include "optimizer/optimizer_base_aggregator_pass.hpp"
#include "optimizer/optimizer_pass_statistic.hpp"

using namespace ast;
using namespace optimizer;

bool BaseAggregationPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    bool optimized = this->compute(node, ctx);

    // statistic calculaton logic

    return optimized;
}

std::shared_ptr<PassStatistic> BaseAggregationPass::statistic() {

    return collectedStatistic;

}

void BaseAggregationPass::addPass(const BaseAggregationPass::PassDescription &desc) {
    if (passesAggregator.find(desc.first) == passesAggregator.end()) {
        passesAggregator.emplace(
            desc.first,
            std::vector<BasePassPtr>{desc.second}
        );

    } else {
        passesAggregator[desc.first].push_back(desc.second);
    }
}
