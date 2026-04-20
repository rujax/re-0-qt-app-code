#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QPushButton;
class QGridLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QLineEdit *_feedEdit;
    QPushButton *_subscribeButton;
    QGridLayout *_feedsLayout;

    void _buildUI();
};

#endif // MAINWINDOW_H
