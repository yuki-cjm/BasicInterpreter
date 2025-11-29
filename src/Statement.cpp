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

void RemStatement::execute(VarState &state, Program& program) const override{}

void LetStatement::execute(VarState &state, Program& program) const override{
    state.setvalue(variable_name, value);
}

void PrintStatement::execute(VarState &state, Program& program) const override{
    std::cout << result << '\n';
}

void InputStatement::execute(VarState &state, Program& program) const override{
    int value;
    std::cin >> value;
    state.setvalue(variable_name, value);
}

void EndStatement::execute(VarState &state, Program& program) const override{
    program.programEnd();
}

void GotoStatement::execute(VarState &state, Program& program) const override{
    program.changePC(Linenumber);
}

void IfStatement::execute(VarState &state, Program& program) const override{
    switch(op)
    {
        case '<': if(leftvalue < rightvalue) program.changePC(Linenumber); break;
        case '=': if(leftvalue == rightvalue) program.changePC(Linenumber); break;
        case '>': if(leftvalue > rightvalue) program.changePC(Linenumber); break;
    }
}

void Runstatement::execute(VarState &state, Program& program) const override{
    program.run();
}

void ListStatement::execute(VarState &state, Program& program) const override{
    program.list();
}

void ClearStatement::execute(VarState &state, Program& program) const override{
    program.clear();
}

void QuitStatement::execute(VarState &state, Program& program) const override{
    exit(0);
}

void HelpStatement::execute(VarState &state, Program& program) const override{
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