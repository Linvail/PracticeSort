#include <iostream>
#include <functional>   // std::bind
#include <random>
#include <vector>

#include "Sort.h"
#include "QuickSort.h"

using namespace std;

void testVariousSorting()
{
    std::random_device rd;
    std::mt19937 generator( rd() );

    std::uniform_int_distribution<int> distribution( 0, 50 );
    auto dice = std::bind( distribution, generator );

    vector<int> testData;

    int testSize = 30;
    for( int i = 0; i < testSize; ++i )
    {
        testData.push_back( dice() );
    }

    std::cout << "Bubble sort\n";
    Sort::bubbleSort( testData );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "Insertion sort\n";
    Sort::insertionSort( testData );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "Merge-recursive sort\n";
    Sort::mergeSortRecursive( testData, 0, testData.size() - 1 );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "Merge-iterative sort\n";
    Sort::mergeSort( testData );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "Selection sort\n";
    Sort::selectionSort( testData );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "quickSort_Lomuto\n";
    Sort::quickSort_Lomuto( testData, 0, testData.size() - 1 );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "quickSort_Hoare\n";
    Sort::quickSort_Hoare( testData, 0, testData.size() - 1 );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "quickSort_with_insertionSort\n";
    Sort::quickSort_with_insertionSort( testData, 0, testData.size() - 1 );
    Sort::printResult( testData );

    Sort::shuffle( testData );

    std::cout << "quickSort_std_async\n";
    Sort::quickSort_std_async( testData, 0, testData.size() - 1 );
    Sort::printResult( testData );
}

int main()
{
    //Sort::testShuffle();

    testVariousSorting();

    cout << endl;

    Sort::test_Lomuto_and_Hoare();
}