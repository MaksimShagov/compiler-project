#include <stdexcept>

#include "optimizer/optimizer_function_pass.hpp"

using namespace ast;
using namespace optimizer;


std::shared_ptr<PassStatistic> FunctionPass::statistic() {

    return collectedStatistic;

}

bool FunctionPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    if (node->type != NodeType::ProgramRoot) {
        throw std::logic_error("ERROR: exepted ProgrammRoot node in FunctionPass");
    }

    for (auto &function : node->children) {
        if (function->type == NodeType::FunctionDefinition &&
            passesAggregator.find(NodeType::BranchRoot) != passesAggregator.end()) {
            auto function_attributes = function->children.begin();
            std::advance(function_attributes, 3); // BranchRoot
            ctx.startScope(*function_attributes);
            for (auto &pass: passesAggregator[NodeType::BranchRoot]) {
                pass->procces(*function_attributes, ctx);
            }
            ctx.endScope();
        }
    }
    return false;
}
