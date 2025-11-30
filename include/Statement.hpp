#pragma once

#include <iostream>
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
    explicit RemStatement(std::string source) : Statement(std::move(source)) {};
    ~RemStatement() = default;

    void execute(VarState &state, Program& program) const override;
};

class LetStatement : public Statement {
  public:
    explicit LetStatement(std::string source, std::string name, int num): Statement(std::move(source)), variable_name(std::move(name)), value(num){};
    ~LetStatement() = default;

    void execute(VarState &state, Program& program) const override;
  private:
    std::string variable_name;
    int value;
};

class PrintStatement : public Statement {
  public:
    explicit PrintStatement(std::string source, std::shared_ptr<Expression> ptr) : Statement(std::move(source)), exp(ptr) {};
    ~PrintStatement() = default;

    void execute(VarState &state, Program& program) const override;
  private:
    std::shared_ptr<Expression> exp;
};

class InputStatement : public Statement {
  public:
    explicit InputStatement(std::string source, std::string name) : Statement(std::move(source)), variable_name(std::move(name)){};
    ~InputStatement() = default;

    void execute(VarState &state, Program& program) const override;
  private:
    std::string variable_name;
};

class EndStatement : public Statement {
  public:
    explicit EndStatement(std::string source) : Statement(std::move(source)) {};
    ~EndStatement() = default;

    void execute(VarState &state, Program& program) const override;
};

class GotoStatement : public Statement {
  public:
    explicit GotoStatement(std::string source, int line) : Statement(std::move(source)), Linenumber(line) {};
    ~GotoStatement() = default;

    void execute(VarState &state, Program& program) const override;
  private:
    int Linenumber;
};

class IfStatement : public Statement {
  public:
    explicit IfStatement(std::string source, int left, char op, int right, int num) : Statement(std::move(source)), leftvalue(left), op(op), rightvalue(right), Linenumber(num) {};
    ~IfStatement() = default;

    void execute(VarState &state, Program& program) const override;
  private:
    int leftvalue, rightvalue;
    char op;
    int Linenumber;
};
