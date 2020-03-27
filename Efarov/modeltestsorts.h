#ifndef MODELTESTSORTS_H
#define MODELTESTSORTS_H

#include <QObject>
#include "sorter.h"
#include <ctime>
#include <sys/time.h>
#include <QVector>
#include <QPair>
#include <QMutex>


using VD = QVector<double>;
using VVD = QVector<VD>;
using PVDVVD = QPair<VD, VVD>;


class ModelTestSorts: public QObject
{
    Q_OBJECT

private:
    int __count_tests;
    int __step;
    int __max_size;                                     // max size testing array
    Sorter *sorter;
    QPair<QVector<double>, QVector<QVector<double>>> __data;
    bool __run = false;

    QMutex* __mutex;

    void __random_fill_array(int *arr, int n);
    double __measure_time(int *arr, int n, void (Sorter::*func_sort)());
    double __middle_time(int *arr, int n, void (Sorter::*func_sort)());

public:
    explicit ModelTestSorts(QObject *parent = nullptr);

    void setCountTests(int c);
    int countTests() const;

    void setStep(int s);
    int step() const;

    void setMaxSize(int ms);
    int maxSize() const;

    void setMutex(QMutex* mutex);

    QPair<QVector<double>, QVector<QVector<double>>>& data();

    ~ModelTestSorts();

public slots:
    void test();
    void stop_test();

signals:
    void progress(int val);
    void updated_data();
    void finished();
};

#endif // MODELTESTSORTS_H
