#include "quiz_widget.h"
#include <QVBoxLayout>

QuizWidget::QuizWidget(QWidget* parent) : QWidget(parent) {
    audioQuizWidget_ = new AudioQuizWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(audioQuizWidget_);
    setLayout(layout);
}
