#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "modeltestsorts.h"
#include <QThread>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_explore_th_clicked();
    void update_graphic();
    void full_set_progress();

    void on_bt_cancel_th_clicked();

    void on_bt_explore_clicked();

private:
    Ui::MainWindow *ui;
    ModelTestSorts *model;
    QThread* th;
    QMutex mt;
};
#endif // MAINWINDOW_H
