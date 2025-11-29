// TODO: Imply interfaces declared in the Recorder.hpp.
#include "Recorder.hpp"

#include <algorithm>
#include <map>

#include "Statement.hpp"

void Recorder::add(int line, Statement* stmt){
    recorder.insert(line, stmt);
}

void Recorder::remove(int line){
    if(hasLine(line))
        recorder.erase(line);
}

const Recorder::Statement* get(int line) const noexcept{
    if(hasLine(line))
        return recorder[line];
    else
        return nullptr;
}

bool Recorder::hasLine(int line) const noexcept{
    auto it = recorder.find(line);
    if(it != recorder.end())
        return true;
    return false;
}

void Recorder::clear() noexcept{
    recorder.clear();
}

void Recorder::printLines() const{
    for(auto it = recorder.begin(); it != recorder.end(); it++)
        std::cout << (it->second).text() << '\n';
}

int Recorder::nextLine(int line) const noexcept{
    auto it = recorder.std::upper_bound(line);
    if(it != recorder.end())
        return recorder->first;
    return -1;
}