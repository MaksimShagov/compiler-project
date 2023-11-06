#pragma once

#include <memory>
#include <map>
#include <ast/syntax_tree.hpp>

#include "backend/optimizer/optimizer_base_pass.hpp"

namespace optimizer {

    class PassesDict
    {
    public:
        using PassDescription = std::pair<ast::NodeType, BasePass*>;
        using PassesAggregation = std::map<ast::NodeType, std::vector<BasePass*>>;

        PassesDict() = default;
        ~PassesDict() = default;

        void addPass(const PassDescription& desc);

        std::map<ast::NodeType, std::vector<BasePass*>> passesDict;
    };

} // namespace optimizer
