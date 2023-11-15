
#include "optimizer/optimizer_utils.hpp"
#include "optimizer/optimizer_branch_root_pass.hpp"

using namespace ast;
using namespace optimizer;

void BranchRootPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

std::shared_ptr<PassStatistic> BranchRootPass::statistic() {
    return collectedStatistic;
}

void BranchRootPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    for (auto child = node->children.begin(); child != node->children.end(); child++) {
        NodeType type = nodeTypeIterator(child);

        for (auto &pass : passesAggregator[type]) {
            pass->procces(*child, ctx);
        }

    }
}
