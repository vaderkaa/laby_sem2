#include "Subtask.hpp"

#include <iostream>
#include <string>

Subtask::Subtask(const std::string& description, unsigned int priority, bool completed) : description(description), priority(priority), completed(completed) {}
Subtask::~Subtask() {}

void Subtask::mark_completed() { this->completed = true; }
bool Subtask::is_completed() const { return this->completed; }
unsigned int Subtask::get_priority() const { return this->priority; }
void Subtask::print() const
{
    std::cout << "[" << (completed ? 'x' : ' ') << "] P: " << priority << ", " << description << std::endl;
}