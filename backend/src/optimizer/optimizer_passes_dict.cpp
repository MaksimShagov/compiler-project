
#include "optimizer/optimizer_passes_dict.hpp"

using namespace ast;
using namespace optimizer;

void PassesDict::addPass(const PassesDict::PassDescription &desc) {

    if (passesDict.find(desc.first) == passesDict.end())
    {
        passesDict.emplace(
            desc.first,
            std::vector<BasePass*>{desc.second}
        );

    } else {
        passesDict[desc.first].push_back(desc.second);
    }

}
