// TODO: Imply interfaces declared in the Recorder.hpp.
#include "Recorder.hpp"

#include <iostream>
#include <algorithm>
#include <map>

#include "Statement.hpp"
Recorder::~Recorder(){
    for(auto it = recorder.begin(); it != recorder.end(); it++)
        delete it->second;
}

void Recorder::add(int line, Statement* stmt){
    if(hasLine(line))
    {
        delete recorder[line];
        if(stmt == nullptr)
            recorder.erase(line);
        else
            recorder[line] = stmt;
    }
    else 
        if(stmt != nullptr)
            recorder.insert({line, stmt});
}

void Recorder::remove(int line){
    if(hasLine(line))
        recorder.erase(line);
}

Statement* Recorder::get(int line) noexcept{
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
    for(auto it = recorder.begin(); it != recorder.end(); it++)
        delete it->second;
    recorder.clear();
}

void Recorder::printLines() const{
    for(auto it = recorder.begin(); it != recorder.end(); it++)
        std::cout << (it->second)->text() << '\n';
}

int Recorder::nextLine(int line) const noexcept{
    auto it = recorder.upper_bound(line);
    if(it != recorder.end())
        return it->first;
    return -1;
}

