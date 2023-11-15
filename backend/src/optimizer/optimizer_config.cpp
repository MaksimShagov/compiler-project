#include <iostream>
#include <rapidjson/document.h>

#include "optimizer/optimizer_config.hpp"
#include "optimizer/optimizer_base_pass.hpp"
#include "optimizer/optimizer_base_aggregator_pass.hpp"

using namespace ast;
using namespace std;
using namespace optimizer;
using namespace rapidjson;

OptimizerConfig::OptimizerConfig(const std::string &config_path) {
    Document document;
    std::ifstream tree_file(config_path);
    std::string tree_string;
    std::string str;
    while (std::getline(tree_file, str))
    {
        tree_string += str;
        tree_string.push_back('\n');
    }
    document.Parse(tree_string.c_str());

    // BaseAggregationPass::PassesAggregation aggregator;
    for (auto& m : document.GetObject()) {
        auto &array = document[m.name.GetString()];
        auto parentPassName = std::string(m.name.GetString());
        auto parentNodeType = getNodeTypeByName(parentPassName);
        auto pass = getPassByName(parentPassName);

        for (int i = 0; i < array.Size(); i++) {
            auto passName = std::string(array[i].GetString());
            auto nodeType = getNodeTypeByName(passName);
            if (aggregator.find(nodeType) == aggregator.end()) {
                aggregator.emplace(
                    nodeType,
                    std::vector<BasePass*>{getPassByName(passName)}
                );
            } else {
                aggregator[nodeType].push_back(getPassByName(passName));
            }
        }
        if (aggregator.find(parentNodeType) == aggregator.end()) {
                aggregator.emplace(
                    parentNodeType,
                    std::vector<BasePass*>{getPassByName(parentPassName)}
                );
            } else {
                aggregator[parentNodeType].push_back(getPassByName(parentPassName));
            }
    }
}


BasePass* OptimizerConfig::getPassByName(const std::string &passName) {
    if (passName == "FunctionPass") {
        return new FunctionPass();
    }
    else if (passName == "BranchRootPass") {
        return new BranchRootPass();
    }
    else if (passName == "VariableDefenitonPass") {
        return new VariableDefenitonPass();
    }
    else if (passName == "ExpressionPass") {
        return new ExpressionPass();
    }
    else if (passName == "BinaryOperatorPass") {
        return new BinaryOperatorPass();
    }
    else if (passName == "ConstantPropagationPass") {
        return new ConstantPropagationPass();
    }
    else if (passName == "ConstantFoldingPass") {
        return new ConstantFoldingPass();
    }
}


ast::NodeType OptimizerConfig::getNodeTypeByName(const std::string &passName) {
    if (passName == "FunctionPass") {
        return NodeType::FunctionDefinition;
    }
    else if (passName == "BranchRootPass") {
        return NodeType::BranchRoot;
    }
    else if (passName == "ExpressionPass") {
        return NodeType::Expression;
    }
    else if (passName == "VariableDefenitonPass") {
        return NodeType::VariableDeclaration;
    }
    else if (passName == "BinaryOperatorPass") {
        return NodeType::BinaryOperation;
    } 
    else if (passName == "ConstantPropagationPass") {
        return NodeType::BinaryOperation;
    }
    else if (passName == "ConstantFoldingPass") {
        return NodeType::BinaryOperation;
    }
}


bool OptimizerConfig::isAggregatablePass(const std::string &passName) {
    if (passName == "FunctionPass" ||
        passName == "BranchRootPass" ||
        passName == "VariableDefenitonPass" ||
        passName == "BinaryOperatorPass" ||
        passName == "ExpressionPass"
    ) {
        return true;
    }
    return false;
}


BasePass* OptimizerConfig::getPasses() {

    return aggregator[NodeType::FunctionDefinition].front();
}
