#include "audio_wave_widget.h"
#include <QPainter>
#include <QVBoxLayout>

AudioWaveWidget::AudioWaveWidget(QWidget* parent) : QWidget(parent), pixmap_(width_, height_) {
    label_ = new QLabel(this);
    label_->setFixedSize(width_, height_);
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(label_);
    setLayout(layout);
    pixmap_.fill(Qt::black);
    label_->setPixmap(pixmap_);
}

void AudioWaveWidget::onAudioData(const QByteArray& data) {
    const int16_t* raw = reinterpret_cast<const int16_t*>(data.constData());
    int n = data.size() / sizeof(int16_t);
    for (int i = 0; i < n; ++i) {
        samples_.append(raw[i] / 32768.0f); // норма на [-1, 1]
        if (samples_.size() > maxSamples_)
            samples_.remove(0, samples_.size() - maxSamples_);
    }
    update();
}

void AudioWaveWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.fillRect(rect(), Qt::white);

    if (samples_.isEmpty())
        return;

    QPen pen(Qt::blue, 2);
    p.setPen(pen);

    int w = width();
    int h = height();
    int N = samples_.size();
    QPoint last(0, h / 2);

    for (int i = 0; i < N; ++i) {
        float x = float(i) * w / N;
        float y = h / 2 - samples_[i] * (h / 2 - 5);
        QPoint pt(x, y);
        if (i > 0)
            p.drawLine(last, pt);
        last = pt;
    }
}

void AudioWaveWidget::updateWave(const QByteArray& data) {
    pixmap_.fill(Qt::black);
    QPainter painter(&pixmap_);
    painter.setPen(Qt::green);

    const int16_t* samples = reinterpret_cast<const int16_t*>(data.constData());
    int sampleCount = data.size() / sizeof(int16_t);

    if (sampleCount < 2) {
        label_->setPixmap(pixmap_);
        return;
    }

    int prevY = height_ / 2;
    for (int x = 0; x < width_ && x < sampleCount; ++x) {
        int16_t sample = samples[x];
        int y = height_ / 2 - (sample * (height_ / 2)) / 32768;
        if (x > 0)
            painter.drawLine(x - 1, prevY, x, y);
        prevY = y;
    }

    label_->setPixmap(pixmap_);
}
