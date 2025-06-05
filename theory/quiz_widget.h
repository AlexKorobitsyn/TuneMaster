#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "../theory/audio_quiz_widget.h"

class QuizWidget : public QWidget {
    Q_OBJECT
public:
    explicit QuizWidget(QWidget* parent = nullptr);
    AudioQuizWidget* audioQuizWidget_;
    void showQuestion(const QString& question);
    void checkAnswer();

    void showAnswerResult(bool correct);

private slots:


private:
    QLabel* labelQuestion_;
    QLineEdit* editAnswer_;
    QPushButton* btnSubmit_;
    QLabel* labelFeedback_;

};
