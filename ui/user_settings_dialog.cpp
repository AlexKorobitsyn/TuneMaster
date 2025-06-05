#include "user_settings_dialog.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>

UserSettingsDialog::UserSettingsDialog(QWidget* parent)
    : QDialog(parent)
{
    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel("Чувствительность микрофона:", this);
    sliderMicSensitivity_ = new QSlider(Qt::Horizontal, this);
    sliderMicSensitivity_->setRange(1, 100);
    sliderMicSensitivity_->setValue(50);

    checkShowHints_ = new QCheckBox("Показывать советы по настройке", this);
    checkShowHints_->setChecked(true);

    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(label);
    layout->addWidget(sliderMicSensitivity_);
    layout->addWidget(checkShowHints_);
    layout->addWidget(buttonBox);
}

int UserSettingsDialog::micSensitivity() const {
    return sliderMicSensitivity_->value();
}

void UserSettingsDialog::setMicSensitivity(int value) {
    sliderMicSensitivity_->setValue(value);
}

bool UserSettingsDialog::showHints() const {
    return checkShowHints_->isChecked();
}

void UserSettingsDialog::setShowHints(bool value) {
    checkShowHints_->setChecked(value);
}
