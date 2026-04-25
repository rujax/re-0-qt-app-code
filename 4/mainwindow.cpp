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
    _feedEdit->setObjectName("feed-edit");
    _feedEdit->setPlaceholderText("请输入 RSS 链接");

    _subscribeButton = new QPushButton("订阅");
    _subscribeButton->setObjectName("subscribe-button");

    QHBoxLayout *subscribeLayout = new QHBoxLayout();
    subscribeLayout->setSpacing(spacing);
    subscribeLayout->setContentsMargins(spacing, spacing, spacing, spacing);
    subscribeLayout->addWidget(_feedEdit);
    subscribeLayout->addWidget(_subscribeButton);

    QFrame *subscribeLine = new QFrame();
    subscribeLine->setObjectName("subscribe-line");
    subscribeLine->setFrameShape(QFrame::HLine);
    subscribeLine->setContentsMargins(spacing + 5, 0, spacing + 5, 0);

    _feedsLayout = new QGridLayout();
    _feedsLayout->setSpacing(spacing);
    _feedsLayout->setContentsMargins(spacing, spacing, spacing, spacing);

    int row = 5;
    int col = 3;

    for (int r = 0; r < row; ++r)
    {
        for (int c = 0; c < col; ++c)
        {
            QLabel *feedLabel = new QLabel(QString::number(r * col + c + 1));
            feedLabel->setProperty("class", "feed-label");
            feedLabel->setAlignment(Qt::AlignCenter);
            feedLabel->setMinimumSize(QSize(240, 180));

            _feedsLayout->addWidget(feedLabel, r, c);
        }
    }

    QWidget *feedsContainer = new QWidget;
    feedsContainer->setObjectName("feeds-container");
    feedsContainer->setLayout(_feedsLayout);

    QScrollArea *feedsScrollArea = new QScrollArea();
    feedsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    feedsScrollArea->setWidgetResizable(true);
    feedsScrollArea->setFrameShape(QFrame::NoFrame);
    feedsScrollArea->setWidget(feedsContainer);

    QFrame *informationLine = new QFrame();
    informationLine->setObjectName("information-line");
    informationLine->setFrameShape(QFrame::HLine);

    QLabel *versionLabel = new QLabel(QString("版本: %1").arg(PROJECT_VERSION));
    versionLabel->setObjectName("version-label");

    QPushButton *configButton = new QPushButton(QIcon(":/config.svg"), "");
    configButton->setObjectName("config-button");
    configButton->setIconSize(QSize(28, 28));

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
    mainLayout->addWidget(subscribeLine);
    mainLayout->addWidget(feedsScrollArea);
    mainLayout->addWidget(informationLine);
    mainLayout->addLayout(informationLayout);

    QWidget *container = new QWidget(this);
    container->setObjectName("container");
    container->setLayout(mainLayout);

    setCentralWidget(container);
}
