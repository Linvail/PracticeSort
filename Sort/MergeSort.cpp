#include <iostream>
#include <vector>

#include "Sort.h"

using namespace std;

namespace Sort
{
// There are two ways to do merge sort
	// a. top-down, recursive way.
	// b. bottom-top, iterative way.
	void mergeSort
		(
		vector<int>& aInput
		)
	{
		// The idea is to merge 2 adjacent items into a segment, which contains 1~2 items. We will have roughly n/2 segments.
		// Then, merge two smallest segments into a bigger segment, which contains 2~3 items. Then, continue until the segment has the same as the input.
		const int len = aInput.size();
		vector<int> temporal( len );

		int segSize = 1;
		for( ; segSize < len; segSize += segSize )
		{
			// segSize = 1. [1] [2] [3] [4] [0]
			// segSize = 2. [1, 2] [3, 4] [0]
			// segSize = 3. [1, 2, 3, 4] [0]
			for( int start = 0; start < len; start += ( segSize + segSize ) )
			{
				int low = start, mid = min( start + segSize, len ), high = min( start + segSize + segSize, len );
				int k = low;
				int start1 = low, end1 = mid;
				int start2 = mid, end2 = high;
				while( start1 < end1 && start2 < end2 )
				{
					temporal[k++] = aInput[start1] < aInput[start2] ? aInput[start1++] : aInput[start2++];
				}
				while( start1 < end1 )
				{
					temporal[k++] = aInput[start1++];
				}
				while( start2 < end2 )
				{
					temporal[k++] = aInput[start2++];
				}
			}

			// After swap, the values in temporal are useless. The latest results are in aInput.
			swap( aInput, temporal );
		}

	}

	// Utility for mergeSortRecursive.
	void merge
		(
		vector<int>& aInput,
		int aBegin,
		int aMid,
		int aEnd
		)
	{
		// Note that the vector's range constructor doesn't copy the item at 'last' iterator.
		// So, we need to +1 for the 2nd parameter.
		vector<int> leftSub( aInput.begin() + aBegin, aInput.begin() + aMid + 1 );
		vector<int> rightSub( aInput.begin() + aMid + 1, aInput.begin() + aEnd + 1 );

		// Add max number to the end for comparison.
		leftSub.push_back( numeric_limits<int>::max() );
		rightSub.push_back( numeric_limits<int>::max() );

		int leftIdx = 0;
		int rightIdx = 0;

		// Now we need to fill aInput with correct value in the range.
		for( int i = aBegin; i <= aEnd; ++i )
		{
			if( leftSub[leftIdx] < rightSub[rightIdx] )
			{
				aInput[i] = leftSub[leftIdx];
				leftIdx++;
			}
			else
			{
				aInput[i] = rightSub[rightIdx];
				rightIdx++;
			}
		}

	}

	void mergeSortRecursive
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

		int mid = aBegin + ( aEnd - aBegin ) / 2;

		mergeSortRecursive( aInput, aBegin, mid );

		mergeSortRecursive( aInput, mid + 1, aEnd );

		merge( aInput, aBegin, mid, aEnd );
	}
}