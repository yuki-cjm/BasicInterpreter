#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Statement.hpp"

class Recorder {
 public:
  ~Recorder() = default;

  void add(int line, Statement* stmt);
  void remove(int line);
  Statement* get(int line) noexcept;
  bool hasLine(int line) const noexcept;
  void clear() noexcept;
  void printLines() const;
  int nextLine(int line) const noexcept;

 private:
  // TODO
    std::map<int, Statement*> recorder;
};
