#pragma once

#include "Subtask.hpp"

#include <string>

struct SubtaskNode
{
    Subtask data; //pola struktury
    SubtaskNode* next;
    SubtaskNode(const Subtask& data) : data(data), next(nullptr) {} //konstruktor wezla
};

class Task
{
private:
    std::string description;
    SubtaskNode* head;

public:
    Task(const std::string description);
    ~Task();

    void add_subtask(const Subtask& subtask); //dodaje pod-zadanie do listy, zachowujac kolejnosc zgodnie z nierosnacym priorytetem
    void complete_subtask(unsigned int index); //oznacza jako ukonczone pod-zadanie o wskazanym indeksie (liczac od 0)
    bool is_completed() const; //zwraca true, jesli wszystkie pod-zadania sa ukonczone, w przeciwnym razie false
    void clear(); //usuwa wszystkie pod-zadania z listy
    void print() const; //wypisuje zadanie oraz jego pod-zadania

    Task(const Task& other);
    Task& operator=(const Task& other);

    Task(Task&& other);
    Task& operator=(Task&& other);

    Task() = default;
};