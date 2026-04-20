#include "mainwindow.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>

#include "project.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("RSSReader");

    _buildUI();
}

MainWindow::~MainWindow() = default;

void MainWindow::_buildUI()
{
    int spacing = 20;

    _feedEdit = new QLineEdit();
    _feedEdit->setPlaceholderText("请输入 RSS 链接");

    _subscribeButton = new QPushButton("订阅");

    QHBoxLayout *subscribeLayout = new QHBoxLayout();
    subscribeLayout->setSpacing(spacing);
    subscribeLayout->setContentsMargins(spacing, spacing, spacing, spacing / 2);
    subscribeLayout->addWidget(_feedEdit);
    subscribeLayout->addWidget(_subscribeButton);

    _feedsLayout = new QGridLayout();
    _feedsLayout->setSpacing(spacing);
    _feedsLayout->setContentsMargins(spacing, spacing / 2, spacing, 0);

    int row = 5;
    int col = 3;

    for (int r = 0; r < row; ++r)
    {
        for (int c = 0; c < col; ++c)
        {
            QLabel *feedLabel = new QLabel(QString::number(r * col + c + 1));
            feedLabel->setAlignment(Qt::AlignCenter);
            feedLabel->setStyleSheet("background-color: Violet; font-size: 24px");
            feedLabel->setMinimumSize(QSize(240, 180));

            _feedsLayout->addWidget(feedLabel, r, c);
        }
    }

    QWidget *feedsContainer = new QWidget;
    feedsContainer->setLayout(_feedsLayout);

    QScrollArea *feedsScrollArea = new QScrollArea();
    feedsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    feedsScrollArea->setFrameShape(QFrame::NoFrame);
    feedsScrollArea->setWidget(feedsContainer);

    QLabel *versionLabel = new QLabel(QString("版本: %1").arg(PROJECT_VERSION));
    versionLabel->setStyleSheet("font-size: 14px");

    QPushButton *configButton = new QPushButton(QIcon(":/config.svg"), "");
    configButton->setIconSize(QSize(24, 24));

    QHBoxLayout *informationLayout = new QHBoxLayout();
    informationLayout->setSpacing(spacing);
    informationLayout->setContentsMargins(spacing / 2, spacing / 2, spacing / 2, spacing / 2);
    informationLayout->addWidget(versionLabel);
    informationLayout->addStretch();
    informationLayout->addWidget(configButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addLayout(subscribeLayout);
    mainLayout->addWidget(feedsScrollArea);
    mainLayout->addLayout(informationLayout);

    QWidget *container = new QWidget(this);
    container->setLayout(mainLayout);

    setCentralWidget(container);
}
