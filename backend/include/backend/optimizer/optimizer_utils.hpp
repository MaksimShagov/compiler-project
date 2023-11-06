#pragma once

#include "optimizer/optimizer.hpp"
#include "optimizer/optimizer_context.hpp"

namespace optimizer {

    bool isLiteral(const ast::Node::Ptr &node) {
        switch (node->type) {
        case ast::NodeType::IntegerLiteralValue:
        case ast::NodeType::FloatingPointLiteralValue:
        case ast::NodeType::StringLiteralValue:
        case ast::NodeType::BooleanLiteralValue:
            return true;
        }
        return false;
    }

    bool isAssignment(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::BinaryOperation && node->binOp() == ast::BinaryOperation::Assign;
    }

    bool isZeroIntLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::IntegerLiteralValue && node->intNum() == 0;
    }

    bool isNonZeroIntLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::IntegerLiteralValue && node->intNum() != 0;
    }

    bool isZeroFloatLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::FloatingPointLiteralValue && node->fpNum() == 0.0;
    }

    bool isNonZeroFloatLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::FloatingPointLiteralValue && node->fpNum() != 0.0;
    }

    bool isTrueLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::BooleanLiteralValue && node->boolean();
    }

    bool isFalseLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::BooleanLiteralValue && !node->boolean();
    }

    bool isTruthyLiteral(const ast::Node::Ptr &node) {
        return isNonZeroIntLiteral(node) || isNonZeroFloatLiteral(node) || isTrueLiteral(node);
    }

    bool isFalsyLiteral(const ast::Node::Ptr &node) {
        return isZeroIntLiteral(node) || isZeroFloatLiteral(node) || isFalseLiteral(node);
    }

    bool isNumericLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::IntegerLiteralValue || node->type == ast::NodeType::FloatingPointLiteralValue;
    }

    bool isBooleanLiteral(const ast::Node::Ptr &node) {
        return node->type == ast::NodeType::BooleanLiteralValue;
    }

    bool isConstantLiteral(const ast::Node::Ptr &node) {
        return isBooleanLiteral(node) || isNumericLiteral(node);
    }

    bool isModifiedVariable(const ast::Node::Ptr &node, OptimizerContext &ctx) {
        return node->type == ast::NodeType::VariableName && ctx.findVariable(node).attributes.modified;
    }

    bool isNonModifiedVariable(const ast::Node::Ptr &node, OptimizerContext &ctx) {
        return node->type == ast::NodeType::VariableName && !ctx.findVariable(node).attributes.modified &&
            node->parent->type != ast::NodeType::VariableDeclaration;
    }

    bool isVariableWithType(const ast::Node::Ptr &node, ast::TypeId typeId, OptimizerContext &ctx) {
        return node->type == ast::NodeType::VariableName && ctx.findVariable(node).type == typeId;
    }

    bool canBeConstantInt(const ast::Node::Ptr &node, OptimizerContext &ctx) {
        return node->type == ast::NodeType::IntegerLiteralValue || isVariableWithType(node, ast::BuiltInTypes::IntType, ctx);
    }

    bool canBeConstantFloat(const ast::Node::Ptr &node, OptimizerContext &ctx) {
        return node->type == ast::NodeType::FloatingPointLiteralValue || isVariableWithType(node, ast::BuiltInTypes::FloatType, ctx);
    }

    bool canBeConstantBool(const ast::Node::Ptr &node, OptimizerContext &ctx) {
        return node->type == ast::NodeType::BooleanLiteralValue || isVariableWithType(node, ast::BuiltInTypes::BoolType, ctx);
    }

    ast::NodeType nodeTypeIterator(const std::list<ast::Node::Ptr>::iterator &iter) {
        return iter->get()->type;
    }

} // namespace