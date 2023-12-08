#pragma once
#include <memory>
#include <fstream>
#include <string>

#include <ast/node.hpp>

#include "backend/optimizer/optimizer_context.hpp"
#include "backend/optimizer/optimizer_base_pass.hpp"
#include "backend/optimizer/optimizer_branch_root_pass.hpp"
#include "backend/optimizer/optimizer_function_pass.hpp"
#include "backend/optimizer/optimizer_expression_passes.hpp"
#include "optimizer/optimizer_base_aggregator_pass.hpp"


namespace optimizer {

    class OptimizerConfig {
        BasePassPtr finalPass;
        std::map<std::string, BaseAggregationPassPtr> aggregator;
    public:
        OptimizerConfig(const std::string &config_path);

        BasePassPtr getPasses();

    private:
        BasePassPtr getPassByName(const std::string &passName);
        ast::NodeType getNodeTypeByName(const std::string &passName);
        bool isAggregatablePass(const std::string &passName);
    };

} // namespace optimizer