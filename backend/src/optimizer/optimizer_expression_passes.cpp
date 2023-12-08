#include <stdexcept>

#include "optimizer/optimizer_utils.hpp"
#include "optimizer/optimizer_expression_passes.hpp"

using namespace ast;
using namespace optimizer;

bool ExpressionPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    bool self_optimized = false;

    for (auto child = node->children.begin(); child != node->children.end(); child++) {
        NodeType type = nodeTypeIterator(child);
        
        bool optimized = true;
        while (optimized) {
            optimized = false;
            for (auto &pass : passesAggregator[type]) {
                optimized = optimized || pass->procces(*child, ctx);
            }
            if (!self_optimized && optimized) {
                self_optimized = true;
            }
        }
    }
    return self_optimized;
}

std::shared_ptr<PassStatistic> ExpressionPass::statistic() {
    return collectedStatistic;
}

bool BinaryOperatorPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    NodeType type = node->type;
    bool self_optimized = false;
    bool optimized = true;
    while (optimized) {
        optimized = false;
        for (auto &pass : passesAggregator[type]) {
            optimized = optimized || pass->procces(node, ctx);
        }
        if (!self_optimized && optimized) {
            self_optimized = true;
        }
    }

    for (auto child = node->children.begin(); child != node->children.end(); child++) {
        NodeType type = nodeTypeIterator(child);
        bool optimized = true;
        while (optimized) {
            optimized = false;
            if (type == NodeType::BinaryOperation) {
                optimized = optimized || procces(*child, ctx);
            }
            for (auto &pass : passesAggregator[type]) {
                optimized = optimized || pass->procces(*child, ctx);
            }
            if (!self_optimized && optimized) {
                self_optimized = true;
            }
        }
    }
    return self_optimized;
}

std::shared_ptr<PassStatistic> BinaryOperatorPass::statistic() {
    return collectedStatistic;
}

bool VariableDefenitonPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    bool self_optimized = false;
    auto variable_attr = node->children.begin();
    auto variable_type_id = (*variable_attr)->typeId();
    variable_attr++; // skip variable type_name
    auto variable_name = (*variable_attr)->str(); 
    variable_attr++;

    if (variable_attr != node->children.end()) {
        NodeType type = nodeTypeIterator(variable_attr);
        bool optimized = true;
        while (optimized) {
            optimized = false;
            for (auto &pass : passesAggregator[type]) {
                optimized = optimized || pass->procces(*variable_attr, ctx);
            }
            if (!self_optimized && optimized) {
                self_optimized = true;
            }
        }

        auto calculated_value = (*variable_attr)->children.front(); // rename
        if (isLiteral(calculated_value)) {
            if (variable_type_id == BuiltInTypes::IntType)
                ctx.values.front()[variable_name] = calculated_value->intNum();
            else if (variable_type_id == BuiltInTypes::FloatType)
                ctx.values.front()[variable_name] = calculated_value->fpNum();
            else if (variable_type_id == BuiltInTypes::BoolType)
                ctx.values.front()[variable_name] = calculated_value->boolean();
        }
    }
    return self_optimized;
}

std::shared_ptr<PassStatistic> VariableDefenitonPass::statistic() {
    return collectedStatistic;
}

bool ConstantFoldingPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    Node::Ptr first;
    Node::Ptr second;
    if (node->children.size() == 2) {
        first = node->firstChild();
        second = node->secondChild();
    } else {
        return false;
    }


    if (isLiteral(first) && isLiteral(second)) {
        if (first->type == NodeType::IntegerLiteralValue && second->type == NodeType::IntegerLiteralValue) {
            node->value = calculateOperation(first->intNum(), second->intNum(), node->binOp());
            node->type = NodeType::IntegerLiteralValue;
            node->children.clear();
            return true;
        }
        if (first->type == NodeType::FloatingPointLiteralValue && second->type == NodeType::FloatingPointLiteralValue) {
            node->value = calculateOperation(first->fpNum(), second->fpNum(), node->binOp());
            node->type = NodeType::FloatingPointLiteralValue;
            node->children.clear();
            return true;
        }
        if (first->type == NodeType::BooleanLiteralValue && second->type == NodeType::BooleanLiteralValue) {
            node->value = calculateOperation(first->boolean(), second->boolean(), node->binOp());
            node->type = NodeType::BooleanLiteralValue;
            node->children.clear();
            return true;
        }
    }
    return false;
}

std::shared_ptr<PassStatistic> ConstantFoldingPass::statistic() {
    return collectedStatistic;
}

bool ConstantPropagationPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    bool optimized = false;
    if (node->type == NodeType::BinaryOperation) {
        auto first = node->firstChild();
        auto second = node->secondChild();
        if (first->type == NodeType::VariableName) {
            optimized = optimized || propagate(first, ctx);
        }
        if (second->type == NodeType::VariableName) {
            optimized = optimized || propagate(second, ctx);
        }
    }
    return optimized;
}

bool ConstantPropagationPass::propagate(ast::Node::Ptr &node, OptimizerContext &ctx) {
    const std::string &varName = node->str();
    if (!ctx.hasVariable(varName))
        return false;
    auto variableIter = ctx.findVariableValue(varName);
    auto variableType = ctx.findVariable(node).type;
    if (variableType == BuiltInTypes::FloatType) {
        node->type = NodeType::FloatingPointLiteralValue;
        node->value = std::get<double>(variableIter);
        return true;
    } else if (variableType == BuiltInTypes::IntType) {
        node->type = NodeType::IntegerLiteralValue;
        node->value = std::get<long int>(variableIter);
        return true;
    } else if (variableType ==  BuiltInTypes::BoolType) {
        node->type = NodeType::BooleanLiteralValue;
        node->value = std::get<bool>(variableIter);
        return true;
    }
    return false;
}

std::shared_ptr<PassStatistic> ConstantPropagationPass::statistic() {
    return collectedStatistic;
}

bool TypeConversionPass::compute(ast::Node::Ptr &node, OptimizerContext &ctx) {
    bool optimized = false;
    if (node->type == NodeType::BinaryOperation) {
        auto first = node->firstChild();
        auto second = node->secondChild();
        if (first->type == NodeType::TypeConversion) {
            optimized = optimized || conversion(first, ctx);
        }
        if (second->type == NodeType::TypeConversion) {
            optimized = optimized || conversion(second, ctx);
        }
    }
    return optimized;
}

bool TypeConversionPass::conversion(ast::Node::Ptr &node, OptimizerContext &ctx) {
    Node::Ptr &operand = node->lastChild();
    if (isNumericLiteral(operand)) {
        if (node->firstChild()->typeId() == BuiltInTypes::FloatType) {
            node->type = NodeType::FloatingPointLiteralValue;
            node->value = static_cast<double>(operand->intNum());
        } else {
            node->type = NodeType::IntegerLiteralValue;
            node->value = static_cast<long int>(operand->fpNum());
        }
        node->children.clear();
        return true;
    } else if (isNonModifiedVariable(operand, ctx)) { // this logic may placed in PropagationPass?
        const std::string &varName = operand->str();
        if (node->firstChild()->typeId() == BuiltInTypes::FloatType) {
            node->type = NodeType::FloatingPointLiteralValue;
            node->value = static_cast<double>(std::get<long int>(ctx.findVariableValue(varName)));
        } else {
            node->type = NodeType::IntegerLiteralValue;
            node->value = static_cast<long int>(std::get<double>(ctx.findVariableValue(varName)));
        }
        node->children.clear();
        return true;
    }
    return false;
}

std::shared_ptr<PassStatistic> TypeConversionPass::statistic() {
    return collectedStatistic;
}
