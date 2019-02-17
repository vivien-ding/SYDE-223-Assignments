#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

// EXPLICIT CONSTRUCTOR AND DESTRUCTOR
// PURPOSE: Creates a new empty DronesManager
DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {
}

// PURPOSE: Destroys this instance and frees up all dynamically allocated memory
DronesManager::~DronesManager() {
	// delete prev;
	// prev = NULL;
	// delete next;
	// next = NULL;
	// delete first;
	// first = NULL;
	// delete last;
	// last = NULL;

	DroneRecord* temp = first;
	while(temp!=NULL){
		DroneRecord* cur = temp;
		temp = temp->next;
		delete cur;
	}
}

// PURPOSE: Comparison operator to compare two DroneRecord instances
bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool are_equal = rhs.droneID == lhs.droneID;
		are_equal = are_equal && (rhs.range == lhs.range);
		are_equal = are_equal && (rhs.yearBought == lhs.yearBought);
		are_equal = are_equal && (rhs.droneType == lhs.droneType);
		are_equal = are_equal && (rhs.manufacturer == lhs.manufacturer);
		are_equal = are_equal && (rhs.description == lhs.description);
		are_equal = are_equal && (rhs.batteryType == lhs.batteryType);
		return are_equal;
}

// ACCESSORS
// PURPOSE: Returns the number of elements in the list
unsigned int DronesManager::get_size() const {
	int count = 0;
	DroneRecord* p = first;

	while (p != NULL){
		++count;
		p = p->next;
	}

	return count;
}

// PURPOSE: Checks if the list is empty; returns true if the list is empty, false otherwise
bool DronesManager::empty() const {
	if (first == NULL && last == NULL){
		return true;
	}
	return false;
}

// PURPOSE: Returns the value at the given index in the list
// if index is invalid, returns last element; if the list is empty, returns DroneRecord(0)
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	int count = 0;
	DroneRecord* p = first;

	if (p == NULL){
		return DroneRecord(0);
	}

	while (p != NULL){
		count++;
		if (count == index){
			return p->DroneRecord;
		}
		p = p->next;
	}
	return last->DroneRecord;

	// need to figure out how to access DroneRecord elements properly (https://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/)
}

// PURPOSE: Searches for the given value, and returns the index of this value if found	
// if not found, returns the size of the list; if the list is empty, returns 0
unsigned int DronesManager::search(DroneRecord value) const {
	int index = 0;
	DroneRecord* p = first;

	if (p == NULL){
		return 0;
	}

	while (p != NULL){
		index++;
		if (p->DroneRecord == value){
			return index;
		}  // still not sure if thats how you acess the instance of DroneRecord at p
		p = p->next;
	}

	return get_size();
}

// PURPOSE: Prints all the elements in the list to the console
void DronesManager::print() const {
	DroneRecord* p = first;

	while (p != NULL){
		cout << "Drone ID: " << p->droneID << endl;
		cout << "Range: " << p->range << endl;
		cout << "Year Bought: " << p->yearBought << endl;
		cout << "Drone Type: " << p->droneType << endl;
		cout << "Manufacturer: " << p->manufacturer << endl;
		cout << "Description: " << p->description << endl;
		cout << "Battery Type: " << p->batteryType << endl;
		
		p = p->next;
	}
}


// MUTATORS
// PURPOSE: Inserts a value into the list at a given index; the list is not sorted
// if the index is invalid, insertion is rejected
bool DronesManager::insert(DroneRecord value, unsigned int index) {
	int count = 0;
	DroneRecord* p = first;
	DroneRecord* newValue = &value;

	//if list is empty insert value at first node
	if (p == NULL){
		first->DroneRecord = newValue;
		return true;
	}
	
	while (p != NULL){
		count++;
		if (count == index){
			DroneRecord* temp_prev = p->prev;
			temp_prev->next = newValue;
			p->prev = newValue;
			newValue->next = p;
			newValue->prev = temp_prev;
			
			// adds node in: sets previous node's "next" to newValue and sets the next node's previous to newValue
			return true;
		}  
		p = p->next;
	}
	return false;
}

// PURPOSE: Inserts a value at the beginning of the list; the list is not sorted
bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* newValue = &value;

	if (first == NULL){
		first = newValue;
		return true;
	}
	else{
		DroneRecord* p = first;
		p->prev = newValue;
		first = newValue;
		newValue->next = p;	
		return true;

	}

	return false;
}

