#include "audio_quiz_widget.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QMap>
#include <algorithm>

AudioQuizWidget::AudioQuizWidget(QWidget* parent) : QWidget(parent) {
    labelQuestion_ = new QLabel("Что за нота звучит?", this);
    btnReplay_ = new QPushButton("Ещё раз", this);

    QHBoxLayout* answersLayout = new QHBoxLayout;
    for (int i = 0; i < 4; ++i) {
        QPushButton* btn = new QPushButton(this);
        connect(btn, &QPushButton::clicked, this, &AudioQuizWidget::answerClicked);
        answerButtons_ << btn;
        answersLayout->addWidget(btn);
    }

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(labelQuestion_);
    mainLayout->addLayout(answersLayout);
    mainLayout->addWidget(btnReplay_);
    setLayout(mainLayout);

    allNotes_ = QStringList{ "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5" };
    player_ = new SineWavePlayer(this);

    connect(btnReplay_, &QPushButton::clicked, this, &AudioQuizWidget::playNote);

    nextQuestion();
}

void AudioQuizWidget::playNote() {
    player_->play(currentFrequency_, 1500); // 1500 ms — дольшеб
}

void AudioQuizWidget::answerClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    if (btn->text() == correctNote_) {
        QMessageBox::information(this, "Верно!", "Молодец!");
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Правильный ответ: " + correctNote_);
    }
    nextQuestion();
}

void AudioQuizWidget::nextQuestion() {
    correctNote_ = allNotes_[QRandomGenerator::global()->bounded(allNotes_.size())];
    QStringList answers = { correctNote_ };
    while (answers.size() < 4) {
        QString note = allNotes_[QRandomGenerator::global()->bounded(allNotes_.size())];
        if (!answers.contains(note))
            answers << note;
    }
    std::shuffle(answers.begin(), answers.end(), *QRandomGenerator::global());

    for (int i = 0; i < 4; ++i) {
        answerButtons_[i]->setText(answers[i]);
    }

    static QMap<QString, float> noteToFreq = {
        {"C4", 261.63f}, {"D4", 293.66f}, {"E4", 329.63f}, {"F4", 349.23f},
        {"G4", 392.00f}, {"A4", 440.00f}, {"B4", 493.88f}, {"C5", 523.25f}
    };
    currentFrequency_ = noteToFreq.value(correctNote_, 440.0f);

    playNote();
}
