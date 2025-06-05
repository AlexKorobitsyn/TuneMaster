#pragma once

#include <QObject>
#include <QByteArray>

class PitchDetector : public QObject {
    Q_OBJECT
public:
    explicit PitchDetector(QObject* parent = nullptr);

    float detectPitch(const QByteArray& audioData, int sampleRate = 44100);

signals:
    void pitchDetected(float frequency);  
};
