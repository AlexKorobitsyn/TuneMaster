#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../audio/sine_wave_player.h"

class AudioQuizWidget : public QWidget {
    Q_OBJECT
public:
    explicit AudioQuizWidget(QWidget* parent = nullptr);
    QStringList allNotes_;
    void playNote();
    void answerClicked();
    void nextQuestion();

private slots:


private:

    QLabel* labelQuestion_;
    QPushButton* btnReplay_;
    QVector<QPushButton*> answerButtons_;
    QString correctNote_;
    float currentFrequency_;
    SineWavePlayer* player_;

};