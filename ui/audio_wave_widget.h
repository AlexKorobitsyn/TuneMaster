#pragma once

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QByteArray>

class AudioWaveWidget : public QWidget {
    Q_OBJECT
public:
    explicit AudioWaveWidget(QWidget* parent = nullptr);

public slots:
    void updateWave(const QByteArray& data);
    void onAudioData(const QByteArray& data);

protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QVector<float> samples_;
    static constexpr int maxSamples_ = 1024;
    QLabel* label_;
    QPixmap pixmap_;
    int width_ = 400, height_ = 100;
};
