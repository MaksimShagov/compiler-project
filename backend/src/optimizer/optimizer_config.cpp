#include <iostream>
#include <memory>
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

    for (auto& m : document.GetObject()) {
        auto &array = document[m.name.GetString()];
        auto parentPassName = std::string(m.name.GetString());
        auto parentNodeType = getNodeTypeByName(parentPassName);
        auto pass = std::static_pointer_cast<BaseAggregationPass>(getPassByName(parentPassName));

        for (int i = 0; i < array.Size(); i++) {
            auto passName = std::string(array[i].GetString());
            auto nodeType = getNodeTypeByName(passName);
            auto proccesed_pass = aggregator.find(passName);
            if (aggregator.find(passName) != aggregator.end()) {
                pass->addPass({
                    nodeType, 
                    std::static_pointer_cast<BaseAggregationPass>(proccesed_pass->second)
                });
            } else {
                pass->addPass({nodeType, getPassByName(passName)});
            }
        }
        aggregator.emplace(parentPassName, pass);
    }
    finalPass = aggregator["FunctionPass"];
}


BasePassPtr OptimizerConfig::getPassByName(const std::string &passName) {
    if (passName == "FunctionPass") {
        return std::make_shared<FunctionPass>();
    }
    else if (passName == "BranchRootPass") {
        return std::make_shared<BranchRootPass>();
    }
    else if (passName == "VariableDefenitonPass") {
        return std::make_shared<VariableDefenitonPass>();
    }
    else if (passName == "ExpressionPass") {
        return std::make_shared<ExpressionPass>();
    }
    else if (passName == "BinaryOperatorPass") {
        return std::make_shared<BinaryOperatorPass>();
    }
    else if (passName == "ConstantPropagationPass") {
        return std::make_shared<ConstantPropagationPass>();
    }
    else if (passName == "ConstantFoldingPass") {
        return std::make_shared<ConstantFoldingPass>();
    }
    else if (passName == "TypeConversionPass") {
        return std::make_shared<TypeConversionPass>();
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
    else if (passName == "TypeConversionPass") {
        return NodeType::BinaryOperation;
    }
}


BasePassPtr OptimizerConfig::getPasses() {

    return finalPass;
}
