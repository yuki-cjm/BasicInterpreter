#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};

// TODO: Other statement types derived from Statement, e.g., GOTOStatement,
// LetStatement, etc.
class RemStatement : public Statement {
  public:
    explicit RemStatement(std::string source) : Statement(source) {};
    ~RemStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
};

class LetStatement : public Statement {
  public:
    explicit LetStatement(std::string source, std::string name, int num): Statement(source), variable_name(name), value(num){};
    ~LetStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
  private:
    std::string variable_name;
    int value;
};

class PrintStatement : public Statement {
  public:
    explicit PrintStatement(std::string source, int value) : Statement(source), result(value) {};
    ~PrintStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
  private:
    int result;
};

class InputStatement : public Statement {
  public:
    explicit InputStatement(std::string source, std::string name) : Statement(source), variable_name(name){};
    ~InputStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
  private:
    std::string variable_name;
};

class EndStatement : public Statement {
  public:
    explicit EndStatement(std::string source) : Statement(source) {};
    ~EndStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
};

class GotoStatement : public Statement {
  public:
    explicit GotoStatement(std::string source, int line) : Statement(source), Linenumber(line) {};
    ~GotoStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
  private:
    int Linenumber;
};

class IfStatement : public Statement {
  public:
    explicit IfStatement(std::string source, int left, char op, int right, int num) : Statement(source), leftvalue(left), op(op), rightvalue(right), Linenumber(num) {};
    ~IfStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
  private:
    int leftvalue, rightvalue;
    char op;
    int Linenumber;
};

class RunStatement : public Statement {
  public:
    explicit RunStatement(std::string source) : Statement(source) {};
    ~RunStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
};

class ListStatement : public Statement {
  public:
    explicit ListStatement(std::string source) : Statement(source) {};
    ~ListStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
};

class ClearStatement : public Statement {
  public:
    explicit ClearStatement(std::string source) : Statement(source) {};
    ~ClearStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
};

class QuitStatement : public Statement {
  public:
    explicit QuitStatement(std::string source) : Statement(source) {};
    ~QuitStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
};

class HelpStatement : public Statement {
  public:
    explicit HelpStatement(std::string source) : Statement(source) {};
    ~HelpStatement() { delete this; };

    void execute(VarState &state, Program& program) const override;
};