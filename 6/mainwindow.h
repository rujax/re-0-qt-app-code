#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QPushButton;
class QGridLayout;
class QNetworkAccessManager;
class QNetworkReply;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    // Tool
    QNetworkAccessManager *_manager;

    // UI
    QLineEdit *_feedEdit;
    QPushButton *_subscribeButton;
    QGridLayout *_feedsLayout;

    // Methods
    void _buildUI();
    void _connectSlots();

private slots:
    void _subscribeButtonClicked();
    void _requestFinished(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
