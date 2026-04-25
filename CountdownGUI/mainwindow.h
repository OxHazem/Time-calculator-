#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QLabel *timeLabel;
    QLineEdit *input;
    QPushButton *startBtn;
    QPushButton *resetBtn;
    QTimer *timer;

    int remainingSeconds = 0;

    void updateDisplay();

private slots:
    void startCountdown();
    void resetCountdown();
    void updateTime();
};

#endif
