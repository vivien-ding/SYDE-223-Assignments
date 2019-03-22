#include "lab4_priority_queue.hpp"
#include <iostream>

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	capacity = n_capacity;
	size = 0;
	heap = new TaskItem*[capacity+1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {

}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if (size == 0){
		return true;
	}
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	return (size == capacity);
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	cout << "Number of elements: " << size << " Capacity: " << capacity << endl;
	if (size == 0) {
		cout << "No elements";
	} else {
		cout << "Elements: ";
		for (int i = 0; i <= size; i++){
			cout << heap[i] << " ";
		}
	}

}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if (empty()) return TaskItem(-1, "NULL");
	else{
		return *heap[1];
	}
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	
	if (size == capacity) return false;
	
	else if (size == 0){
		heap[1] = new TaskItem(val);
		
	
	} else {
		int i = size + 1;
		heap[i] = new TaskItem(val);
		
		while (i > 1 && heap[i/2]->priority < heap[i]->priority){
			
			TaskItem* temp = heap[i];
			heap[i] = heap[i/2];
			heap[i/2] = temp;
			i /= 2;
		}
	}

	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (size == 0){
		return false;
	} 
	else {
		heap[1] = heap[size];
		size--;
		int i = 1;
		while ((i*2 <= size) && ((heap[i]->priority < heap[2*i]->priority) || (heap[i]->priority < heap[2*i+1]->priority))){
			if (heap[2*i]->priority > heap[2*i+1]->priority && 2*i <= size){
				TaskItem* temp = heap[i];
				heap[i] = heap[2*i];
				heap[2*i] = temp;
				i*=2;
			} 
			else if (heap[2*i]->priority < heap[2*i+1]->priority && 2*i+1 <= size){
				TaskItem* temp = heap[i];
				heap[i] = heap[2*i+1];
				heap[2*i+1] = temp;
				i = 2*i+1;

			} 
		}
		return true;
	}
}
