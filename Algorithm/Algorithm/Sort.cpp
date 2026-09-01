#include "pch.h"
#include "Sort.h"

void Sort::test()
{
    // -3, 0, 0, 5, 7, 7, 12, 12, 19, 42, 88 가 정상
	int arrs[] = {12, 42, 7, 19, -3, 88, 0, 12, 7, 5, 0};

    //int arrs[] = { 1, 0 , -1};

	//vector<int> arrs;

    auto compare = [](const int& a, const int& b) -> int
        {
            if (a == b)      return 0;
            else if (a < b) return -1;
            else            return 1;
        };


    auto speak = [](const Array<int>& array)->void
        {
            for (int i = 0; i < array.size(); i++)
            {
                printf("%d, ", array[i]);
            }
            printf("\n");
        };

    if(0)
    {
        Array<int> arrs1(arrs);

        Sort::bubbleSort<int>(arrs1, compare);

        speak(arrs1);
    }

    if(0)
    {
        Array<int> cr(arrs);
        Sort::selectionSort<int>(cr, compare);
        speak(cr);
    }

    if (0)
    {
        Array<int> cr(arrs);
        Sort::insertionSort<int>(cr, compare);
        speak(cr);
    }

    if (0)
    {
        Array<int> cr(arrs);
        Sort::shellSort<int>(cr, compare);
        speak(cr);
    }

    if(0)// sehllSort 3h + 1 확인 -> + 1 했던 건 3으로 나눌 때 절사되므로 올라갔을 때의 값들이 내려올 때도 반복되네
    {
        int n = 121;
        int h = 1;
        for (; h < n; h = 3 * h + 1)
        {
            printf("%d, ", h);
        }
        printf("\n");
        for (; h > 0; h /= 3)
        {
            printf("%d, ", h);
        }
    }

    if (0)
    {
        Array<int> cr(arrs);
        Sort::quickSort<int>(cr, compare);
        speak(cr);
    }


    if (0)
    {
        Array<int> cr(arrs);
        Sort::mergeSort<int>(cr, compare);
        speak(cr);
    }

    if (0)
    {
        Array<int> cr(arrs);
        Sort::heapSort<int>(cr, compare);
        speak(cr);
    }

    if (0)
    {
        // 0, 0, 3, 5, 7, 7, 12, 12, 19, 42, 88 가 정상
        Array<int> cr({ 12, 42, 7, 19, 3, 88, 0, 12, 7, 5, 0 });
        Sort::countingSort(cr, 100);
        speak(cr);
    }


    if (1)
    {
        // 0, 0, 4, 53, 71, 143, 317, 887, 1243, 1909, 7031, 420071 가 정상
        Array<int> cr({
                143,
                420071,
                7031,
                1909,
                317,
                887,
                0,
                1243,
                71,
                53,
                4,
                0
            });
        Sort::radixSort(cr);
        speak(cr);
    }
}












