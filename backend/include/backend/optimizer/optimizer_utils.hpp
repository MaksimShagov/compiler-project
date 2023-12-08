#pragma once

#include <ast/syntax_tree.hpp>
#include <ast/types.hpp>
#include "optimizer/optimizer_context.hpp"

namespace optimizer {

    bool isLiteral(const ast::Node::Ptr &node);

    bool isAssignment(const ast::Node::Ptr &node);

    bool isZeroIntLiteral(const ast::Node::Ptr &node);

    bool isNonZeroIntLiteral(const ast::Node::Ptr &node);

    bool isZeroFloatLiteral(const ast::Node::Ptr &node);

    bool isNonZeroFloatLiteral(const ast::Node::Ptr &node);

    bool isTrueLiteral(const ast::Node::Ptr &node);

    bool isFalseLiteral(const ast::Node::Ptr &node);

    bool isTruthyLiteral(const ast::Node::Ptr &node);

    bool isFalsyLiteral(const ast::Node::Ptr &node);

    bool isNumericLiteral(const ast::Node::Ptr &node);

    bool isBooleanLiteral(const ast::Node::Ptr &node);

    bool isConstantLiteral(const ast::Node::Ptr &node);

    bool isModifiedVariable(const ast::Node::Ptr &node, OptimizerContext &ctx);

    bool isNonModifiedVariable(const ast::Node::Ptr &node, OptimizerContext &ctx);

    bool isVariableWithType(const ast::Node::Ptr &node, ast::TypeId typeId, OptimizerContext &ctx);

    bool canBeConstantInt(const ast::Node::Ptr &node, OptimizerContext &ctx);

    bool canBeConstantFloat(const ast::Node::Ptr &node, OptimizerContext &ctx);

    bool canBeConstantBool(const ast::Node::Ptr &node, OptimizerContext &ctx);

    ast::NodeType nodeTypeIterator(const std::list<ast::Node::Ptr>::iterator &iter);
} // namespace
