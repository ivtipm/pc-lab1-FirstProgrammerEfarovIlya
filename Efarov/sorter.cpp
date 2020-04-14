#include "sorter.h"


Sorter::Sorter(int *arr, int n, bool asc)
    :__asc(asc)
{
    setList(arr, n);
}


void Sorter::setList(int *arr, int n)
{
    __arr = arr;
    __n = n;
}


void Sorter::setDirect(bool asc)
{
    __asc = asc;
}


int Sorter::size() const
{
    return __n;
}


int* Sorter::list() const
{
    return __arr;
}


bool Sorter::direct() const
{
    return __asc;
}


void Sorter::bubleSort()
{
    for (int i = 0; i < __n; i++)
    {
        for (int j = 0; j < __n - i - 1; j++)
        {
            bool flag = __asc ? __arr[j] > __arr[j + 1]: __arr[j] < __arr[j + 1];
            if (flag)
            {
                std::swap(__arr[j], __arr[j + 1]);
            }
        }
    }
}


void Sorter::selectSort()
{
    for (int i = 0; i < __n - 1; i++)
    {
        int ind = i;
        for (int j = i + 1; j < __n; j++)
        {
            bool flag = __asc ? __arr[ind] > __arr[j]: __arr[ind] < __arr[j];
            if (flag)
            {
                ind = j;
            }
        }

        if (ind != i)
        {
            std::swap(__arr[ind], __arr[i]);
        }
    }
}


void Sorter::exchangeSort()
{
    for (int i = 0; i < __n - 1; i++)
    {
        for (int j = i + 1; j < __n; j++)
        {
            bool flag = __asc ? __arr[i] > __arr[j]: __arr[i] < __arr[j];
            if (flag)
            {
                std::swap(__arr[i], __arr[j]);
            }
        }
    }
}


void Sorter::insertSort()
{
    for (int i = 1; i < __n; i++)
    {
        int j = i;
        while ((__asc ? __arr[j - 1] > __arr[j]:
                        __arr[j - 1] < __arr[j]) && j > 0)
        {
            std::swap(__arr[j], __arr[j - 1]);
            j--;
        }
    }
}


void Sorter::shellSort()
{
    for (int k = __n / 2; k > 0; k /= 2)
    {
        for (int i = k; i < __n; i++)
        {
            int j = i;
            while ((__asc ?__arr[j - k] > __arr[j]: __arr[j - k] < __arr[j]) && j - k + 1 > 0)
            {
                std::swap(__arr[j], __arr[j - k]);
                j--;
            }
        }
    }
}


void Sorter::combSort()
{
    double fact = 4 / 3.0;

    for (int i = __n - 1; i > 0; i = int(i / fact))
    {
        for (int j = 0; j < __n - i; j++)
        {
            bool flag = __asc ? __arr[j] > __arr[j + i]: __arr[j] < __arr[j + i];
            if (flag)
            {
                std::swap(__arr[j], __arr[j + i]);
            }
        }
    }


    for (int i = 0; i < __n; i++)
    {
        bool swapped = false;
        for (int j = 0; j < __n - i - 1; j++)
        {
            bool flag = __asc ? __arr[j] > __arr[j + 1] : __arr[j] < __arr[j + 1];
            if (flag)
            {
                std::swap(__arr[j], __arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}


void Sorter::__quickSort(int *arr, int low, int high)
{
    int i = low;
    int j = high - 1;
    int size = high - low;
    if (size > 1)
    {
        int pivot = arr[(low + high)/2];
        while (true)
        {
            while (__asc? arr[i] < pivot: arr[i] > pivot)
            {
                i++;
            }

            while (__asc? arr[j] > pivot: arr[j] < pivot)
            {
                j--;
            }

            if (i >= j)
            {
                break;
            }

            std::swap(arr[i], arr[j]);
            i++;
        }

        __quickSort(arr, low, i);
        __quickSort(arr, i, high);
    }
}


void Sorter::quickSort()
{
    __quickSort(__arr, 0, __n);
}


Sorter::~Sorter()
{
}


void debugOutputList(const Sorter &sorter)
{
    QString ans = "[";
    for (int i = 0; i < sorter.__n; i++)
    {
        ans += QString::number(sorter.__arr[i]);
        if (i != sorter.__n - 1)
        {
            ans += ", ";
        }
    }
    ans += "]";
    qDebug() << ans;
}
