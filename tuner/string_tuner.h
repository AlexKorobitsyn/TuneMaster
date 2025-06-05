#pragma once

#include <QObject>
#include <QString>
#include <QMap>

class StringTuner : public QObject {
    Q_OBJECT
public:
    explicit StringTuner(QObject *parent = nullptr);

    void setTargetString(const QString &stringName);
    QString getClosestString(double frequency) const;
    double getTargetFrequency() const;
    QString getTargetString() const;

private:
    QMap<QString, double> stringFrequencies_;
    QString targetString_;
};
