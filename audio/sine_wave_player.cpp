#include "sine_wave_player.h"
#include <QtMath>

SineWavePlayer::SineWavePlayer(QObject* parent) : QObject(parent), audio_(nullptr), device_(nullptr) {}

void SineWavePlayer::play(float frequency, int durationMs) {
    int sampleRate = 44100;
    int nSamples = (durationMs * sampleRate) / 1000;
    buffer_.resize(nSamples * sizeof(int16_t));
    int16_t* samples = reinterpret_cast<int16_t*>(buffer_.data());

    double amplitude = 16000.0; // max 32767
    double twoPiF = 2 * M_PI * frequency;
    for (int i = 0; i < nSamples; ++i) {
        double t = static_cast<double>(i) / sampleRate;
        samples[i] = static_cast<int16_t>(amplitude * qSin(twoPiF * t));
    }

    QAudioFormat format;
    format.setSampleRate(sampleRate);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    if (audio_)
        delete audio_;
    audio_ = new QAudioOutput(format, this);

    device_ = audio_->start();
    device_->write(buffer_);
}
