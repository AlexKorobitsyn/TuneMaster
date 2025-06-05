#include "mic_input.h"
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QDebug>

MicInput::MicInput(QObject *parent) : QObject(parent) {
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying nearest";
        format = info.nearestFormat(format);
    }

    audioInput_ = new QAudioInput(info, format, this);
}

MicInput::~MicInput() {
    stop();
    delete audioInput_;
}

void MicInput::start() {
    if (!audioInput_) return;
    inputIODevice_ = audioInput_->start();
    connect(inputIODevice_, &QIODevice::readyRead, this, &MicInput::handleAudioData);
}

void MicInput::stop() {
    if (audioInput_) audioInput_->stop();
    if (inputIODevice_) {
        disconnect(inputIODevice_, &QIODevice::readyRead, this, &MicInput::handleAudioData);
        inputIODevice_ = nullptr;
    }
}

void MicInput::handleAudioData() {
    if (!inputIODevice_) return;
    QByteArray data = inputIODevice_->readAll();
    emit audioDataReady(data);
}
