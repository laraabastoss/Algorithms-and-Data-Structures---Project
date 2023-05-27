#include "Student.h"

using namespace std;

Student::Student(string c): code(c) {}

Student::Student(string c, string n): code(c), name(n) {}

string Student::getCode() const {
    return code;
}

string Student::getName() const {
    return name;
}

list<UcTurma> Student::getUcturma() const {
    return ucturmas;
}

void Student::addUcturma(UcTurma& uc) {
    ucturmas.push_back(uc);
}

bool Student::operator<(const Student &s) const {
    return code < s.getCode();
}

void Student::removeUcturma(UcTurma &uc) {
    ucturmas.remove(uc);
}