#include <stdexcept>

#include "optimizer/optimizer_utils.hpp"
#include "optimizer/optimizer_expression_passes.hpp"

using namespace ast;
using namespace optimizer;

void ExpressionPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

void ExpressionPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    for (auto child = node->children.begin(); child != node->children.end(); child++) {
        NodeType type = nodeTypeIterator(child);

        for (auto &pass : passesAggregator[type]) {
            pass->procces(*child, ctx);
        }

    }
}

std::shared_ptr<PassStatistic> ExpressionPass::statistic() {
    return collectedStatistic;
}


void BinaryOperatorPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

void BinaryOperatorPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    NodeType type = node->type;
    
    for (auto &pass : passesAggregator[type]) {
        pass->procces(node, ctx);
    }
    
    for (auto child = node->children.begin(); child != node->children.end(); child++) {
        NodeType type = nodeTypeIterator(child);

        for (auto &pass : passesAggregator[type]) {
            pass->procces(*child, ctx);
        }

    }
}

std::shared_ptr<PassStatistic> BinaryOperatorPass::statistic() {
    return collectedStatistic;
}


void VariableDefenitonPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

void VariableDefenitonPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    auto variable_attr = node->children.begin();
    auto variable_type_id = (*variable_attr)->typeId();
    variable_attr++; // skip variable type_name
    auto variable_name = (*variable_attr)->str(); 
    variable_attr++;

    if (variable_attr != node->children.end()) {
        NodeType type = nodeTypeIterator(variable_attr);
        for (auto &pass : passesAggregator[type]) {
            pass->procces(*variable_attr, ctx);
        }
        auto value = (*variable_attr)->children.front(); // rename
        if (isLiteral(value)) {
            if (variable_type_id == BuiltInTypes::IntType)
                ctx.values.front()[variable_name] = value->intNum();
            else if (variable_type_id == BuiltInTypes::FloatType)
                ctx.values.front()[variable_name] = value->fpNum();
            else if (variable_type_id == BuiltInTypes::BoolType)
                ctx.values.front()[variable_name] = value->boolean();
        }
    }
}

std::shared_ptr<PassStatistic> VariableDefenitonPass::statistic() {
    return collectedStatistic;
}

void ConstantFoldingPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

void ConstantFoldingPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    auto first = node->firstChild();
    auto second = node->secondChild();

    if (isLiteral(first) && isLiteral(second)) {
        if (first->type == NodeType::IntegerLiteralValue && second->type == NodeType::IntegerLiteralValue) {
            node->type = NodeType::IntegerLiteralValue;
            node->value = calculateOperation(first->intNum(), second->intNum(), node->binOp());
            node->children.clear();
        }
        if (first->type == NodeType::FloatingPointLiteralValue && second->type == NodeType::FloatingPointLiteralValue) {
            node->type = NodeType::FloatingPointLiteralValue;
            node->value = calculateOperation(first->fpNum(), second->fpNum(), node->binOp());
            node->children.clear();
        }
        if (first->type == NodeType::BooleanLiteralValue && second->type == NodeType::BooleanLiteralValue) {
            node->type = NodeType::BooleanLiteralValue;
            node->value = calculateOperation(first->boolean(), second->boolean(), node->binOp());
            node->children.clear();
        }
    }
}


std::shared_ptr<PassStatistic> ConstantFoldingPass::statistic() {
    return collectedStatistic;
}

void ConstantPropagationPass::procces(ast::Node::Ptr &node, OptimizerContext &ctx) {

    this->compute(node, ctx);

    // statistic calculaton logic
}

void ConstantPropagationPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    if (node->type == NodeType::VariableName) {
        const std::string &varName = node->str();
        if (!ctx.hasVariable(varName))
            return;
        auto variableIter = ctx.findVariableValue(varName);
        auto variableType = ctx.findVariable(node).type;
        if (variableType == BuiltInTypes::FloatType) {
            node->type = NodeType::FloatingPointLiteralValue;
            node->value = std::get<double>(variableIter);
        } else if (variableType == BuiltInTypes::IntType) {
            node->type = NodeType::IntegerLiteralValue;
            node->value = std::get<long int>(variableIter);
        } else if (variableType ==  BuiltInTypes::BoolType) {
            node->type = NodeType::BooleanLiteralValue;
            node->value = std::get<bool>(variableIter);
        }
    }

}

std::shared_ptr<PassStatistic> ConstantPropagationPass::statistic() {
    return collectedStatistic;
}

