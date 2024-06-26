// main.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cassert>
#include "token.hpp"
#include "tokenize.hpp"
#include "parser.hpp"
#include "graph_viz.hpp"
#include "validate.hpp"
#include "execute.hpp"

int main() {
    
    // ints and floats must both be 32 bits for this program to work
    assert(sizeof(float) == 4);
    assert(sizeof(int) == 4);
    assert(sizeof(char) == 1);
    
    // get input
    std::ifstream input;
    std::stringstream s;
    std::string script;
    input.open("../input.fql");
    s << input.rdbuf();
    input.close();
    script = s.str();

    // remove comments and print resultant text
    remove_comments(script);
    // print_escaped_whitespace(script);

    // tokenize and print tokens
    std::vector<token> token_stream = tokenize(script);
    //print_token_stream(token_stream);

    // parse
    Parser p(token_stream);
    std::shared_ptr<node> ast = p.parse();

    // traverse syntax trees
    //print_traversals(ast);

    // make graphviz output
    make_dotfile(ast, "../AbstractSyntaxTree.dot");
    
    // validate
    Validator v(buildTableList(TABLE_DIRECTORY));
    v.validate(ast);

    execute(ast);

    std::cout << "\nProgram has ended properly.\n";
    return 0;
}