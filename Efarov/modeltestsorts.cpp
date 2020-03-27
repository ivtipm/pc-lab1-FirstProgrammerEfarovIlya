#include "modeltestsorts.h"

ModelTestSorts::ModelTestSorts(QObject *parent)
    :QObject(parent), __count_tests(3), __step(1), __max_size(100), sorter(nullptr)
{
    srand(static_cast<unsigned>(time(nullptr)));
    sorter = new Sorter();
}


void ModelTestSorts::stop_test()
{
    __run = false;
}


void ModelTestSorts::test()
{
    __run = true;
    QVector<double> x, y1, y2, y3, y4, y5, y6, y7;
    double p = 0.0;

    for (int i = 1; i <= __max_size / __step; i++)
    {
        p += (i * __step) / 100.0;
    }

    int k = 0;
    for (int n = __step; n <= __max_size; n += __step)
    {
        QVector<QVector<double>> v;
        int *arr = new int[n];

        x.push_back(n);
        y1.push_back(__middle_time(arr, n, &Sorter::bubleSort));
        y2.push_back(__middle_time(arr, n, &Sorter::selectSort));
        y3.push_back(__middle_time(arr, n, &Sorter::exchangeSort));
        y4.push_back(__middle_time(arr, n, &Sorter::insertSort));
        y5.push_back(__middle_time(arr, n, &Sorter::shellSort));
        y6.push_back(__middle_time(arr, n, &Sorter::combSort));
        y7.push_back(__middle_time(arr, n, &Sorter::quickSort));

        delete [] arr;

        k += n;
        emit progress(static_cast<int>(k / p));

        v.push_back(y1);
        v.push_back(y2);
        v.push_back(y3);
        v.push_back(y4);
        v.push_back(y5);
        v.push_back(y6);
        v.push_back(y7);

        __data.first = x;
        __data.second = v;

        emit progress_data(__data);

        if (!__run)
        {
            break;
        }
    }

    emit finished();
}


void ModelTestSorts::__random_fill_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }
}


double ModelTestSorts::__measure_time(int *arr, int n, void (Sorter::*func_sort)())
{
    struct timeval tv0, tv1;        // time variables
    this->__random_fill_array(arr, n);
    this->sorter->setList(arr, n);
    gettimeofday(&tv0, nullptr);
    (sorter->*func_sort)();
    gettimeofday(&tv1, nullptr);
    return static_cast<double>(tv1.tv_usec - tv0.tv_usec) / 1000000 + static_cast<double>(tv1.tv_sec - tv0.tv_sec);
}



double ModelTestSorts::__middle_time(int *arr, int n, void (Sorter::*func_sort)())
{
    double sum = 0.0;
    for (int i = 0; i < __count_tests; i++)
    {
        sum += __measure_time(arr, n, func_sort);
    }
    return sum / __count_tests;
}


void ModelTestSorts::setCountTests(int c)
{
    if (c > 0)
    {
        __count_tests = c;
    }
    else
    {
        c = 1;
    }
}


int ModelTestSorts::countTests() const
{
    return __count_tests;
}


void ModelTestSorts::setStep(int s)
{
    if (s > 0 && s <= __max_size/2)
    {
        __step = s;
    }
    else
    {
        __step = 1;
    }
}


int ModelTestSorts::step() const
{
    return __step;
}


void ModelTestSorts::setMaxSize(int ms)
{
    if (ms > 0)
    {
        __max_size = ms;
    }
    else
    {
        __max_size = 1;
    }
}


int ModelTestSorts::maxSize() const
{
    return __max_size;
}



QPair<QVector<double>, QVector<QVector<double>>> ModelTestSorts::data() const
{
    return __data;
}


ModelTestSorts::~ModelTestSorts()
{
    delete sorter;
    sorter = nullptr;
}
