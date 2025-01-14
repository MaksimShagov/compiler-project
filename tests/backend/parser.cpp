#include <gtest/gtest.h>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "stringvec.hpp"

using namespace ast;
using namespace lexer;
using namespace parser;

TEST(Parser, can_parse_if_statement) {
    StringVec source = {
        "def main() -> None:", "    x: int = 1 ", "    if x == 2:", "        x = 3", "    else:", "        x = 1",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      VariableDeclaration\n"
                           "        TypeName: IntType\n"
                           "        VariableName: x\n"
                           "        Expression\n"
                           "          IntegerLiteralValue: 1\n"
                           "      IfStatement\n"
                           "        Expression\n"
                           "          BinaryOperation: Equal\n"
                           "            VariableName: x\n"
                           "            IntegerLiteralValue: 2\n"
                           "        BranchRoot\n"
                           "          Expression\n"
                           "            BinaryOperation: Assign\n"
                           "              VariableName: x\n"
                           "              IntegerLiteralValue: 3\n"
                           "        ElseStatement\n"
                           "          BranchRoot\n"
                           "            Expression\n"
                           "              BinaryOperation: Assign\n"
                           "                VariableName: x\n"
                           "                IntegerLiteralValue: 1\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_if_elif_statement) {
    StringVec source = {
        "def main() -> None:", "    x: int = 1 ",  "    if x == 2:",
        "        x = 3",       "    elif x == 3:", "        x = 2",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      VariableDeclaration\n"
                           "        TypeName: IntType\n"
                           "        VariableName: x\n"
                           "        Expression\n"
                           "          IntegerLiteralValue: 1\n"
                           "      IfStatement\n"
                           "        Expression\n"
                           "          BinaryOperation: Equal\n"
                           "            VariableName: x\n"
                           "            IntegerLiteralValue: 2\n"
                           "        BranchRoot\n"
                           "          Expression\n"
                           "            BinaryOperation: Assign\n"
                           "              VariableName: x\n"
                           "              IntegerLiteralValue: 3\n"
                           "        ElifStatement\n"
                           "          Expression\n"
                           "            BinaryOperation: Equal\n"
                           "              VariableName: x\n"
                           "              IntegerLiteralValue: 3\n"
                           "          BranchRoot\n"
                           "            Expression\n"
                           "              BinaryOperation: Assign\n"
                           "                VariableName: x\n"
                           "                IntegerLiteralValue: 2\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_while_statement) {
    StringVec source = {
        "def main() -> None:",
        "    x: int = 1 ",
        "    while x == 2:",
        "        x = 3",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      VariableDeclaration\n"
                           "        TypeName: IntType\n"
                           "        VariableName: x\n"
                           "        Expression\n"
                           "          IntegerLiteralValue: 1\n"
                           "      WhileStatement\n"
                           "        Expression\n"
                           "          BinaryOperation: Equal\n"
                           "            VariableName: x\n"
                           "            IntegerLiteralValue: 2\n"
                           "        BranchRoot\n"
                           "          Expression\n"
                           "            BinaryOperation: Assign\n"
                           "              VariableName: x\n"
                           "              IntegerLiteralValue: 3\n";

    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_long_expression) {
    StringVec source = {
        "def main() -> None:",
        "    x = (y + z + 5 * 2) / 2",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      Expression\n"
                           "        BinaryOperation: Assign\n"
                           "          VariableName: x\n"
                           "          BinaryOperation: Div\n"
                           "            BinaryOperation: Add\n"
                           "              BinaryOperation: Add\n"
                           "                VariableName: y\n"
                           "                VariableName: z\n"
                           "              BinaryOperation: Mult\n"
                           "                IntegerLiteralValue: 5\n"
                           "                IntegerLiteralValue: 2\n"
                           "            IntegerLiteralValue: 2\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_nested_if_statement) {
    StringVec source = {
        "def main() -> None:",
        "    if x == 2:",
        "        if x > 1:",
        "            x = 3",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      IfStatement\n"
                           "        Expression\n"
                           "          BinaryOperation: Equal\n"
                           "            VariableName: x\n"
                           "            IntegerLiteralValue: 2\n"
                           "        BranchRoot\n"
                           "          IfStatement\n"
                           "            Expression\n"
                           "              BinaryOperation: Greater\n"
                           "                VariableName: x\n"
                           "                IntegerLiteralValue: 1\n"
                           "            BranchRoot\n"
                           "              Expression\n"
                           "                BinaryOperation: Assign\n"
                           "                  VariableName: x\n"
                           "                  IntegerLiteralValue: 3\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_function_call) {
    StringVec source = {
        "def main() -> None:",
        "    function(x, y + 1, z + x)",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      Expression\n"
                           "        FunctionCall\n"
                           "          FunctionName: function\n"
                           "          FunctionArguments\n"
                           "            Expression\n"
                           "              VariableName: x\n"
                           "            Expression\n"
                           "              BinaryOperation: Add\n"
                           "                VariableName: y\n"
                           "                IntegerLiteralValue: 1\n"
                           "            Expression\n"
                           "              BinaryOperation: Add\n"
                           "                VariableName: z\n"
                           "                VariableName: x\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_function_definition_with_parameters) {
    StringVec source = {
        "def foo(x: int, y: float, z: bool) -> None:",
        "    return",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: foo\n"
                           "    FunctionArguments\n"
                           "      FunctionArgument\n"
                           "        TypeName: IntType\n"
                           "        VariableName: x\n"
                           "      FunctionArgument\n"
                           "        TypeName: FloatType\n"
                           "        VariableName: y\n"
                           "      FunctionArgument\n"
                           "        TypeName: BoolType\n"
                           "        VariableName: z\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      ReturnStatement\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_function_with_return) {
    StringVec source = {
        "def main() -> float:",
        "    return 1 / x",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: FloatType\n"
                           "    BranchRoot\n"
                           "      ReturnStatement\n"
                           "        Expression\n"
                           "          BinaryOperation: Div\n"
                           "            IntegerLiteralValue: 1\n"
                           "            VariableName: x\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_multiple_functions) {
    StringVec source = {
        "def func1() -> None:",  "    x: int",     "    return",
        "def func2() -> int:",   "    y: int = 1", "    return y",
        "def func3() -> float:", "    return 2.3", "    z: int",
        "def func4() -> None:",  "    x: float",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: func1\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      VariableDeclaration\n"
                           "        TypeName: IntType\n"
                           "        VariableName: x\n"
                           "      ReturnStatement\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: func2\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: IntType\n"
                           "    BranchRoot\n"
                           "      VariableDeclaration\n"
                           "        TypeName: IntType\n"
                           "        VariableName: y\n"
                           "        Expression\n"
                           "          IntegerLiteralValue: 1\n"
                           "      ReturnStatement\n"
                           "        Expression\n"
                           "          VariableName: y\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: func3\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: FloatType\n"
                           "    BranchRoot\n"
                           "      ReturnStatement\n"
                           "        Expression\n"
                           "          FloatingPointLiteralValue: 2.3\n"
                           "      VariableDeclaration\n"
                           "        TypeName: IntType\n"
                           "        VariableName: z\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: func4\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      VariableDeclaration\n"
                           "        TypeName: FloatType\n"
                           "        VariableName: x\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_nested_function_call_alone) {
    StringVec source = {
        "def main() -> None:",
        "    x = foo(bar())",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      Expression\n"
                           "        BinaryOperation: Assign\n"
                           "          VariableName: x\n"
                           "          FunctionCall\n"
                           "            FunctionName: foo\n"
                           "            FunctionArguments\n"
                           "              Expression\n"
                           "                FunctionCall\n"
                           "                  FunctionName: bar\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_nested_function_call_inside_expression) {
    StringVec source = {
        "def main() -> None:",
        "    x = foo(1 + bar())",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      Expression\n"
                           "        BinaryOperation: Assign\n"
                           "          VariableName: x\n"
                           "          FunctionCall\n"
                           "            FunctionName: foo\n"
                           "            FunctionArguments\n"
                           "              Expression\n"
                           "                BinaryOperation: Add\n"
                           "                  IntegerLiteralValue: 1\n"
                           "                  FunctionCall\n"
                           "                    FunctionName: bar\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_multiple_nested_function_calls) {
    StringVec source = {
        "def main() -> None:",
        "    x = foo(bar(), 1 + baz())",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      Expression\n"
                           "        BinaryOperation: Assign\n"
                           "          VariableName: x\n"
                           "          FunctionCall\n"
                           "            FunctionName: foo\n"
                           "            FunctionArguments\n"
                           "              Expression\n"
                           "                FunctionCall\n"
                           "                  FunctionName: bar\n"
                           "              Expression\n"
                           "                BinaryOperation: Add\n"
                           "                  IntegerLiteralValue: 1\n"
                           "                  FunctionCall\n"
                           "                    FunctionName: baz\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_nested_function_call_with_arguments) {
    StringVec source = {
        "def main() -> None:",
        "    x = foo(bar(y))",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      Expression\n"
                           "        BinaryOperation: Assign\n"
                           "          VariableName: x\n"
                           "          FunctionCall\n"
                           "            FunctionName: foo\n"
                           "            FunctionArguments\n"
                           "              Expression\n"
                           "                FunctionCall\n"
                           "                  FunctionName: bar\n"
                           "                  FunctionArguments\n"
                           "                    Expression\n"
                           "                      VariableName: y\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, can_parse_complex_nested_function_call) {
    StringVec source = {
        "def main() -> None:",
        "    x = foo(bar(fun()) + 1, baz(y), z)",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string tree_str = "ProgramRoot\n"
                           "  FunctionDefinition\n"
                           "    FunctionName: main\n"
                           "    FunctionArguments\n"
                           "    FunctionReturnType: NoneType\n"
                           "    BranchRoot\n"
                           "      Expression\n"
                           "        BinaryOperation: Assign\n"
                           "          VariableName: x\n"
                           "          FunctionCall\n"
                           "            FunctionName: foo\n"
                           "            FunctionArguments\n"
                           "              Expression\n"
                           "                BinaryOperation: Add\n"
                           "                  FunctionCall\n"
                           "                    FunctionName: bar\n"
                           "                    FunctionArguments\n"
                           "                      Expression\n"
                           "                        FunctionCall\n"
                           "                          FunctionName: fun\n"
                           "                  IntegerLiteralValue: 1\n"
                           "              Expression\n"
                           "                FunctionCall\n"
                           "                  FunctionName: baz\n"
                           "                  FunctionArguments\n"
                           "                    Expression\n"
                           "                      VariableName: y\n"
                           "              Expression\n"
                           "                VariableName: z\n";
    ASSERT_EQ(tree_str, tree.dump());
}

TEST(Parser, parse_boolean_variable_declaration) {
    StringVec source = {
        "def main() -> None:",
        "    x: bool = True",
        "    y: bool = False",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string syntax_tree =
    "ProgramRoot\n"
    "  FunctionDefinition\n"
    "    FunctionName: main\n"
    "    FunctionArguments\n"
    "    FunctionReturnType: NoneType\n"
    "    BranchRoot\n"
    "      VariableDeclaration\n"
    "        TypeName: BoolType\n"
    "        VariableName: x\n"
    "        Expression\n"
    "          BooleanLiteralValue: True\n"
    "      VariableDeclaration\n"
    "        TypeName: BoolType\n"
    "        VariableName: y\n"
    "        Expression\n"
    "          BooleanLiteralValue: False\n";
    ASSERT_EQ(syntax_tree, tree.dump());
}

TEST(Parser, parse_boolean_expression) {
    StringVec source = {
        "def main() -> None:",
        "    x: bool = True",
        "    y: bool = False",
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string syntax_tree =
    "ProgramRoot\n"
    "  FunctionDefinition\n"
    "    FunctionName: main\n"
    "    FunctionArguments\n"
    "    FunctionReturnType: NoneType\n"
    "    BranchRoot\n"
    "      VariableDeclaration\n"
    "        TypeName: BoolType\n"
    "        VariableName: x\n"
    "        Expression\n"
    "          BooleanLiteralValue: True\n"
    "      VariableDeclaration\n"
    "        TypeName: BoolType\n"
    "        VariableName: y\n"
    "        Expression\n"
    "          BooleanLiteralValue: False\n";
    ASSERT_EQ(syntax_tree, tree.dump());
}

TEST(Parser, parse_boolean_if_statment) {
    StringVec source = {
        "def main() -> None:",
        "    x: bool = True",
        "    y: bool = False",
        "    if x == True:",
        "        y = True"
    };
    TokenList token_list = Lexer::process(source);
    SyntaxTree tree = Parser::process(token_list);
    std::string syntax_tree =
    "ProgramRoot\n"
    "  FunctionDefinition\n"
    "    FunctionName: main\n"
    "    FunctionArguments\n"
    "    FunctionReturnType: NoneType\n"
    "    BranchRoot\n"
    "      VariableDeclaration\n"
    "        TypeName: BoolType\n"
    "        VariableName: x\n"
    "        Expression\n"
    "          BooleanLiteralValue: True\n"
    "      VariableDeclaration\n"
    "        TypeName: BoolType\n"
    "        VariableName: y\n"
    "        Expression\n"
    "          BooleanLiteralValue: False\n"
    "      IfStatement\n"
    "        Expression\n"
    "          BinaryOperation: Equal\n"
    "            VariableName: x\n"
    "            BooleanLiteralValue: True\n"
    "        BranchRoot\n"
    "          Expression\n"
    "            BinaryOperation: Assign\n"
    "              VariableName: y\n"
    "              BooleanLiteralValue: True\n";
    ASSERT_EQ(syntax_tree, tree.dump());
}
