#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QPair>

class NoteTrainer : public QObject {
    Q_OBJECT

public:
    enum class NotationStyle { Western, Russian };

    explicit NoteTrainer(QObject *parent = nullptr);

    void setOctaveRange(int min, int max);
    void setNotationStyle(NotationStyle style);

    QString getRandomNote() const;
    QString getNoteName(int midiNote) const;

private:
    int octaveMin = 2;
    int octaveMax = 5;
    NotationStyle currentStyle = NotationStyle::Western;

    QString westernName(int index) const;
    QString russianName(int index) const;
};
