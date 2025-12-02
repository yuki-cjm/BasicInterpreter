#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Statement.hpp"

class Recorder {
 public:
  ~Recorder();

  void add(int line, std::shared_ptr<Statement> stmt);
  void remove(int line);
  std::shared_ptr<Statement> get(int line) noexcept;
  bool hasLine(int line) const noexcept;
  void clear() noexcept;
  void printLines() const;
  int nextLine(int line) const noexcept;

 private:
  // TODO
    std::map<int, std::shared_ptr<Statement>> recorder;
};