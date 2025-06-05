#pragma once

#include <QObject>
#include <QAudioInput>
#include <QIODevice>

class MicInput : public QObject {
    Q_OBJECT
public:
    explicit MicInput(QObject *parent = nullptr);
    ~MicInput();

    void start();
    void stop();

signals:
    void audioDataReady(const QByteArray &data);

private slots:
    void handleAudioData();

private:
    QAudioInput *audioInput_ = nullptr;
    QIODevice *inputIODevice_ = nullptr;
};
