#pragma once

#include <memory>
#include <vector>

#include "Recorder.hpp"
#include "VarState.hpp"

class Statement;

class Program {
 public:
  Program();

  void addStmt(int line, std::shared_ptr<Statement> stmt);
  void removeStmt(int line);

  void run();
  void list() const;
  void clear();
  void help();

  void execute(std::shared_ptr<Statement> stmt);

  int getPC() const noexcept;
  void changePC(int line);
  void programEnd();
  void indent();
  void dedent();

  std::shared_ptr<VarState> get_vars();

 private:
  Recorder recorder_;
  VarState vars_;
  int programCounter_;
  bool programEnd_;
  bool Counter_changed;

  void resetAfterRun() noexcept;
};