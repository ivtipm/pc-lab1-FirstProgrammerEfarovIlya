#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    th = new QThread(this);
    model = new ModelTestSorts();

    model->setMutex(&mt);

    connect(th, &QThread::started, model, &ModelTestSorts::test);
    connect(model, &ModelTestSorts::finished, th, &QThread::quit);
    connect(model, SIGNAL(updated_data()),
            this, SLOT(update_graphic()));

    connect(model, &ModelTestSorts::progress, ui->progressBar, &QProgressBar::setValue);
    connect(model, SIGNAL(finished()), this, SLOT(full_set_progress()));
}

MainWindow::~MainWindow()
{
    delete th;
    delete model;
    delete ui;
}


void MainWindow::full_set_progress()
{
    ui->progressBar->setValue(100);
    ui->statusbar->showMessage("процесс завершён");
}


void MainWindow::update_graphic()
{
    mt.lock();
    double a = 0;
    double b = model->maxSize() + 100;
    ui->graphic_widget->clearGraphs();

    ui->graphic_widget->addGraph();
    ui->graphic_widget->addGraph();
    ui->graphic_widget->addGraph();
    ui->graphic_widget->addGraph();
    ui->graphic_widget->addGraph();
    ui->graphic_widget->addGraph();
    ui->graphic_widget->addGraph();

    ui->graphic_widget->graph(0)->setData(model->data().first, model->data().second[0]);

    ui->graphic_widget->graph(0)->setPen(QPen(Qt::red));

    ui->graphic_widget->graph(0)->setName("пузырьковая");
\


    ui->graphic_widget->graph(1)->setData(model->data().first, model->data().second[1]);

    ui->graphic_widget->graph(1)->setPen(QPen(Qt::yellow));

    ui->graphic_widget->graph(1)->setName("выбором");



    ui->graphic_widget->graph(2)->setData(model->data().first, model->data().second[2]);

    ui->graphic_widget->graph(2)->setPen(QPen(Qt::gray));

    ui->graphic_widget->graph(2)->setName("обменом");


    ui->graphic_widget->graph(3)->setData(model->data().first, model->data().second[3]);

    ui->graphic_widget->graph(3)->setPen(QPen(Qt::blue));

    ui->graphic_widget->graph(3)->setName("вставками");



    ui->graphic_widget->graph(4)->setData(model->data().first, model->data().second[4]);

    ui->graphic_widget->graph(4)->setPen(QPen(Qt::green));

    ui->graphic_widget->graph(4)->setName("шелла");



    ui->graphic_widget->graph(5)->setData(model->data().first, model->data().second[5]);

    ui->graphic_widget->graph(5)->setPen(QPen(Qt::cyan));

    ui->graphic_widget->graph(5)->setName("расчёской");



    ui->graphic_widget->graph(6)->setData(model->data().first, model->data().second[6]);

    ui->graphic_widget->graph(6)->setPen(QPen(Qt::magenta));

    ui->graphic_widget->graph(6)->setName("быстрая");



    ui->graphic_widget->axisRect()->setupFullAxesBox();

    ui->graphic_widget->legend->setVisible(true);

    ui->graphic_widget->legend->setBrush(QBrush(QColor(255,255,255,150)));

    ui->graphic_widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphic_widget->xAxis->setLabel("n");
    ui->graphic_widget->yAxis->setLabel("t");

    ui->graphic_widget->xAxis->setRange(a, b);

    double minY = model->data().second[0][0], maxY = model->data().second[0][0];
    for (int i = 0; i < model->data().second.size(); i++)
    {
        for (int j = 1; j < model->data().second[i].size(); j++)
        {
            if (model->data().second[i][j]< minY)
            {
                minY = model->data().second[i][j];
            }

            if (model->data().second[i][j] > maxY)
            {
                maxY = model->data().second[i][j];
            }
        }
    }

    ui->graphic_widget->yAxis->setRange(minY, maxY);

    ui->graphic_widget->replot();
    mt.unlock();
}


void MainWindow::on_bt_explore_th_clicked()
{
    ui->statusbar->showMessage("обработка данных...");
    model->setMaxSize(ui->spb_count->value());
    model->setStep(ui->spb_d->value());
    model->setCountTests(ui->spb_ctests->value());
    model->moveToThread(th);
    th->start();
}

void MainWindow::on_bt_cancel_th_clicked()
{
    model->stop_test();
}

void MainWindow::on_bt_explore_clicked()
{
    ui->statusbar->showMessage("обработка данных...");
    model->setMaxSize(ui->spb_count->value());
    model->setStep(ui->spb_d->value());
    model->setCountTests(ui->spb_ctests->value());
    model->test();
}
