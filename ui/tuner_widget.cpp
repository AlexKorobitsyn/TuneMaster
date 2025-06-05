#include "tuner_widget.h"
#include <cmath>
#include <QMap>

TunerWidget::TunerWidget(QWidget* parent) : QWidget(parent) {
    labelNote = new QLabel("Note: -", this);
    labelFrequency = new QLabel("Freq: - Hz", this);
    labelHint = new QLabel("Hint: -", this);

    stringSelector = new QComboBox(this);
    stringSelector->addItems({
        "E2", "A2", "D3", "G3", "B3", "E4"
        });

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Select string:", this));
    layout->addWidget(stringSelector);
    layout->addWidget(labelNote);
    layout->addWidget(labelFrequency);
    layout->addWidget(labelHint);
    setLayout(layout);
}

QString TunerWidget::selectedNote() const {
    return stringSelector->currentText();
}


void TunerWidget::updatePitch(float frequency, float target) {
    QString note = getClosestNote(frequency);
    labelNote->setText("Note: " + note);
    labelFrequency->setText(QString("Freq: %1 Hz").arg(frequency, 0, 'f', 2));
    labelHint->setText("Hint: " + getTuningHint(frequency, target));
}

QString TunerWidget::getClosestNote(float freq) const {
    static const QVector<QString> notes = {
        "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
    };
    int midi = qRound(69 + 12 * std::log2(freq / 440.0));
    int index = midi % 12;
    int octave = midi / 12 - 1;
    return notes[index] + QString::number(octave);
}

float TunerWidget::getTargetFrequency(const QString &note) const {
    QRegExp rx("([A-G]#?)(\\d+)");
    if (!rx.exactMatch(note)) return 0.0;
    QString name = rx.cap(1);
    int octave = rx.cap(2).toInt();

    static const QMap<QString, int> noteOffsets = {
        {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4},
        {"F", 5}, {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
    };

    int semitone = (octave + 1) * 12 + noteOffsets.value(name, 0);
    return 440.0 * std::pow(2.0, (semitone - 69) / 12.0);
}

QString TunerWidget::getTuningHint(float freq, float target) const {
    if (target == 0.0) return "-";
    float diff = freq - target;
    if (std::abs(diff) < 0.5f) return "Perfect!";
    return (diff > 0) ? "Too high" : "Too low";
}
