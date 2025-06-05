#include "string_tuner.h"
#include <cmath>

StringTuner::StringTuner(QObject *parent) : QObject(parent) {
    stringFrequencies_["E2"] = 82.41;
    stringFrequencies_["A2"] = 110.00;
    stringFrequencies_["D3"] = 146.83;
    stringFrequencies_["G3"] = 196.00;
    stringFrequencies_["B3"] = 246.94;
    stringFrequencies_["E4"] = 329.63;
    targetString_ = "E2";
}

void StringTuner::setTargetString(const QString &stringName) {
    if (stringFrequencies_.contains(stringName)) {
        targetString_ = stringName;
    }
}

QString StringTuner::getClosestString(double frequency) const {
    QString closest;
    double minDiff = 1e9;
    for (auto it = stringFrequencies_.begin(); it != stringFrequencies_.end(); ++it) {
        double diff = std::abs(it.value() - frequency);
        if (diff < minDiff) {
            minDiff = diff;
            closest = it.key();
        }
    }
    return closest;
}

double StringTuner::getTargetFrequency() const {
    return stringFrequencies_.value(targetString_, 0.0);
}

QString StringTuner::getTargetString() const {
    return targetString_;
}
