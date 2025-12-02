#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class VarState {
 public:
  VarState();
  ~VarState();

  void setValue(const std::string& name, int value);
  int getValue(const std::string& name) const;
  void clear();
  int getDent();
  void indent();
  void dedent();

 private:
  std::vector<std::unordered_map<std::string, int>> values_;
  int dent;
};