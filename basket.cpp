//============================================================================
// Name        : basket.cpp
// Author      : Gerardo Sanchez
// Version     :
// Copyright   : All Rights Reserved
// Description : Cup - Problem
//============================================================================

#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>

using namespace std;

//configuration is an entity that will represent the configuration
//and the respective result of said configuration
typedef struct configuration{
	int b;
	int n;
	int k;
	int result; //holds the computed number of combinations for this configuration
} configuration;

int basket(bool** cup, const int numBalls, int numCups, const int sizeCup);
void printCups(bool** mCup, int sizeOfArray, int sizeCup);

//will hold all the instances of each configuration
	vector<configuration> memoized;

int main(){

	//file parsing variables
	ifstream inFile;
	inFile.open("input.txt", ios::in);
	assert(inFile.is_open() == true);

	ofstream outFile;
	outFile.open("mOutput.txt", ios::out);
	assert(outFile.is_open() == true);

	int numInstances = 0; //number of instances to run (loop)

	/*
	 	 - Example populating a new configuration when reaching the solution
			configuration* result1 = new configuration();
			result1->b = 1;
			result1->n = 2;
			result1->k = 3;
			memoized.push_back(*result1);
			cout << "Memoized - b: " << memoized[0].b << " n: " << memoized[0].n << " k: " << memoized[0].k <<endl;
	*/

	inFile >> numInstances;

	for(int i = 0; i < numInstances; ++i)
	{
		//begin an instance of the basket problem
		int numCombinations;
		int b = 0, n = 0, k = 0;
		inFile >> b >> n >> k;
		cout << "numBalls[b]: " << b << " numCups[n]: " << n << " sizeCup[k]: " << k << endl;
		bool** cup  = new bool*[n]; //allocate number of cups
		for(int j = 0; j<n; ++j)
		{
			cup[j] = new bool[k];
			for(int y = 0; y < k; ++y){
				cup[j][y] = false; // populate the cups as EMPTY (false)
			}
		}

//		int startIndx = 0, stopIndx = n;
//		printCups(&cup[startIndx], stopIndx - startIndx, k); //(array, sizeOfArray, sizeCup)
		basket(cup, b, n, k);
		//function call here

		//WRITE to File -  result of instance here
		//outFile << "PAYLOAD " << i << endl;
		cout << endl;
	}

	//cout << numInstances;

	inFile.close();
	outFile.close();
	return 0;
}

int findSolution(const int numBalls, const int numCups, const int sizeCup){

	//vector<configuration> memoized is GLOBAL here

	//linear search
	for(int i = 0; i < memoized.size(); ++i){
		if(memoized[i].b == numBalls && memoized[i].n == numCups && memoized[i].k == sizeCup){
			cout << "Found: " << memoized[i].b << " " << memoized[i].n << " " << memoized[i].k << endl;
			return memoized[i].result;
		}
	}
	cout << "No solution found for " << numBalls << " " << numCups << " " << sizeCup << endl;

	return -1;
}

//b = number of BALLS
//n = number of CUPS
//k = size of CUP
int basket(bool** cup, const int numBalls, int numCups, const int sizeCup){
	//pass by value
	int tempNumBalls = numBalls;
	int mResult = -1; //holds the current result
	mResult = findSolution(numBalls, numCups, sizeCup);//FIRST iterate through Memoization vector to find if a solution exists and return that value
	if(mResult != -1){
		return mResult;
	}

	if(numCups == 1){ //only one cup/configuration possible
		return 1;
	}

	//look at the array of cups
	//start at cup 0 (to n)
	//	fill each cup until it is full (true, if filled) then move onto the next cup
	for(int i = 0; i < numCups; ++i)
	{
		for (int j = 0; j < sizeCup; ++j)
		{
			if(tempNumBalls == 0)
			{
				break; //no more balls left
			}
			cup[i][j] = true;
			--tempNumBalls;
		}
	}

	printCups(cup, numCups, sizeCup);
	//	if there are no more balls, this configuration is done do and do recursive call
	//	recursive call on cups[i to n] with tempB balls
	//	if cups is only one, return a ONE
	//

	return 0;
	//return sum + 1;

}

void printCups(bool** mCup, int sizeOfArray, int sizeCup){
	for(int j = 0; j < sizeOfArray; ++j){
		cout << "cup " << j;
		for(int y = 0; y < sizeCup; ++y){
			cout << "[";
			if(mCup[j][y] == true){
				cout << "o]";
			} else{
				cout << " ]";
			}
		}
		cout <<endl;
	}
}
