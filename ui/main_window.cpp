#include "main_window.h"
#include "../ui/tuner_widget.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include "../audio/mic_input.h"
#include "../audio/pitch_detector.h"
#include "../tuner/string_tuner.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDockWidget>
#include "audio_wave_widget.h"
#include "../theory/quiz_widget.h"
#include "../theory/audio_quiz_widget.h"

    
bool MainWindow::isLoudEnough(const QByteArray& data) {
    const int16_t* samples = reinterpret_cast<const int16_t*>(data.constData());
    int sampleCount = data.size() / sizeof(int16_t);

    int64_t sum = 0;
    for (int i = 0; i < sampleCount; ++i)
        sum += std::abs(samples[i]);

    double avg = sum / static_cast<double>(sampleCount);
    return avg > 500; 
}
void MainWindow::onSettings() {
    UserSettingsDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        int sens = dlg.micSensitivity();
        bool showHints = dlg.showHints();
        // tunerWidget_->setMicSensitivity(sens);???
        // tunerWidget_->setShowHints(showHints);можно
    }
}

void MainWindow::setupMenu() {
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* fileMenu = menuBar->addMenu(tr("&Файл"));
    QMenu* helpMenu = menuBar->addMenu(tr("&Справка"));
    QMenu* settingsMenu = menuBar->addMenu(tr("&Настройки"));
    QAction* userSettingsAction = new QAction(tr("Пользовательские настройки"), this);

    QAction* exitAction = new QAction(tr("Выход"), this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);

    QAction* aboutAction = new QAction(tr("О программе"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    
    connect(userSettingsAction, &QAction::triggered, this, &MainWindow::onSettings);
    settingsMenu->addAction(userSettingsAction);


    fileMenu->addAction(exitAction);
    helpMenu->addAction(aboutAction);

    setMenuBar(menuBar);
}



void MainWindow::onAbout() {
    QMessageBox::about(this, "О программе", "TuneMaster v0.1\nPet-проект для настройки гитары и изучения теории музыки на Qt.");
}

void MainWindow::onExit() {
    close();
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    MicInput* micInput_;
    PitchDetector* pitchDetector_;
    StringTuner* stringTuner_;
    AudioWaveWidget* audioWaveWidget_;

    auto* tabs = new QTabWidget(this);
    tunerWidget_ = new TunerWidget(this);
    tabs->addTab(tunerWidget_, tr("Гитарный тюнер"));
    auto* quizWidget = new QuizWidget(this);
    tabs->addTab(quizWidget, tr("Викторина"));
    setCentralWidget(tabs);
    setWindowTitle("TuneMaster");
    resize(600, 400);

    setupMenu();

    audioWaveWidget_ = new AudioWaveWidget(this);


    auto* dockWave = new QDockWidget("Волна звука", this);
    dockWave->setWidget(audioWaveWidget_);
    dockWave->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, dockWave);
    micInput_ = new MicInput(this);
    pitchDetector_ = new PitchDetector(this);
    stringTuner_ = new StringTuner(this);
    connect(micInput_, &MicInput::audioDataReady, audioWaveWidget_, &AudioWaveWidget::onAudioData);


    connect(micInput_, &MicInput::audioDataReady, this, [=](const QByteArray& data) {
        if (!isLoudEnough(data)) return;
        float freq = pitchDetector_->detectPitch(data);
        QString targetNote = tunerWidget_->selectedNote();
        float targetFreq = tunerWidget_->getTargetFrequency(targetNote);
        tunerWidget_->updatePitch(freq, targetFreq);

        });
    micInput_->start();
}



MainWindow::~MainWindow() = default;
