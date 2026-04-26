#pragma once

#include <string>

class Subtask
{
private:
    std::string description; //opis pod-zadania
    unsigned int priority; //priorytet zadania (im wyzsza liczba, tym wyzszy priorytet)
    bool completed; //informacja, czy zadanie zostało wykonane

public:
    Subtask(const std::string& description, unsigned int priority = 0, bool completed = false); //TU PRZY REFERENCJI MUSI BYC CONST!!!
    ~Subtask();

    void mark_completed(); //oznacza pod-zadanie jako wykonane
    bool is_completed() const; //zwraca, czy zadanie jest ukonczone
    unsigned int get_priority() const; //zwraca priorytet
    void print() const; //wypisuje pod-zadanie
};