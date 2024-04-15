#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTableWidget *t = ui->tableWidget;
    int column = 2; // 3列目
    for (int row = 0; row < t->rowCount(); row++) {
        QPushButton *startButton = new QPushButton("Start");
        QPushButton *stopButton = new QPushButton("Stop");
        // [Start]ボタンと[Stop]ボタンをトグルさせる
        startButton->setCheckable(true);
        stopButton->setCheckable(true);
        startButton->setAutoExclusive(true);
        stopButton->setAutoExclusive(true);
        startButton->setStyleSheet("background-color: rgb(224,224,224)");
        stopButton->setStyleSheet("background-color: rgb(224,224,224)");

        QWidget *w = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(w);
        layout->addWidget(startButton);
        layout->addWidget(stopButton);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(2,1,2,1);    // 左上右下
        w->setLayout(layout);
        t->setCellWidget(row, column, w);

        // 初期状態の設定
        stopButton->setChecked(true);   // Stopが押された状態
        QTableWidgetItem *leftItem = new QTableWidgetItem("STOPPED");
        t->setItem(row, column-1, leftItem);    // 左のセル

        // ボタンが押されたときの処理
        connect(startButton, &QPushButton::toggled, this, [=](bool checked) {
            // なぜかセルのフォーカスが移動するので戻す
            t->setCurrentCell(row, column);

            QString text = "";
            if (checked) {
                text = "RUNNING";
            }
            else {
                text = "STOPPED";
            }
            leftItem->setText(text);
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
