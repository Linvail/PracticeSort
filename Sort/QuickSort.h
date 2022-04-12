#pragma once

#include <vector>
using namespace std;

namespace Sort
{

	void quickSort_Lomuto
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	void quickSort_Hoare
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	void quickSort_std_async
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	void quickSort_with_insertionSort
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	void test_Lomuto_and_Hoare();

}