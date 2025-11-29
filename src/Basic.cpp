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
  Program program;
  Parser parser(program.get_vars());

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      // TODO: The main function.
        TokenStream tokenstream = lexer.tokenize(line);
        const Token *token = tokenstream.peek();
        switch(token->type)
        {
            case TokenType::RUN : program.run();break;
            case TokenType::LIST : program.list();break;
            case TokenType::CLEAR : program.clear();break;
            case TokenType::QUIT : exit(0);break;
            case TokenType::HELP : 
            default:
                ParsedLine parsedline = parser.parseLine(tokenstream, line);
                if(parsedline.getLine().has_value())
                    program.addStmt(parsedline.getLine().value(), parsedline.getStatement());
                else
                    program.execute(parsedline.getStatement());
                std::cout << "!@#!@#!@\n";
        }
        std::cout << "why?\n";
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
    std::cout << "why\n";
  }
  return 0;
}