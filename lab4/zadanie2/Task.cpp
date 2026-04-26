#include "Task.hpp"
#include "Subtask.hpp"

#include <iostream>

Task::Task(const std::string description) : description(description), head(nullptr) {}
Task::~Task() { clear(); }

void Task::add_subtask(const Subtask& subtask)
{
    SubtaskNode* new_node = new SubtaskNode(subtask);
    if(head == nullptr || subtask.get_priority() > head->data.get_priority()) //strzalka, bo head jest wskaznikiem
    {
        new_node->next = head; //ustawiamy next na null albo podlaczamy na poczatek
        head = new_node;
        return;
    }

    SubtaskNode* current = head;
    while(current->next != nullptr && subtask.get_priority() <= current->next->data.get_priority())
        current = current->next; //PAMIETAJ, ZEBY ZMIENIAC CURRENT, BO ZAPOMINAM XD
    new_node->next = current->next;
    current->next = new_node;
}

void Task::complete_subtask(unsigned int index)
{
    if(head == nullptr)
        return;

    SubtaskNode* current = head;
    unsigned int position = 0;
    while(current->next != nullptr && position != index)
    {
        position++;
        current = current->next;
    }
    if(position == index)
        current->data.mark_completed();
}

bool Task::is_completed() const
{
    SubtaskNode* current = head;
    while(current != nullptr)
    {
        if(current->data.is_completed() == false)
            return false;
        current = current->next;
    }
    return true;
}

void Task::clear()
{
    while(head != nullptr)
    {
        SubtaskNode* temp = head;
        head = head->next; //zmieniamy glowe
        delete temp; //i dopiero usuwamy zawartosc
    }
}

void Task::print() const
{
    std::cout << "[" << (is_completed() ? 'x' : ' ') << "] " << description << std::endl;
    SubtaskNode* current = head;
    while(current != nullptr)
    {
        std::cout << "  - ";
        current->data.print();
        current = current->next;
    }
}

Task::Task(const Task& other) : description(other.description)
{
    head = nullptr;
    SubtaskNode* current = other.head;
    while(current != nullptr)
    {
        add_subtask(current->data);
        current = current->next;
    }
}

Task& Task::operator=(const Task& other)
{
    if(this != &other)
    {
        this->clear();
        description = other.description;
        head = nullptr;
        SubtaskNode* current = other.head;
        while(current != nullptr)
        {
            add_subtask(current->data);
            current = current->next;
        }
    }
    return *this;
}

Task::Task(Task&& other) : description(std::move(other.description)), head(other.head) //BEZ CONST!!!
{
    other.head = nullptr;
}

Task& Task::operator=(Task&& other)
{
    if(this != &other)
    {
        this->clear();
        description = std::move(other.description); //MOVE DO PRZENOSZENIA STRINGOW
        head = other.head;
        other.head = nullptr;
    }
    return *this;
}