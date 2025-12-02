// TODO: Imply interfaces declared in the Program.hpp.
#include "Program.hpp"

#include <iostream>
#include <vector>

#include "Statement.hpp"
#include "Recorder.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Program::Program() = default;

void Program::addStmt(int line, std::shared_ptr<Statement> stmt){
    recorder_.add(line, stmt);
}

void Program::removeStmt(int line){
    recorder_.remove(line);
}

void Program::run(){
    programCounter_ = 0;
    programEnd_ = false;
    programCounter_ = recorder_.nextLine(programCounter_);
    while(programCounter_ != -1){
        Counter_changed = false;
        execute(recorder_.get(programCounter_));
        if(programEnd_)
            break;
        if(Counter_changed)
        {
            if(!recorder_.hasLine(programCounter_))
            {
                throw BasicError("LINE NUMBER ERROR");
                break;
            }
        }
        else
            programCounter_ = recorder_.nextLine(programCounter_);
    }
}

void Program::list() const{
    recorder_.printLines();
}

void Program::clear(){
    recorder_.clear();
    vars_.clear();
}

void Program::execute(std::shared_ptr<Statement> stmt){
    stmt->execute(vars_, *this);
}

int Program::getPC() const noexcept{
    return programCounter_;
}

void Program::changePC(int line){
    programCounter_ = line;
    Counter_changed = true;
}

void Program::programEnd(){
    programEnd_ = true;
}

void Program::indent(){
    vars_.indent();
}

void Program::dedent(){
    vars_.dedent();
}

std::shared_ptr<VarState> Program::get_vars(){
    std::shared_ptr<VarState> temp = std::make_shared<VarState>(vars_);
    return temp;
}

void Program::resetAfterRun() noexcept{
    return ;
}

void Program::help(){
    std::cout << "支持的命令:\n"
              << "  RUN - 开始执行程序\n"
              << "  LIST - 列出当前所有的程序行\n"
              << "  CLEAR - 清除当前所有的程序行\n"
              << "  QUIT - 退出解释器\n"
              << "  HELP - 打印帮助信息\n"
              << "\n"
              << "程序指令:\n"
              << "  [行号] REM <注释> - 注释行\n"
              << "  [行号] LET <变量> = <表达式> - 赋值语句\n"
              << "  [行号] PRINT <表达式> - 打印表达式值\n"
              << "  [行号] INPUT <变量> - 输入变量值\n"
              << "  [行号] END - 结束程序\n"
              << "  [行号] GOTO <行号> - 跳转到指定行\n"
              << "  [行号] IF <表达式1> <操作符> <表达式2> THEN <行号> - 条件跳转\n"
              << "  [行号] INDENT - 进入新的作用域块\n"
              << "  [行号] DEDENT - 退出当前作用域块\n"
              << "\n"
              << "立即执行指令 (不带行号):\n"
              << "  LET <变量> = <表达式>\n"
              << "  PRINT <表达式>\n"
              << "  INPUT <变量>\n"
              << "  INDENT\n"
              << "  DEDENT\n";
}