#include "mainwindow.h"

#include <QBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("RSSReader");

    _buildUI();
}

MainWindow::~MainWindow() = default;

void MainWindow::_buildUI()
{
    QLabel *topLabel = new QLabel("top");
    topLabel->setAlignment(Qt::AlignCenter); // 设置文本居中
    topLabel->setStyleSheet("background-color: Aqua; font-size: 24px"); // 设置文本样式

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(topLabel);

    QLabel *middleLabel = new QLabel("middle");
    middleLabel->setAlignment(Qt::AlignCenter);
    middleLabel->setStyleSheet("background-color: Violet; font-size: 24px");

    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(middleLabel);

    QLabel *bottomLabel = new QLabel("bottom");
    bottomLabel->setAlignment(Qt::AlignCenter);
    bottomLabel->setStyleSheet("background-color: SpringGreen; font-size: 24px");

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(bottomLabel);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    mainLayout->addLayout(topLayout, 2);
    mainLayout->addLayout(middleLayout, 9);
    mainLayout->addLayout(bottomLayout, 1);
    
    QWidget *container = new QWidget(this);
    container->setLayout(mainLayout);
    
    setCentralWidget(container);
}
