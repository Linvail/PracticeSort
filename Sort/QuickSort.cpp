#include <iostream>
#include <vector>

#include <functional>   // std::bind
#include <random>

#include <chrono>
#include <future>

#include "QuickSort.h"
#include "Sort.h"

using namespace std;

namespace Sort
{
	//! Divide the input into two partitions, the left partition is less than the pivot,
	//! the right partition is greater than the pivot.
	//! Use Lomuto partition scheme.
	//!
	//! @return The index of the pivot.
	int partition_Lomuto
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		)
	{
		// Just choose the last item as the pivot.
		const int pivot = aInput[aEnd];
		int i = aBegin - 1;

		for( int j = aBegin; j < aEnd; ++j )
		{
			// Using < or <= is tricky. It seems to take more time when using <= and there are many equal items.
			// 1 4 5 4 4 4 4 5 6 7 4
			if( aInput[j] < pivot )
			{
				i++;
				swap( aInput[j], aInput[i] );
			}
		}

		// Put the pviot in where it should be.
		i++;
		swap( aInput[i], aInput[aEnd] );

		return i;
	}

	//! Divide the input into two partitions, the left partition is less than the pivot,
	//! the right partition is greater than the pivot.
	//! Use Hoare partition scheme.
	//!
	//! @return The index of the last element on the smaller side.
	int partition_Hoare
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		)
	{
		// Pick the pivot. There are many ways. Here we just pick the middle one.
		const size_t midIdx = aBegin + ( aEnd - aBegin ) / 2; // Equal to (aBegin + aEnd) / 2 but won't overflow when aBegin/aEnd are very very big.
		const int pivot = aInput[midIdx];

		// Note that they are out of bound.
		int i = aBegin - 1;
		int j = aEnd + 1;

		while( true )
		{
			do
			{
				i++;
			} while( aInput[i] < pivot );

			do
			{
				j--;
			} while( aInput[j] > pivot );

			if( i >= j )
			{
				// aInput[0 ~ j] are all less than pivot. aInput[j + 1 ~ aEnd] are all greater than pivot.
				return j;
			}

			swap( aInput[i], aInput[j] );
		}
	}


	//! Quick sort is also a type of divide and conquer algorithm
	//! Pick a pivot and make two partitions.
	//! Recursively do quickSort on the two partitions.
	//! Poor choice of pivot or poor handling of equality might result in worst cases
	//!
	//! This causes stack overflow when there are many identical items.
	void quickSort_Lomuto
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		)
	{
		if( aBegin >= aEnd )
		{
			return;
		}

		int pivotIdx = partition_Lomuto( aInput, aBegin, aEnd );

		// Note that the pivot is not included.
		quickSort_Lomuto( aInput, aBegin, pivotIdx - 1 );
		quickSort_Lomuto( aInput, pivotIdx + 1, aEnd );
	}

	//! Hoare is apparently faster than Lomuto, especially when there are many identical items.
	void quickSort_Hoare
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		)
	{
		if( aBegin < aEnd )
		{
			int pivotIdx = partition_Hoare( aInput, aBegin, aEnd );

			quickSort_Hoare( aInput, aBegin, pivotIdx ); // Note that the pivot is included.
			quickSort_Hoare( aInput, pivotIdx + 1, aEnd );
		}
	}

	//! Use std::async for the recursive calls.
	void quickSort_std_async
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		)
	{
		if( aBegin < aEnd )
		{
			int pivotIdx = partition_Hoare( aInput, aBegin, aEnd );

			auto policy = std::launch::async;
			auto f1 = std::async( policy, [&aInput, aBegin, pivotIdx] { quickSort_Hoare( aInput, aBegin, pivotIdx ); } );
			auto f2 = std::async( policy, [&aInput, pivotIdx, aEnd] { quickSort_Hoare( aInput, pivotIdx + 1, aEnd ); } );
			f1.wait();
			f2.wait();
		}
	}

	//! Based on quickSort_Hoare. When count is less than 8, just do the insertion sort.
	void quickSort_with_insertionSort
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		)
	{
		if( aBegin < aEnd )
		{
			if( aEnd - aBegin > 8 )
			{
				int pivotIdx = partition_Hoare( aInput, aBegin, aEnd );

				quickSort_Hoare( aInput, aBegin, pivotIdx ); // Note that the pivot is included.
				quickSort_Hoare( aInput, pivotIdx + 1, aEnd );
			}
			else
			{
				insertionSort( aInput );
			}
		}
	}

	void test_Lomuto_and_Hoare()
	{
		std::random_device rd;
		std::mt19937 generator( rd() );

		std::uniform_int_distribution<int> distribution( 0, 2000000 );
		auto dice = std::bind( distribution, generator );

		vector<int> testData( 30000, 100 );

		using std::chrono::high_resolution_clock;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::chrono::milliseconds;

		auto t1 = high_resolution_clock::now();
		// quickSort_Lomuto would cause stack overflow for testData.
		// On the other hand, quickSort_Hoare works fine.
		quickSort_Hoare( testData, 0, testData.size() - 1 );
		auto t2 = high_resolution_clock::now();

		// Getting number of milliseconds as an integer.
		auto ms_int = duration_cast<milliseconds>( t2 - t1 );
		std::cout << "quickSort_Hoare: " << ms_int.count() << "ms\n";

		t1 = high_resolution_clock::now();
		//quickSort_Lomuto( testData, 0, testData.size() - 1 );
		quickSort_with_insertionSort( testData, 0, testData.size() - 1 );
		t2 = high_resolution_clock::now();
		ms_int = duration_cast<milliseconds>( t2 - t1 );
		//std::cout << "quickSort_Lomuto: " << ms_int.count() << "ms\n";
		std::cout << "quickSort_with_insertionSort: " << ms_int.count() << "ms\n";
		std::cout << "quickSort_Lomuto easily causes stack overflow when there are many identical items..\nOn the other hand, quickSort_Hoare works fine.\n";

		cout << endl;
		testData.clear();

		int testSize = 3000000;
		for( int i = 0; i < testSize; ++i )
		{
			testData.push_back( dice() );
		}
		vector<int> testData2( testData );
		vector<int> testData3( testData );

		t1 = high_resolution_clock::now();
		quickSort_Hoare( testData, 0, testData.size() - 1 );
		t2 = high_resolution_clock::now();
		ms_int = duration_cast<milliseconds>( t2 - t1 );
		std::cout << "quickSort_Hoare: " << ms_int.count() << "ms\n";

		t1 = high_resolution_clock::now();
		//quickSort_with_insertionSort( testData2, 0, testData2.size() - 1 );
		quickSort_std_async( testData2, 0, testData2.size() - 1 );
		t2 = high_resolution_clock::now();
		ms_int = duration_cast<milliseconds>( t2 - t1 );
		//std::cout << "quickSort_with_insertionSort: " << ms_int.count() << "ms\n";
		std::cout << "quickSort_std_async: " << ms_int.count() << "ms\n";

		t1 = high_resolution_clock::now();
		//quickSort_Lomuto( testData3, 0, testData3.size() - 1 );
		std:sort( testData3.begin(), testData3.end() );
		t2 = high_resolution_clock::now();
		ms_int = duration_cast<milliseconds>( t2 - t1 );
		std::cout << "std:sort: " << ms_int.count() << "ms\n";

		cout << endl;

		#if 0
			cout << "Test data: ";
			testData = { 1, 4, 5, 4, 4, 4, 6, 7, 4 };
			testData2 = testData;
			printResult( testData );

			quickSort_Hoare( testData, 0, testData.size() - 1 );
			quickSort_Lomuto( testData2, 0, testData2.size() - 1 );

			printResult( testData );
			printResult( testData2 );
		#endif



	}

} // namespace Sort