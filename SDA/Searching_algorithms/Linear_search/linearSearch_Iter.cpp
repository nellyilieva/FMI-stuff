#include <iostream>
#include <vector>

//работи независимо от подредбата на данните в него

template <class T>
int linear_search(const std::vector<T>& data, const T& el) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == el) {
            return i;
        }
    }
    return -1;
}

//тук напрактика правим и допълнителна проверка дали не сме стигнали края на масива
//за да не я правим и => ускорим работата на алгоритъма, използваме сентинел

template <class T>
int linearSearchSentonel(const std::vector<T>& data, const T& el) {
    T last = data.back();
    data.back() = el;   //set the last element of data to el -> sentinel

    int i = 0;
    while (el != data[i]) {
        i++;
    }

    data.back() = last;  //restore the original back elelement

    if (i < data.size() - 1 || data.back() == el) {
        return i;
    }

    return -1;
}

template <typename Iterator, typename T>
int linearSearch(Iterator begin, Iterator end, const T& el) {
    for (Iterator it = begin; it != end; it++) {
        if (*it == el) {
            return it;
        }
    }
    return end;
}

int main()
{

}