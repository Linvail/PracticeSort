#pragma once

#include <vector>
using namespace std;

namespace Sort
{
	//! Don't use.
	void quickSort_Lomuto
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	//! Faster than quickSort_Lomuto
	void quickSort_Hoare
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	//! Faster than quickSort_Hoare
	void quickSort_with_insertionSort
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	//! Fastest.
	void quickSort_std_async
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	void test_Lomuto_and_Hoare();

}