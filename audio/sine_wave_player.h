#pragma once
#include <QObject>
#include <QAudioOutput>
#include <QIODevice>
#include <QTimer>

class SineWavePlayer : public QObject {
    Q_OBJECT
public:
    explicit SineWavePlayer(QObject* parent = nullptr);
    void play(float frequency, int durationMs = 800);

private:
    QAudioOutput* audio_;
    QIODevice* device_;
    QByteArray buffer_;
};
