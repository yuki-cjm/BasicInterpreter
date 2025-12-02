#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

// TODO: Imply interfaces declared in the Statement.hpp.

void RemStatement::execute(VarState &state, Program& program) const{}

void LetStatement::execute(VarState &state, Program& program) const{
    state.setValue(variable_name, exp->evaluate(program.get_vars()));
}

void PrintStatement::execute(VarState &state, Program& program) const{
    std::cout << exp->evaluate(program.get_vars()) << '\n';
}

void InputStatement::execute(VarState &state, Program& program) const{
    std::string s;
    while(1)
    {
        std::cout << " ? ";
        std::getline(std::cin, s);
        std::istringstream iss(s);
        int value;
        iss >> value;
        if(iss.eof() && !iss.fail())
        {
            state.setValue(variable_name, value);
            break;
        }
        else
            std::cout << "INVALID NUMBER\n";
    }
}

void EndStatement::execute(VarState &state, Program& program) const{
    program.programEnd();
}

void GotoStatement::execute(VarState &state, Program& program) const{
    program.changePC(Linenumber);
}

void IfStatement::execute(VarState &state, Program& program) const{
    int leftvalue = leftexp->evaluate(program.get_vars());
    int rightvalue = rightexp->evaluate(program.get_vars());
    switch(op)
    {
        case '<': if(leftvalue < rightvalue) program.changePC(Linenumber); break;
        case '=': if(leftvalue == rightvalue) program.changePC(Linenumber); break;
        case '>': if(leftvalue > rightvalue) program.changePC(Linenumber); break;
    }
}

void IndentStatement::execute(VarState &state, Program& program) const{
    program.indent();
}

void DedentStatement::execute(VarState &state, Program& program) const{
    program.dedent();
}