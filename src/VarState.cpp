#include "VarState.hpp"

#include <algorithm>

#include "utils/Error.hpp"
VarState::VarState() {
  values_.push_back({});
  dent = 0;
}

VarState::~VarState() = default;

void VarState::setValue(const std::string& name, int value) {
  values_[dent][name] = value;
}

int VarState::getValue(const std::string& name) const {
  for(auto dent_now = values_.rbegin(); dent_now != values_.rend(); dent_now++)
  {
    auto it = dent_now->find(name);
    if(it != dent_now->end())
        return it->second;
  }
  throw BasicError("VARIABLE NOT DEFINED");
}

void VarState::clear() {
    values_.clear();
    dent = 0;
}

int VarState::getDent() {
    return dent;
}

void VarState::indent() {
    values_.push_back({});
    dent++;
}

void VarState::dedent() {
    if(dent == 0)
        throw BasicError("SCOPE UNDERFLOW");
    else
    {
        values_.pop_back();
        dent--;
    }
}