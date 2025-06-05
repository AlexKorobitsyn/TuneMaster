#include "quiz_manager.h"
#include <QRandomGenerator>

QuizManager::QuizManager(QObject *parent) : QObject(parent) {}

void QuizManager::setQuizType(QuizType type) {
    currentType = type;
}

void QuizManager::start() {
    active = true;
    generateQuestion();
}

void QuizManager::stop() {
    active = false;
}

void QuizManager::submitAnswer(const QString &answer) {
    if (!active) return;
    emit answerChecked(answer.trimmed().compare(currentAnswer, Qt::CaseInsensitive) == 0);
    if (active) generateQuestion();
}

void QuizManager::generateQuestion() {
    int midi = getRandomMidiNote();
    QString noteName = getRandomNoteName();

    if (currentType == QuizType::NoteByName) {
        currentQuestion = QString("Play note: %1").arg(noteName);
        currentAnswer = noteName;
    } else {
        currentQuestion = QString("Which note is this? (MIDI %1)").arg(midi);
        currentAnswer = getRandomNoteName();  //stub
    }

    emit questionReady(currentQuestion);
}

QString QuizManager::getRandomNoteName() const {
    static const QVector<QString> names = {
        "C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B"
    };
    int index = QRandomGenerator::global()->bounded(12);
    int octave = QRandomGenerator::global()->bounded(3, 6);
    return QString("%1%2").arg(names[index]).arg(octave);
}

int QuizManager::getRandomMidiNote() const {
    int octave = QRandomGenerator::global()->bounded(3, 6);
    int note = QRandomGenerator::global()->bounded(12);
    return octave * 12 + note;
}
