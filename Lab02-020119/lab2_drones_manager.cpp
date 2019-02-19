#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

// EXPLICIT CONSTRUCTOR AND DESTRUCTOR
// PURPOSE: Creates a new empty DronesManager
DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {
}

// PURPOSE: Destroys this instance and frees up all dynamically allocated memory
DronesManager::~DronesManager() {

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
	if (first == NULL){
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

		if (count == index){
			return *p;
		}

		count++;
		p = p->next;
	}
	return *last;

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

		if (*p == value){
			return index;
		}
		p = p->next;
		index++;
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
	DroneRecord* newValue = new DroneRecord(value.droneID, value.range, value.yearBought, value.droneType, value.manufacturer, value.description, value.batteryType);

	//if list is empty insert value at first node
	if (p == NULL){
		first = newValue;
		last = newValue;
		return true;
	}

	if (index < 0){
		return false;
	}

	while (p != NULL){

		if (count == index){
			newValue->prev = p->prev;
			if(count != 0) newValue->prev->next = newValue;
			newValue->next = p;
			p->prev = newValue;

			return true;
		}
		count++;
		p = p->next;
	}
	return false;
}

// PURPOSE: Inserts a value at the beginning of the list; the list is not sorted
bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* newValue = new DroneRecord(value.droneID, value.range, value.yearBought, value.droneType, value.manufacturer, value.description, value.batteryType);

	if (first == NULL){
		first = newValue;
		last = newValue;
		return true;
	}

	else{
		DroneRecord* p = first;
		p->prev = newValue;
		first = newValue;
		newValue->next = p;
		newValue->prev = NULL;
		return true;

	}

	return false;
}

// PURPOSE: Inserts a value at the end of the list; the list is not sorted
bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* newValue = new DroneRecord(value.droneID, value.range, value.yearBought, value.droneType, value.manufacturer, value.description, value.batteryType);

	if (first == NULL){
		first = newValue;
		last = newValue;
		return true;
	}
	else{
		DroneRecord* p = last;
		p->next = newValue;
		last = newValue;
		newValue->prev = p;
		newValue->next = NULL;
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

	if (p == first && p == last){
		delete p;
		first = NULL;
		last = NULL;
		return true;
	}

	while (p != NULL){

		if (count == index){

			if (p != first) p->prev->next = p->next;
			if (p != last) p->next->prev = p->prev;

			if (p==first) first = p->next;
			if (p==last) last = p->prev;

			delete p;
			p = NULL;

			return true;
		}
		count++;
		p = p->next;
	}
	return false;
}

// PURPOSE: Deletes a value from the beginning of the list
bool DronesManager::remove_front() {

	if (first == NULL){
		return false;
	}

	if (first->next == NULL){
		delete first;
		first = NULL;
		last = NULL;
		return true;
	}

	DroneRecord* p = first->next;
	delete p->prev;
	p->prev = NULL;
	first = p;
	return true;

}

bool DronesManager::remove_back() {
	if (first == NULL){
		return false;
	}

	if (last->prev == NULL){
		delete last;
		last = NULL;
		first = NULL;
		return true;
	}


	DroneRecord* p = last->prev;
	delete p->next;
	p->next = NULL;
	last = p;
	return true;

}

// PURPOSE: Replaces value at the given index with the given value; the list is not sorted
// if the index is invalid, replacement is rejected
bool DronesManager::replace(unsigned int index, DroneRecord value) {
	DroneRecord* p = first;
	DroneRecord* newValue = new DroneRecord(value.droneID, value.range, value.yearBought, value.droneType, value.manufacturer, value.description, value.batteryType);
	int count = 0;

	if (p == NULL){
		return false;
	}

	while (p != NULL){

		if (count == index){
			newValue->prev = p->prev;
			newValue->next = p->next;

			if (p != first) p->prev->next = newValue;
			if (p != last) p->next->prev = newValue;

			if (p == first) first = newValue;
			if (p == last) last = newValue;

			delete p;
			return true;
		}

		count++;
		p = p->next;
	}

	return false;
}

// PURPOSE: Reverses the linked list
bool DronesManager::reverse_list() {
	DroneRecord* p = first;
	DroneRecord* newFirst = first;

	if (first == NULL){
		return false;
	}

	while (p != NULL){
		DroneRecord* before = p->prev;
		p->prev = p->next;
		p->next = before;
		newFirst = p;
		p = p-> prev;

	}

	last = first;
	first = newFirst;

	return true;
}

// PURPOSE: Allows record storage in sorted ascending or descending order based on drone ID value

// PURPOSE: Returns true if the list is sorted in ascending (non-descending) order
bool DronesManagerSorted::is_sorted_asc() const {
	DroneRecord* p = first;

	if (p == NULL){
		return true;
	}
    DroneRecord* p_next = p->next;

	while (p_next != NULL){
		if ( (p_next->droneID) < (p->droneID) ){ //not sure if thats the right syntax for checking the id of the drone that pointer is pointing to
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
		if (p_next->droneID > p->droneID){
			return false;
		}

		p = p->next;
		p_next = p_next->next;
	}
    return true;

}
// MUTATORS

// PURPOSE: Inserts a value so that the list remains sorted in ascending order
// if the list is not sorted in appropriate order, insertion is rejected
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    //if list is empty, insert no matter what
    if(first == NULL){
        insert_front(val);
        return true;
    }

	if (is_sorted_asc() == false){
		return false;
	}

	DroneRecord* p = first;
	int count = 0;

	while (p != NULL){
		if ((p->droneID) > (val.droneID)){
            if(p == first){
                insert_front(val);
            } else{
                insert(val, count);
            }
			return true;
		}
		count++;
		p = p->next;
	}
    //insertAtEnd
    insert_back(val);
	return true;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {

    //if list is empty, insert no matter what
    if(first == NULL){
        insert_front(val);
        return true;
    }

	if (is_sorted_desc() == false){
		return false;
	}

	DroneRecord* p = first;
	int count = 0;
	while (p != NULL){
		if ((p->droneID) < (val.droneID)){
            if(p == first){
                insert_front(val);
            } else{
                insert(val, count);
            }
            return true;
		}
		count++;
		p = p->next;
	}
    //insertAtEnd
    insert_back(val);
	return true;

}

void DronesManagerSorted::sort_asc() {

	DronesManagerSorted* result = new DronesManagerSorted();

	DroneRecord *p = first;


	while(p != NULL){
    DroneRecord copy = DroneRecord(p->droneID, p->range, p->yearBought, p->droneType, p->manufacturer, p->description, p->description);
		result->insert_sorted_asc(copy);
		p = p->next;
	}

    DroneRecord* temp = first;
    while(temp != NULL){
        DroneRecord* cur = temp;
        temp = temp->next;
        delete cur;
    }

    *this = *result;

}

void DronesManagerSorted::sort_desc() {

	DronesManagerSorted* result = new DronesManagerSorted();

	DroneRecord* p = first;

	while(p != NULL){
		DroneRecord copy = DroneRecord(p->droneID, p->range, p->yearBought, p->droneType, p->manufacturer, p->description, p->description);
		result->insert_sorted_desc(copy);
		p = p->next;
	}

	DroneRecord* temp = first;
	while(temp != NULL){
		DroneRecord* cur = temp;
		temp = temp->next;
		delete cur;
	}

	*this = *result;

}
