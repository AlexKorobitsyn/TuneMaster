#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QTimer>

class QuizManager : public QObject {
    Q_OBJECT

public:
    enum class QuizType {
        NoteByName,
        NameByNote
    };

    explicit QuizManager(QObject *parent = nullptr);

    void setQuizType(QuizType type);
    void start();
    void stop();

signals:
    void questionReady(const QString &question);
    void answerChecked(bool correct);

public slots:
    void submitAnswer(const QString &answer);

private:
    QuizType currentType = QuizType::NoteByName;
    QString currentQuestion;
    QString currentAnswer;
    bool active = false;

    void generateQuestion();
    QString getRandomNoteName() const;
    int getRandomMidiNote() const;
};
