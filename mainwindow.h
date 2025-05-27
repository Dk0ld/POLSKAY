#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QPushButton"
#include <QMainWindow>
#include <QLineEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton *button;
    QLineEdit *f;
    QLineEdit *xa;
    QLineEdit *xi;

    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void myClick();
};
#endif // MAINWINDOW_H
