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
    state.setValue(variable_name, value);
}

void PrintStatement::execute(VarState &state, Program& program) const{
    std::cout << result << '\n';
}

void InputStatement::execute(VarState &state, Program& program) const{
    int value;
    std::cin >> value;
    state.setValue(variable_name, value);
}

void EndStatement::execute(VarState &state, Program& program) const{
    program.programEnd();
}

void GotoStatement::execute(VarState &state, Program& program) const{
    program.changePC(Linenumber);
}

void IfStatement::execute(VarState &state, Program& program) const{
    switch(op)
    {
        case '<': if(leftvalue < rightvalue) program.changePC(Linenumber); break;
        case '=': if(leftvalue == rightvalue) program.changePC(Linenumber); break;
        case '>': if(leftvalue > rightvalue) program.changePC(Linenumber); break;
    }
}

