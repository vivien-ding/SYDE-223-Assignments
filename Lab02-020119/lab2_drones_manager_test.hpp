//Written by Vivien (Zhaowei) Ding & Christina Lim 
//Student numbers: 20654920 & 20724130

#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"
#include <iostream>

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
    bool test1() {
    	
    	//create manager, ensure size is not > 0, ensure it's empty, first and last is NULL
		DronesManager manager;
		ASSERT_FALSE(manager.get_size() > 0)
		ASSERT_FALSE(manager.empty() == false)
		ASSERT_FALSE(manager.first != NULL)
		ASSERT_FALSE(manager.last != NULL)
	    return true;
    }

	// PURPOSE: insert_front() and insert_back() on zero-element list
    bool test2() {

    	//insert 200 into empty manager1, manager2
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(200));
		manager2.insert_back(DronesManager::DroneRecord(200));

		//same size of 1
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)

		//first is not empty and first is last for both
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)

		//nothing before first, nothing after last
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)

		//both elements contain 200 as the 0th index
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(200))

	    return true;
    }

	// PURPOSE: select() and search() work properly
    bool test3() {
		DronesManager manager1;

		//10 elements of 0 to 900, inserted into manager 1
		const int num_elems = 10;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(i*100)))
		}

		//check that searching the index value returns the index
		unsigned int idx = 2;
		ASSERT_TRUE(manager1.search(manager1.select(idx)) == idx)

		//check that going beyond the number of elements returns the last value
		ASSERT_TRUE(manager1.select(num_elems + 1) == DronesManager::DroneRecord(900))

		//checks that checking for something that does not exist returns the size
		ASSERT_TRUE(manager1.search(32132100) == manager1.get_size())

		//checks that select works and returns the value of all elements
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager1.select(i) == DronesManager::DroneRecord(i*100))
		}

		//check there's nothing before first and after last
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
	    return true;
    }

    // PURPOSE: remove_front() and remove_back() on one-element list
    bool test4() {

    	//insert same element into empty lists, removes front for 1, removes back for 2
		DronesManager manager1, manager2;
		ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(100)))
		ASSERT_TRUE(manager2.insert_front(DronesManager::DroneRecord(100)))
		ASSERT_TRUE(manager1.remove_front())
		ASSERT_TRUE(manager2.remove_back())

		//checks that they're both empty
		ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL)
		ASSERT_TRUE(manager2.first == NULL && manager2.last == NULL)
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 0)
		ASSERT_TRUE(manager1.empty() == true && manager2.empty() == true)

	    return true;
    }

    // PURPOSE: replace() and reverse_list() work properly
    bool test5() {

    	//creates manager of size 8, inserts 1-7
    	DronesManager manager;
		const int num_elems = 8;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
		}

		//replace 0 with 800, 3 with 900, and 7 with 1000
		ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(800)))
		ASSERT_TRUE(manager.replace(3, DronesManager::DroneRecord(900)))
		ASSERT_TRUE(manager.replace(7, DronesManager::DroneRecord(1000)))

		//first element should be 800, last element should be 1000, and the third element should be 900
		ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(800))
		ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(1000))
		ASSERT_TRUE(*(manager.first->next->next->next) == DronesManager::DroneRecord(900))

		//expected final values
		int test_values[8] = {1000, 6, 5, 4, 900, 2, 1, 800};
		ASSERT_TRUE(manager.reverse_list());
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]))
		}

		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)

	    return true;
    }

    // PURPOSE: insert_front() keeps moving elements forward
    bool test6() {

    	//create manager with size 5, insert front elements 1-4, ensure that size is incrementing
    	// and that insert front is always i, j is expected value at each stage

    	DronesManager manager;
		const int num_elems = 5;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
			ASSERT_TRUE(manager.get_size() == (i + 1))
			ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(i))

			DronesManager::DroneRecord* n = manager.first;
			for (int j = 0; j <= i; j++) {
				DronesManager::DroneRecord expected_value = DronesManager::DroneRecord(i - j);
				ASSERT_TRUE(n != NULL && *n == expected_value)
				n = n->next;
			}
		}
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
    }

    // PURPOSE: inserting at different positions in the list
    bool test7() {

    	//insert in back 1-7 into empty manager
		DronesManager manager;
		const int num_elems = 8;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
		}

		// check for inserting drone records 8, 9, 10 at index 0, 3, 7
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(8), 0))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(9), 3))

		// list size should be 10 now
		ASSERT_TRUE(manager.get_size() == 10)

		ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(8))
		ASSERT_TRUE(*(manager.first->next->next->next) == DronesManager::DroneRecord(9))

		// check values are inserted at proper indexs
		int test_values[10] = {8, 0, 1, 9, 2, 3, 4, 5, 6, 7};
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]))
		}

		return true;
    }

    // PURPOSE: try to remove too many elements, then add a few elements
    bool test8() {

    	//insert elements from 0 to 3
		DronesManager manager;
		const int num_elems = 4;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
		}

		//remove 0, 2 should work
		ASSERT_TRUE(manager.remove(0))
		ASSERT_TRUE(manager.remove(2))

		//only 2 element left, index 2 and 3 are out of bounds
		ASSERT_FALSE(manager.remove(2))
		ASSERT_FALSE(manager.remove(3))
		ASSERT_TRUE(manager.get_size() == 2)

		//insert 3 more elements, size should be 5
		const int num_elems_2 = 3;
		for (int i = 0; i < num_elems_2; i++) {
			ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i+3)))
		}

		ASSERT_TRUE(manager.get_size() == 5)

		//check expected values
		int test_values[5] = {1, 2, 3, 4, 5};
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]))
		}

    	return true;
    }

 	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {

		//insert 1-7
		DronesManager manager;
		const int num_elems = 8;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
		} 

		//insert 8 and 9 at the front
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(8), 0))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(9), 0))

		//cannot insert at index 20
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(11), 20))

		//remove indices 2, 0
		ASSERT_TRUE(manager.remove(2))
		ASSERT_TRUE(manager.remove(0))

		//cannot remove at index 20
		ASSERT_FALSE(manager.remove(15))

		//added 2, removed 2, size is still 8
		ASSERT_TRUE(manager.get_size() == num_elems)


		//first element should be 8 since 9 was removed
		ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(8))

		//second element should be 1 since 9 was removed
		ASSERT_TRUE(*(manager.first->next) == DronesManager::DroneRecord(1))

		//last element should be 7
		ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(7))

		//expected values, test that the rest of array is good
		int test_values[8] = {8, 1, 2, 3, 4, 5, 6 ,7};

		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]))
		}

		//check that remove from empty is illegal
		DronesManager empty_manager;
		ASSERT_FALSE(empty_manager.remove(0))
		ASSERT_TRUE(empty_manager.first == NULL && empty_manager.last == NULL)

		return true;
	}

	// PURPOSE: insert into an unsorted list, then sort the list
	bool test10() {
		DronesManagerSorted manager;

		//insert some unsorted values into back, insert others at random sports
		manager.insert_back(DronesManager::DroneRecord(3));
		manager.insert_back(DronesManager::DroneRecord(1));
		manager.insert_back(DronesManager::DroneRecord(4));
		manager.insert_back(DronesManager::DroneRecord(10));
		manager.insert_back(DronesManager::DroneRecord(5));

		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(11), 0))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(12), 3))

		const int test_values[7] = {11, 3, 1, 12, 4, 10, 5};
		const int num_elems = 7;

		//check expected values
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]))
		}

		//sort, then check if sorted
		manager.sort_asc();
		ASSERT_TRUE(manager.is_sorted_asc());

		const int test_values_sorted[7] = {1, 3, 4, 5, 10, 11, 12};
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values_sorted[i]))
		}


    return true;

	}

	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
	
		//create sorted list		
		DronesManagerSorted manager1;
		const int num_elems = 5;

		for (int i = 0; i < num_elems; i++){
			ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(i)));
		}

		//insert random values
		manager1.insert_sorted_asc(DronesManager::DroneRecord(3));
		manager1.insert_sorted_asc(DronesManager::DroneRecord(1));
		manager1.insert_sorted_asc(DronesManager::DroneRecord(4));
		manager1.insert_sorted_asc(DronesManager::DroneRecord(10));
		manager1.insert_sorted_asc(DronesManager::DroneRecord(5));

		//check still sorted, compares expected values
		ASSERT_TRUE(manager1.is_sorted_asc());

		const int test_values[10] = {0, 1, 1, 2, 3, 3, 4, 4, 5, 10};
		const int num_elems_2 = 10;

		for (int i = 0; i < num_elems_2; i++) {
			ASSERT_TRUE(manager1.select(i) == DronesManager::DroneRecord(test_values[i]))
		}

		//check that remove still works
		manager1.remove_back();
		manager1.remove_front();
		manager1.remove(1);
		ASSERT_TRUE(manager1.is_sorted_asc());

		return true;
	}

	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
		//create sorted list in descending order		
		DronesManagerSorted manager1;
		const int num_elems = 5;

		for (int i = 0; i < num_elems; i++){
			ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(i)));
		}

		//insert random values
		manager1.insert_sorted_desc(DronesManager::DroneRecord(3));
		manager1.insert_sorted_desc(DronesManager::DroneRecord(1));
		manager1.insert_sorted_desc(DronesManager::DroneRecord(4));
		manager1.insert_sorted_desc(DronesManager::DroneRecord(10));
		manager1.insert_sorted_desc(DronesManager::DroneRecord(5));

		//check still sorted, compares expected values
		ASSERT_TRUE(manager1.is_sorted_desc());

		const int test_values[10] = {10, 5, 4, 4, 3, 3, 2, 1, 1, 0};
		const int num_elems_2 = 10;

		for (int i = 0; i < num_elems_2; i++) {
			ASSERT_TRUE(manager1.select(i) == DronesManager::DroneRecord(test_values[i]))
		}

		//check that remove still works
		manager1.remove_back();
		manager1.remove_front();
		manager1.remove(1);
		ASSERT_TRUE(manager1.is_sorted_desc());

		return true;
	}
};


#endif
