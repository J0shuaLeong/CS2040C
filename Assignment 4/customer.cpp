#include "customer.h"
#include "heap.h"
#include <iostream>
using namespace std;
int comparisonWay = 0; // 0 for arrival time, 1 for processing time


bool Customer::operator>(const Customer& c) {
	return comparisonWay ? processing_time < c.processing_time : arrival_time < c.arrival_time; // a customer is "greater" if his time is shorter
};

bool Customer::operator==(const Customer& c) {
	return comparisonWay ? processing_time = c.processing_time : arrival_time < c.arrival_time; // a customer is "equal" if his time is shorter
};

bool Customer::operator<(const Customer& c) {
	return comparisonWay ? processing_time > c.processing_time : arrival_time < c.arrival_time; // a customer is "less" if his time is shorter
};

void customerQueueTest(int n_cust) {
	int current_time = 0;
	int totalWaitingTime = 0;
	int i;
	int WT = 0; // waiting time for each customer
	int busyStatus; //if > 0, counter is serving someone

	Heap<Customer> queue;

	Customer* custList = new Customer[n_cust];
	cout << endl << endl << "Setup" << endl;
	cout << "List of customers and their arrival and processing times" << endl;
	for (i = 0; i<n_cust; i++)
	{
		custList[i].setAT(i);
		custList[i].setPT((n_cust - i) % (n_cust / 2) + 1 + (i % 2)*(n_cust / 2));
		cout << "Customer " << i << " will arrive at time " << custList[i].AT() << " with PT=" << custList[i].PT() << endl;
	}
	cout << endl;


	for (int round = 0; round<2; round++) {
		// you may need a big modification within this for-loop
		cout << endl << endl;
		cout << "Test Round " << round + 1 << endl;
		cout << (round == 0 ? "First come first serve" : "Customer with the least PT served first") << endl;
		comparisonWay = round;
		current_time = 0;
		totalWaitingTime = 0;
		busyStatus = 0;
		queue.insert(custList[0]);

		cout << "Customer arrives at time " << custList[0].AT() << " with PT=" << custList[0].PT() << endl;

		while (!queue.empty()) {

			if (busyStatus == 0 && queue.peekMax().AT() == current_time) { //peekMax() to receive max element in the queue
				cout << "Customer arrives when no one is waiting" << endl;
			}
			if (busyStatus == 0) { //no one queueing
				Customer c = queue.extractMax(); 
				WT = current_time - c.AT(); //calc waiting time 
				busyStatus = c.PT() - 1; //minus one for time spent on serving customer
				cout << "Customer is served at time " << current_time << " with AT=" << c.AT() << " and PT=" << c.PT() << " after waiting for "
					<< WT << " min." << endl;
				totalWaitingTime += WT;
			}
			else {
				busyStatus--; //serving someone
			}
			current_time++;

			if (current_time < n_cust) {
				queue.insert(custList[current_time]);
				cout << "Customer arrives at time " << custList[current_time].AT() << " with PT=" << custList[current_time].PT() << endl;
			}
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;

	}


	delete[] custList;
}