// PURPOSE: Inserts a value at the end of the list; the list is not sorted
bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* newValue = &value;

	if (first == NULL){
		first = newValue;
		return true;
	}
	else{
		DroneRecord* p = last;
		p->next = newValue;
		last = newValue;
		newValue->prev = p;
		return true;
	}

	return false;
}

// PURPOSE: Deletes a value from the list at the given index
bool DronesManager::remove(unsigned int index) {
	int count = 0;
	DroneRecord* p = first;

	if (p == NULL){
		return false;
	}

	while (p != NULL){
		count++;
		if (count == index){
			DroneRecord* after_p = p->next;
			DroneRecord* before_p = p->prev;

			after_p->prev = before_p;
			before_p->next = after_p

			delete p;
			p = NULL;

			return true;
		}  
		p = p->next;
	}
	return false;
}

// PURPOSE: Deletes a value from the beginning of the list
bool DronesManager::remove_front() {
	
	if (first == NULL){
		return false;
	}

	else{
		DroneRecord* p = first->next;
		delete p->prev;
		p->prev = NULL;
		first = p;
		return true;
	}
	
	return false;
}

bool DronesManager::remove_back() {
	if (first == NULL){
		return false;
	}

	else{
		DroneRecord* p = last->prev;
		delete p->next;
		p->next = NULL;
		last = p;
		return true;
	}

	return false;
}

// PURPOSE: Replaces value at the given index with the given value; the list is not sorted	
// if the index is invalid, replacement is rejected
bool DronesManager::replace(unsigned int index, DroneRecord value) {
	DroneRecord* p = first;
	DroneRecord* newValue = &value;
	int count = 0;

	if (p == NULL){
		return false;
	}

	while (p != NULL){
		count++;
		if (count == index){
			p = newValue;
			return true;
		}  
		p = p->next;
	}
	
	return false;
}

// PURPOSE: Reverses the linked list
bool DronesManager::reverse_list() {
	DroneRecord* before = NULL;
	DroneRecord* p = first;
	DroneRecord* after;

	if (first == NULL){
		return false;
	}
	
	while (p != NULL){
		after = p->next;
		p->next = before;
		before = p;
		p = after;
	}

	return true;
}

// PURPOSE: Allows record storage in sorted ascending or descending order based on drone ID value

// PURPOSE: Returns true if the list is sorted in ascending (non-descending) order
bool DronesManagerSorted::is_sorted_asc() const {
	DroneRecord* p = first;
	DroneRecord* p_next = p->next;

	if (p == NULL){
		return false;
	}

	while (p_next != NULL){
		if (*p_next.droneID < *p.droneID){ //not sure if thats the right syntax for checking the id of the drone that pointer is pointing to
			return false;
		}

		p = p->next;
		p_next = p_next->next;
	}

	return true;
}

// PURPOSE: Returns true if the list is sorted in descending (non-ascending) order
bool DronesManagerSorted::is_sorted_desc() const {
	DroneRecord* p = first;
	DroneRecord* p_next = p->next;

	if (p == NULL){
		return false;
	}

	while (p_next != NULL){
		if (*p_next.droneID > *p.droneID){
			return false;
		}

		p = p->next;
		p_next = p_next->next;
	}

}
// MUTATORS

// PURPOSE: Inserts a value so that the list remains sorted in ascending order
// if the list is not sorted in appropriate order, insertion is rejected
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	
	if (is_sorted_asc() == false){
		return false;
	}

	DroneRecord* p = first;
	DroneRecord* newVal = &val;

	while (p != NULL){
		if (*p.droneID > val.droneID){
			// insert newVal before p
			DroneRecord* temp_prev = p->prev;
			p->prev = newVal;
			temp_prev->next = newVal;
			newVal->next = p;
			newVal->prev = temp_prev;
			return true;
		}

		p = p->next;
	}

	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	if (is_sorted_desc() == false){
		return false;
	}

	DroneRecord* p = first;
	DroneRecord* newVal = &val;

	while (p != NULL){
		if (*p.droneID < val.droneID){
			// insert newVal before p
			DroneRecord* temp_prev = p->prev;
			p->prev = newVal;
			temp_prev->next = newVal;
			newVal->next = p;
			newVal->prev = temp_prev;
			return true;
		}

		p = p->next;
	}

	return false;
}

void DronesManagerSorted::sort_asc() {
}
    
void DronesManagerSorted::sort_desc() {
}
