#include "pitch_detector.h"
#include <cmath>

PitchDetector::PitchDetector(QObject* parent)
    : QObject(parent) {}

float PitchDetector::detectPitch(const QByteArray& audioData, int sampleRate) {
    const int16_t* samples = reinterpret_cast<const int16_t*>(audioData.constData());
    int sampleCount = audioData.size() / sizeof(int16_t);

    if (sampleCount < 2)
        return 0.0f;

    int zeroCrossings = 0;
    for (int i = 1; i < sampleCount; ++i) {
        if ((samples[i - 1] < 0 && samples[i] >= 0) || (samples[i - 1] > 0 && samples[i] <= 0))
            ++zeroCrossings;
    }

    float frequency = (zeroCrossings * sampleRate) / (2.0f * sampleCount);
    return frequency;
}
