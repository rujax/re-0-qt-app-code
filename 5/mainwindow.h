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
    // UI
    QLineEdit *_feedEdit;
    QPushButton *_subscribeButton;
    QGridLayout *_feedsLayout;

    // Methods
    void _buildUI();
    void _connectSlots();

private slots:
    void _subscribeButtonClicked();
};

#endif // MAINWINDOW_H
