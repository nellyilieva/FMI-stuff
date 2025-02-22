#include <iostream>

const int QUESTIONS = 10;
const int MAX_LENGTH = 50;
const int OPTIONS = 4;

enum class Options {
    A,
    B,
    C,
    D
};

struct Answer {
    char answerDescription[MAX_LENGTH + 1];
};

struct Question {
    char title[MAX_LENGTH + 1];
    int score;
    Answer arrOptions[OPTIONS];
    Options answer;
};

struct Test {
    int numQuestions;
    Question arrQ[QUESTIONS];
};

Options getOptionFromChar(char optionChar) {
    switch (optionChar) {
    case 'A':
    case 'a':
        return Options::A;
    case 'B':
    case 'b':
        return Options::B;
    case 'C':
    case 'c':
        return Options::C;
    case 'D':
    case 'd':
        return Options::D;
    }
}

void displayOptions(const Question& question) {
    for (int i = 0; i < OPTIONS; i++) {
        std::cout << question.arrOptions[i].answerDescription << std::endl;
    }
}

int finalScore(const Test& test) {
    int finalScore = 0;

    for (int i = 0; i < test.numQuestions; i++) {
        std::cout << test.arrQ[i].title << std::endl;

        displayOptions(test.arrQ[i]);

        char userAnswer;
        std::cout << "Enter your answer (A/B/C/D): ";
        std::cin >> userAnswer;

        if (getOptionFromChar(userAnswer) == test.arrQ[i].answer) {
            finalScore += test.arrQ[i].score;
        }
    }

    return finalScore;
}

int main() {
    Test test;
    test.numQuestions = 2;

    test.arrQ[0] = { "What is the capital of France?", 1, {"A: Sofia", "B: Berlin", "C: Paris", "D: Rome"}, Options::C };
    test.arrQ[1] = { "What is 2 + 2?", 1, {"A: 3", "B: 4", "C: 6", "D: 2"}, Options::B };

    char answer;
    std::cout << "Answer the following questions:" << std::endl;
    int score = finalScore(test);
    std::cout << "Your total score is: " << score << std::endl;
}