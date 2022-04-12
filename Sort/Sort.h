#pragma once

#include <vector>

using namespace std;

namespace Sort
{
	void bubbleSort( vector<int>& aInput );

	void insertionSort( vector<int>& aInput );

	void mergeSort
		(
		vector<int>& aInput
		);

	void mergeSortRecursive
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	void heapSort( vector<int>& aInput );

	void selectionSort( vector<int>& aInput );

	// Utility

	void printResult( const vector<int>& aInput );

	void shuffle( vector<int>& aInput );

	void testShuffle();


}
