#pragma once

#include <QMainWindow>
#include "../ui/user_settings_dialog.h"

class TunerWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool MainWindow::isLoudEnough(const QByteArray& data);

private slots:
    void onAbout();
    void onExit();
    void onSettings();

private:
    TunerWidget* tunerWidget_;
    void setupMenu();
};