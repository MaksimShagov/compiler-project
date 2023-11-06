#include <stdexcept>

#include "optimizer/optimizer_utils.hpp"
#include "optimizer/optimizer_expression_passes.hpp"

using namespace ast;
using namespace optimizer;

ExpressionPass::ExpressionPass(
    PassesDict::PassesAggregation &desc
): expressionPasses(desc) {}

void ExpressionPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

void ExpressionPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    for (auto child = node->children.begin(); child != node->children.end(); child++) {
        NodeType type = nodeTypeIterator(child);

        for (auto &pass : branchRootPasses[type]) {
            pass->procces(*child, ctx);
        }

    }
}

BinaryOperatorPass::BinaryOperatorPass(
    PassesDict::PassesAggregation &desc
): expressionPasses(desc) {}

void BinaryOperatorPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

void BinaryOperatorPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    for (auto child = node->children.begin(); child != node->children.end(); child++) {
        NodeType type = nodeTypeIterator(child);

        for (auto &pass : branchRootPasses[type]) {
            pass->procces(*child, ctx);
        }

    }
}

