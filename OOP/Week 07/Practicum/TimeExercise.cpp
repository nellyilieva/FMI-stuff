#include <iostream>
#include "TimeExercise.h"

const Time::Duration Time::Duration::Seconds(1);
const Time::Duration Time::Duration::Minutes(60);
const Time::Duration Time::Duration::Hours(3600);

Time::Duration::Duration() : seconds(0) {}

Time::Duration::Duration(unsigned _seconds) : seconds(_seconds) {}

unsigned Time::Duration::getSeconds() const {
    return seconds;
}

//prefix
Time::Duration& Time::Duration::operator++() {
    ++seconds;
    return *this;
}

Time::Duration& Time::Duration::operator--() {
    --seconds;
    return *this;
}

//syfix
Time::Duration& Time::Duration::operator++(int) {
    Time:Duration temp = *this;
    ++(*this);
    return temp;
}

Time::Duration& Time::Duration::operator--(int) {
    Time:Duration temp = *this;
    --(*this);
    return temp;
}

Time::Duration& Time::Duration::operator+=(const Duration& other) {
    seconds += other.seconds;
    return *this;
}

Time::Duration& Time::Duration::operator-=(const Duration& other) {
    seconds -= other.seconds;
    return *this;
}

Time::Duration& Time::Duration::operator*=(unsigned factor) {
    seconds *= factor;
    return *this;
}

Time::Duration operator+(const Time::Duration& lhs, const Time::Duration& rhs) {
    Time::Duration d(lhs.getSeconds());
    d += rhs.getSeconds();
    return d;
}

Time::Duration operator-(const Time::Duration& lhs, const Time::Duration& rhs) {
    Time::Duration d(lhs.getSeconds());
    d -= rhs.getSeconds();
    return d;
}

//std::istream& operator>>(std::istream& is, Time::Duration& d) {
//    is >> d.getSeconds();
//    return is;
//}
//
//std::ostream& operator<<(std::ostream& os, const Time::Duration& d) {
//    os << d.getSeconds() << "seconds";
//    return os;
//}

bool operator==(const Time::Duration& lhs, const Time::Duration& rhs) {
    return lhs.getSeconds() == rhs.getSeconds();
}

bool operator!=(const Time::Duration& lhs, const Time::Duration& rhs) {
    return lhs.getSeconds() != rhs.getSeconds();
}

bool operator<(const Time::Duration& lhs, const Time::Duration& rhs) {
    return lhs.getSeconds() < rhs.getSeconds();
}

bool operator>(const Time::Duration& lhs, const Time::Duration& rhs) {
    return lhs.getSeconds() > rhs.getSeconds();
}

bool operator<=(const Time::Duration& lhs, const Time::Duration& rhs) {
    return lhs.getSeconds() <= rhs.getSeconds();
}

bool operator>=(const Time::Duration& lhs, const Time::Duration& rhs) {
    return lhs.getSeconds() >= rhs.getSeconds();
}

int main()
{
    
}
