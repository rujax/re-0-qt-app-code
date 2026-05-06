#include "mainwindow.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlStreamReader>

#include "project.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("RSSReader");

    _manager = new QNetworkAccessManager(this);

    _buildUI();
    _connectSlots();
}

// Destructor
MainWindow::~MainWindow()
{
    _manager->disconnect();
    _manager->deleteLater();
    _manager = nullptr;
}

// Private Methods
void MainWindow::_buildUI()
{
    int spacing = 20;

    _feedEdit = new QLineEdit();
    _feedEdit->setObjectName("feed-edit");
    _feedEdit->setPlaceholderText("请输入 RSS 链接");

    connect(_feedEdit, &QLineEdit::textChanged, [](const QString &text) {
        qDebug() << "text:" << text;
    });

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

void MainWindow::_connectSlots()
{
    connect(_subscribeButton, &QPushButton::clicked, this, &MainWindow::_subscribeButtonClicked);
    connect(_manager, &QNetworkAccessManager::finished, this, &MainWindow::_requestFinished);
}

// Private Slots
void MainWindow::_subscribeButtonClicked()
{
    qDebug() << "feed link text:" << _feedEdit->text();

    QNetworkRequest request(QUrl(_feedEdit->text()));
    request.setRawHeader("Accept", "application/xml");

    _manager->get(request);
}

void MainWindow::_requestFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "request error:" << reply->errorString();

        reply->disconnect();
        reply->deleteLater();
        reply = nullptr;

        return;
    }

    QByteArray content = reply->readAll();
    QXmlStreamReader reader(content);
    QString name;
    QString indent = "  ";

    while (!reader.atEnd()) {
        reader.readNext();

        if (reader.isStartElement())
        {
            name = reader.name().toString();
            QString lowerName = name.toLower();

            if (lowerName == "item")
            {
                indent = "    ";
                qDebug() << "\n  item: {";
            }
            else if (lowerName == "channel")
            {
                indent = "  ";
                qDebug() << "\nchannel: {";
            }
            else if (lowerName == "rss")
            {
                qDebug() << "rss version:" << reader.attributes().value("version").toString();
            }
        } else if (reader.isEndElement())
        {
            QString lowerName = reader.name().toString().toLower();

            if (lowerName == "item") qDebug() << "  }";
            else if (lowerName == "channel") qDebug() << "}";
        } else if (reader.isCharacters() && !reader.isWhitespace())
        {
            QDebug debug = qDebug();
            debug.noquote() << QString("%1%2:").arg(indent, name);
            debug.quote() << reader.text().toString();
        }
    }

    if (reader.hasError())
    {
        qDebug() << "parse xml error:" << reader.errorString();
    }

    reply->disconnect();
    reply->deleteLater();
    reply = nullptr;
}
