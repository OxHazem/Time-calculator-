#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Countdown");
    resize(900, 500);


    input = new QLineEdit("00:05:00");
    input->setFixedWidth(140);
    input->setInputMask("00:00:00"); // enforce hh:mm:ss

    startBtn = new QPushButton("Start");
    resetBtn = new QPushButton("Reset");


    timeLabel = new QLabel("00:05:00");
    timeLabel->setAlignment(Qt::AlignCenter);

    QFont bigFont("Consolas", 150, QFont::Bold);
    timeLabel->setFont(bigFont);

    QHBoxLayout *top = new QHBoxLayout;
    top->addWidget(input);
    top->addWidget(startBtn);
    top->addWidget(resetBtn);
    top->addStretch();

    QVBoxLayout *main = new QVBoxLayout;
    main->addLayout(top);
    main->addStretch();
    main->addWidget(timeLabel);
    main->addStretch();

    setLayout(main);

    // ===== STYLE =====
    setStyleSheet(R"(
        QWidget {
            background-color: #1e1f26;
            color: white;
        }

        QLabel {
            color: #4CAF50;
        }

        QLineEdit {
            background-color: #2b2d36;
            color: white;
            border: none;
            padding: 6px;
            font-size: 16px;
        }

        QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 8px;
        }

        QPushButton:hover {
            background-color: #45a049;
        }
    )");

    // ===== TIMER =====
    timer = new QTimer(this);

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startCountdown);
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::resetCountdown);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
}

void MainWindow::startCountdown() {
    QString text = input->text(); // format hh:mm:ss

    QStringList parts = text.split(":");

    // Validate format
    if (parts.size() != 3) {
        timeLabel->setText("Invalid");
        return;
    }

    int h = parts[0].toInt();
    int m = parts[1].toInt();
    int s = parts[2].toInt();

    // Validate values
    if (m >= 60 || s >= 60) {
        timeLabel->setText("Invalid");
        return;
    }

    remainingSeconds = h * 3600 + m * 60 + s;

    updateDisplay();
    timer->start(1000);
}

void MainWindow::resetCountdown() {
    timer->stop();
    remainingSeconds = 0;
    timeLabel->setText("00:00:00");
}

void MainWindow::updateTime() {
    if (remainingSeconds <= 0) {
        timer->stop();
        timeLabel->setText("00:00:00");
        return;
    }

    remainingSeconds--;
    updateDisplay();
}

void MainWindow::updateDisplay() {
    int h = remainingSeconds / 3600;
    int m = (remainingSeconds % 3600) / 60;
    int s = remainingSeconds % 60;

    QString text = QString("%1:%2:%3")
        .arg(h, 2, 10, QChar('0'))
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));

    timeLabel->setText(text);

    // Color warning (last 10 seconds)
    if (remainingSeconds <= 10 && remainingSeconds > 0) {
        timeLabel->setStyleSheet("color: red;");
    } else {
        timeLabel->setStyleSheet("color: #4CAF50;");
    }
}