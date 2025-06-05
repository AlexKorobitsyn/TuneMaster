#pragma once

#include <QDialog>

class QSlider;
class QCheckBox;

class UserSettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit UserSettingsDialog(QWidget* parent = nullptr);

    int micSensitivity() const;
    void setMicSensitivity(int value);

    bool showHints() const;
    void setShowHints(bool value);

private:
    QSlider* sliderMicSensitivity_;
    QCheckBox* checkShowHints_;
};
