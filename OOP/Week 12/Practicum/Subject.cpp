#include "Subject.h"

void Subject::printSubjectName() const {
	std::cout << nameSub << "/n";
}

const MyString& Subject::getNameSub() const {
	return nameSub;
}

const MyString& Subject::getNameLector() const {
	return nameLector;
}

int Subject::getScore() const {
	return score;
}

Subject::Subject(MyString _nameSub, MyString _nameLector, Vector<MyString> _assistants, int _score) :
	nameSub(_nameSub), nameLector(_nameLector), assistants(_assistants), score(_score) {}

SubjectType Subject::getType() const {
	return type;
}