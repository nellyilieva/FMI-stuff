#include <iostream>
#include <cstring>

constexpr unsigned SECONDS_IN_HOURS = 3600;
constexpr unsigned SECONDS_IN_MINUTE = 60;
constexpr unsigned DAY_SECONDS = 24 * 3600;

class Time {
private:
    unsigned secondsFromMidnight;

    bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier) {
        if (newValue >= lowerBound && newValue <= upperBound) {
            (secondsFromMidnight -= (oldValue * multiplier)) += (newValue * multiplier);
            return true;
        }
        else {
            return false;
        }
    }

public:
    Time() : secondsFromMidnight(0) {}

    Time (unsigned hours, unsigned mins, unsigned seconds) {
        setHours(hours);
        setMins(mins);
        setSeconds(seconds);
    }

    unsigned getTotalSeconds() const {
        return secondsFromMidnight;
    }

    unsigned getHours() const {
        return secondsFromMidnight / SECONDS_IN_HOURS;
    }

    unsigned getMins() const {
        return (secondsFromMidnight / 60) % 60;
    }

    unsigned getSeconds() const {
        return secondsFromMidnight % 60;
    }

    bool setHours(unsigned hours) {
        return validateAndSet(0, 23, hours, getHours(), SECONDS_IN_HOURS);
    }

    bool setMins(unsigned mins)
    {
        return validateAndSet(0, 59, mins, getMins(), SECONDS_IN_MINUTE);

    }
    bool setSeconds(unsigned seconds)
    {
        return validateAndSet(0, 59, seconds, getSeconds(), 1);
    }
};

class Exam {
private:
    Time startSecondsAfterMidnight;
    unsigned int durationSeconds;
    unsigned int maxPoints;
public:
    Time getEndTime() const {
        unsigned int endSeconds = startSecondsAfterMidnight.getTotalSeconds() + durationSeconds;
        unsigned int hours = endSeconds / SECONDS_IN_HOURS;
        unsigned int mins = (endSeconds / SECONDS_IN_MINUTE) % 60;
        unsigned int seconds = endSeconds % 60;
        return Time(hours, mins, seconds);
    }

    bool isAtTheSameTime(const Exam& other) const {
        return startSecondsAfterMidnight.getTotalSeconds() == other.getStartSecondsAfterMidnight().getTotalSeconds() &&
            durationSeconds == other.getDurationSeconds() &&
            maxPoints == other.getMaxPoints();
    }

    Exam() : startSecondsAfterMidnight(0, 0, 0), durationSeconds(0), maxPoints(0) {}

    Exam(unsigned int hours, unsigned int mins, unsigned int seconds, unsigned int duration, unsigned int max)
        : startSecondsAfterMidnight(hours, mins, seconds), durationSeconds(duration), maxPoints(max) {}

    Time getStartSecondsAfterMidnight() const {
        return startSecondsAfterMidnight;
    }

    int getDurationSeconds() const {
        return durationSeconds;
    }

    int getMaxPoints() const {
        return maxPoints;
    }

    void setStartSecondsAfterMidnight(unsigned int hours, unsigned int mins, unsigned int seconds) {
        startSecondsAfterMidnight.setHours(hours);
        startSecondsAfterMidnight.setMins(mins);
        startSecondsAfterMidnight.setSeconds(seconds);
    }

    void setDurationSeconds(int durationSeconds) {
        this->durationSeconds = durationSeconds;
    }

    void setMaxPoints(int maxPoints) {
        this->maxPoints = maxPoints;
    }


};

int main()
{
    
}
