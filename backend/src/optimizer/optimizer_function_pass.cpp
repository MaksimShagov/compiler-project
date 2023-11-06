#include <stdexcept>

#include "optimizer/optimizer_function_pass.hpp"

using namespace ast;
using namespace optimizer;

FunctionPass::FunctionPass(const PassesDict::PassesAggregation &desc): functionRootPasses{desc} {}

void FunctionPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

std::shared_ptr<PassStatistic> FunctionPass::statistic() {

    return collected_statistic;

}

void FunctionPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    if (node->type != NodeType::ProgramRoot) {
        throw std::logic_error("ERROR: exepted ProgrammRoot node in FunctionPass");
    }

    for (auto &function : node->children) {
        if (function->type == NodeType::FunctionDefinition &&
            functionRootPasses.find(NodeType::FunctionDefinition) != functionRootPasses.end()) {
            auto function_attributes = function->children.begin();
            std::advance(function_attributes, 3); // BranchRoot
            for (auto &pass: functionRootPasses[NodeType::FunctionDefinition]) {
                pass->procces(*function_attributes, ctx);
            }
        }
    }
}
