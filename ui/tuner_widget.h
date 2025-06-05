#pragma once

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>

class TunerWidget : public QWidget {
    Q_OBJECT

public:
    explicit TunerWidget(QWidget *parent = nullptr);
    void updatePitch(float frequency, float target);
    QString selectedNote() const;

    QString getClosestNote(float freq) const;
    QString getTuningHint(float freq, float target) const;
    float getTargetFrequency(const QString& note) const;

private:
    QLabel *labelNote;
    QLabel *labelFrequency;
    QLabel *labelHint;

    QComboBox* stringSelector;
   
};
