/*
Optimize the approach from geeksforgeeks

Maximum size rectangle binary sub-matrix with all 1s
Given a binary matrix, find the maximum size rectangle binary-sub-matrix with all 1’s.
Input:
0 1 1 0
1 1 1 1
1 1 1 1
1 1 0 0
Output:
8
*/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

#define R 4 
#define C 4 
int maxHist(int rows[])
{
	// Create an empty stack. The stack holds indexes of 
	// hist[] array/ The bars stored in stack are always 
	// in increasing order of their heights. 
	stack<int> result;

	int top_val; // Top of stack 

	int max_area = 0; // Initialize max area in current 
	// row (or histogram) 

	int area = 0; // Initialize area with current top 

	vector<int> row;
	for (int i=0;i<C;i++)
		row.push_back(rows[i]);
	row.push_back(0);

	// Run through all bars of given histogram (or row) 
	int i = 0;
	while (i < C+1) {
		// If this bar is higher than the bar on top stack, 
		// push it to stack 
		if (result.empty() || row[result.top()] <= row[i])
			result.push(i++);

		else {
			// If this bar is lower than top of stack, then 
			// calculate area of rectangle with stack top as 
			// the smallest (or minimum height) bar. 'i' is 
			// 'right index' for the top and element before 
			// top in stack is 'left index' 
			top_val = row[result.top()];
			result.pop();
			area = top_val * (result.empty()? i: i-result.top()-1);			
			max_area = max(area, max_area);
		}
	}	
	return max_area;
}

int maxRectangle(int A[][C])
{
	// Calculate area for first row and initialize it as 
	// result 
	int result = maxHist(A[0]);

	// iterate over row to find maximum rectangular area 
	// considering each row as histogram 
	for (int i = 1; i < R; i++) {

		for (int j = 0; j < C; j++)

			// if A[i][j] is 1 then add A[i -1][j] 
			if (A[i][j])
				A[i][j] += A[i - 1][j];

		// Update result if area with current row (as last row) 
		// of rectangle) is more 
		result = max(result, maxHist(A[i]));
	}

	return result;
}
int main()
{
	int A[][C] = {
		{ 0, 1, 1, 0 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 0, 0 },
	};

	cout << "Area of maximum rectangle is "
		<< maxRectangle(A);

	return 0;
}
