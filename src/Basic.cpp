#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      // TODO: The main function.
        TokenStream tokenstream = lexer.tokenize(line);
        ParsedLine parsedline = parser.parseline(tokenstream, line);
        if(parsedline.getline())
            program.addStmt(parsedline.getline(), parsedline.getStatement());
        else
            parsedline.getStatement()->execute();
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}