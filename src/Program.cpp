// TODO: Imply interfaces declared in the Program.hpp.
#include "Program.hpp"

#include "Statement.hpp"
#include "Recorder.hpp"
#include "VarState.hpp"

Program::Program() = default;

void Program::addStmt(int line, Statement* stmt){
    recorder_.add(line, stmt);
}

void Program::removeStmt(int line){
    recorder_.remove(line);
}

void Program::run(){
    programCounter_ = 0;
    programEnd_ = false;
    programCounter_ = recorder_.nextLines(programCounter_);
    while(programCounter_ != -1){
        execute(recorder_[programCounter_]->second);
        if(programEnd_)
            break;
        programCounter_ = recorder_.nextLines(programCounter_);
    }
}

void Program::list() const{
    recorder_.printLines();
}

void Program::clear(){
    recorder_.clear();
    vars_.clear();
}

void Program::execute(Statement* stmt){
    stmt->execute(vars_, *this);
}

int Program::getPC() const noexcept{
    return programCounter_;
}

void Program::changePC(int line){
    programCounter_ = line;
}

void Program::programEnd(){
    programEnd_ = true;
}

VarState* Program::get_vars(){
    return &vars_;
}

void Program::resetAfterRun() noexcept{
    return ;
}