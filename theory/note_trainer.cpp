#include "note_trainer.h"
#include <QRandomGenerator>

NoteTrainer::NoteTrainer(QObject *parent) : QObject(parent) {}

void NoteTrainer::setOctaveRange(int min, int max) {
    octaveMin = min;
    octaveMax = max;
}

void NoteTrainer::setNotationStyle(NotationStyle style) {
    currentStyle = style;
}

QString NoteTrainer::getRandomNote() const {
    int octave = QRandomGenerator::global()->bounded(octaveMin, octaveMax + 1);
    int note = QRandomGenerator::global()->bounded(12);
    int midi = octave * 12 + note;
    return getNoteName(midi);
}

QString NoteTrainer::getNoteName(int midiNote) const {
    int noteIndex = midiNote % 12;
    int octave = midiNote / 12;

    QString name = (currentStyle == NotationStyle::Western)
                       ? westernName(noteIndex)
                       : russianName(noteIndex);

    return QString("%1%2").arg(name).arg(octave);
}

QString NoteTrainer::westernName(int index) const {
    static const QVector<QString> names = {
        "C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B"
    };
    return names[index];
}

QString NoteTrainer::russianName(int index) const {
    static const QVector<QString> names = {
        "До", "До♯", "Ре", "Ре♯", "Ми", "Фа",
        "Фа♯", "Соль", "Соль♯", "Ля", "Ля♯", "Си"
    };
    return names[index];
}
