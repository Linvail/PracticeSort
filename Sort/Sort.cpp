// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include <functional>   // std::bind
#include <random>

#include "Sort.h"

using namespace std;

namespace Sort
{
	void printResult( const vector<int>& aInput )
	{
		cout << "Result: ";
		for( int i : aInput )
		{
			cout << i << " ";
		}
		cout << endl;
	}

	void bubbleSort( vector<int>& aInput )
	{
		const int lastIndex = aInput.size() - 1;
		bool exchanged = true;

		for( int i = 0; exchanged && i < lastIndex; ++i ) // run 4 times for 5 items
		{
			// If no exchange occurred in one iteration, it means the array has been sorted. We shall not continue.
			exchanged = false;
			// After the 1st outer loop, the greatest item will be moved to end.
			// So, we don't need to count the tail.
			for( int j = 0; j < lastIndex - i; ++j )
			{
				if( aInput[j] > aInput[j + 1] )
				{
					swap( aInput[j], aInput[j + 1] );
					exchanged = true;
				}
			}
		}
	}

	// It works like you pick a poker card from the table one by one, and sort them in hands.
	// We want to do in-place.
	void insertionSort( vector<int>& aInput )
	{
		for( int i = 1; i < aInput.size(); ++i )
		{
			int j = i;
			while( j > 0 && aInput[j] < aInput[j - 1] )
			{
				swap( aInput[j], aInput[j - 1] );
				j--;
			}
		}
	}

	void selectionSort( vector<int>& aInput )
	{
		size_t indexOfSmallest = 0;

		for( size_t i = 0; i < aInput.size(); ++i )
		{
			int smallest = numeric_limits<int>::max();
			for( size_t j = i; j < aInput.size(); ++j )
			{
				if( aInput[j] < smallest )
				{
					smallest = aInput[j];
					indexOfSmallest = j;
				}
			}
			swap( aInput[i], aInput[indexOfSmallest] );
		}
	}

	void shuffle( vector<int>& aInput )
	{
		std::random_device rd;
		std::mt19937 generator( rd() );

		// std::default_random_engine engine(time(nullptr)) <-- time-based seed works badly here.
		// I guess it's because the loop runs very fast, so the time-based seed might be the same in many iterations.

		for( int i = 0; i < aInput.size() - 1; ++i )
		{
			// i <= pos < n
			uniform_int_distribution<int> distribution( i, static_cast<int>( aInput.size() - 1 ) );
			int pos = distribution( generator );

			swap( aInput[i], aInput[pos] );
		}
	}

	void testShuffle()
	{
		vector<int> testData = { 1, 2, 3 };
		vector<int> testData1 = { 1, 2, 3 };
		vector<int> testData2 = { 1, 3, 2 };
		vector<int> testData3 = { 2, 1, 3 };
		vector<int> testData4 = { 2, 3, 1 };
		vector<int> testData5 = { 3, 1, 2 };
		vector<int> testData6 = { 3, 2, 1 };

		vector<int> suffleResult( 6, 0 );

		for( int i = 0; i < 100000; i++ )
		{
			shuffle( testData );

			if( std::equal( testData.begin(), testData.end(), testData1.begin() ) )
			{
				suffleResult[0]++;
			}
			else if( std::equal( testData.begin(), testData.end(), testData2.begin() ) )
			{
				suffleResult[1]++;
			}
			else if( std::equal( testData.begin(), testData.end(), testData3.begin() ) )
			{
				suffleResult[2]++;
			}
			else if( std::equal( testData.begin(), testData.end(), testData4.begin() ) )
			{
				suffleResult[3]++;
			}
			else if( std::equal( testData.begin(), testData.end(), testData5.begin() ) )
			{
				suffleResult[4]++;
			}
			else if( std::equal( testData.begin(), testData.end(), testData6.begin() ) )
			{
				suffleResult[5]++;
			}
		}

		cout << "Result of shuffle..." << endl;
		cout << "Cout of [1 2 3]: " << suffleResult[0] << endl;
		cout << "Cout of [1 3 2]: " << suffleResult[1] << endl;
		cout << "Cout of [2 1 3]: " << suffleResult[2] << endl;
		cout << "Cout of [2 3 1]: " << suffleResult[3] << endl;
		cout << "Cout of [3 1 2]: " << suffleResult[4] << endl;
		cout << "Cout of [3 2 1]: " << suffleResult[5] << endl;

	}

}

