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

int basket(int* cup, const int numBalls, const int numCups, const int sizeCup);
void printCups(int* mCup, int sizeOfArray);

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
		int* cup = new int[n]; //initializes each integer to 0 by default

		//int startIndx = 0, stopIndx = n;
		//printCups(&cup[startIndx], stopIndx - startIndx, k); //(array, sizeOfArray, sizeCup)
		numCombinations = basket(cup, b, n, k);
		//numCombinations = basket(cup, 3, 3, 2);
		//function call here

		//WRITE to File -  result of instance here
		outFile << "Itr: " << i << " " << numCombinations << endl;
		cout << "Itr: " << numCombinations << endl;
		cout << endl;
	}

	inFile.close();
	outFile.close();
	return 0;
}

int findSolution(const int numBalls, const int numCups, const int sizeCup){

	//vector<configuration> memoized is GLOBAL here

	//linear search
	for(unsigned int i = 0; i < memoized.size(); ++i){
		if(memoized[i].b == numBalls && memoized[i].n == numCups && memoized[i].k == sizeCup){
			cout << "Found: " << memoized[i].b << " " << memoized[i].n << " " << memoized[i].k << endl;
			return memoized[i].result;
		}
	}
	cout << "No solution found for " << numBalls << " " << numCups << " " << sizeCup << endl;

	return 0;
}

//b = number of BALLS
//n = number of CUPS
//k = size of CUP
int basket(int* cup, const int numBalls, const int numCups, const int sizeCup){
	//integer Array pass by REFERENCE
	*cup = 0; //ensure that the current cup is set to zero for evaluating configurations

	unsigned int ballsAdded = 0;
	int ballsLeft = numBalls - ballsAdded;
	unsigned int numCupsLeft = numCups - 1; //not including the current cup
	int slotsLeft = numCupsLeft * sizeCup;
	int mResult = 0; //holds the current result

	//mResult = findSolution(numBalls, numCups, sizeCup);//FIRST iterate through Memoization vector to find if a solution exists and return that value
	if(mResult != 0){
		return mResult;
	}

	//base case - HERE
	if(numBalls == 0 || (numCupsLeft == 0 && numBalls <= sizeCup)){
		//cout << "Base Case. ++1" << endl;
		return 1;
	}

	while(*cup < sizeCup){ //while the cup isn't full

		//determine the amount of balls left for subsequent cups
		ballsLeft = numBalls - ballsAdded;

		if(numCups > 1) //more than a cup, determine range of slots available
		{
			if(ballsLeft <= slotsLeft) //will the subsequent cups fit the remaining balls, in this configuration?
			{
				//we can fit the balls in subsequent calls
//				cout << "numCups left: " << numCupsLeft
//						<< ", (slots) left: " << slotsLeft
//						<< ", numBalls: " << numBalls
//						<< ", balls used: " << ballsAdded
//						<< ", balls left: " << ballsLeft
//
//						<< "\nThe balls will fit in subsequent calls." << endl;

				//add the ball to the current cup/slot and then make recursive call
				*cup = ballsAdded;
				//printCups(cup, numCups);

				mResult += basket(++cup, ballsLeft, numCupsLeft, sizeCup); //RECURSION

				//after recursive tree completes!
				--cup; //Change scope of current cup

				//prevent cup overflow and prevent imaginary balls
				if(*cup < sizeCup && ballsLeft != 0){
					++ballsAdded;
				}else{
					//cup is full, check if we have a cup left, meaning the possible combos is only one and has already been determined
					if(ballsLeft < slotsLeft){
						//cout << "mResult: " << mResult << endl;
						return mResult; //traversal done
					}else{
						mResult += basket(++cup, ballsLeft, numCupsLeft, sizeCup); //keep going down the tree of cups
					}
				}

			}else{
//				cout << "Balls will not fit in subsequent calls with this configuration."
//						<< " One more ball added, trying again. " << endl;
				++ballsAdded;
				*cup = ballsAdded; //add the ball to the current cup, since it won't fit later on
			}
		}
	}

	return mResult;
}

void printCups(int* mCup, int sizeOfArray)
{
	for(int j = 0; j < sizeOfArray; ++j)
	{
		cout << j<< ": [" << mCup[j] << "] ";
	}
	cout << endl;
}
