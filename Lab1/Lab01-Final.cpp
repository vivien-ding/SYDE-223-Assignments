//Written by Vivien (Zhaowei) Ding and Christina Lim

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using std::vector;

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;


class Artwork {
	string artist, title;
	int year;

public:

	//empty constructor
	Artwork() : year(0){}

	//constructor
	Artwork(string new_artist, string new_title, int new_year): artist(new_artist), title(new_title), year(new_year){}

	//operator override - checks all fields in Artwork for equality
	bool operator==(const Artwork& target){
		bool are_equal = artist == target.artist;
		are_equal = are_equal && (title == target.title);
		are_equal = are_equal && (year == target.year);
		return are_equal;
	}

};

class SoldArtwork : public Artwork{
	string customer_name, customer_address;
	double sale_amount;

public:
	//empty constructor
	SoldArtwork(): sale_amount(0){}

	//constructor
	SoldArtwork(string new_customer_name, string new_customer_address, double new_sale_amount, Artwork new_artwork): customer_name(new_customer_name), 
				customer_address(new_customer_address), sale_amount(new_sale_amount), Artwork(new_artwork){}

	//operator override - checks all fields for equality
	bool operator==(const SoldArtwork& target){
		return customer_name == target.customer_name
		&& customer_address == target.customer_address
		&& sale_amount == target.sale_amount;
	}

};

class ArtCollection {
	
	//friend function
	friend ArtCollection operator+(const ArtCollection& collection1, const ArtCollection& collection2);


public:
	vector<Artwork> my_artwork;
	vector<SoldArtwork> my_sold_artwork;

	//insert artwork function, adds only new artwork to artwork vector
	bool insert_artwork(const Artwork& artwork_info){
		for (int index = 0; index < my_artwork.size(); ++index){
			if(my_artwork[index] == artwork_info){
				return false;
			}
		}
		my_artwork.push_back(artwork_info);
		return true;
	}

	//sell artwork function, removes artwork from vector (if exists) and adds to sold artwork vector
	bool sell_artwork(const SoldArtwork& artwork_info){
		Artwork a = static_cast<Artwork>(artwork_info);
		for (int index = 0; index < my_artwork.size(); ++index){
			if(my_artwork[index] == a){
				my_artwork.erase(my_artwork.begin() + index);
				my_sold_artwork.push_back(artwork_info);
				return true;
			}
		}
		return false;
	}

	//operator override, checks each vector in artwork and sold artwork between 2 art collections
	bool operator==(const ArtCollection& target){

		bool equal = 1;

		if (my_artwork.size() != target.my_artwork.size() || my_sold_artwork.size() != target.my_sold_artwork.size()){
			equal = 0;
		}
		else {
			for (int index = 0; index < my_artwork.size(); ++index){
				if ((my_artwork[index] == target.my_artwork[index]) == false){
					return false;
				}
			}
			for (int index = 0; index < my_sold_artwork.size(); ++index){
				if ((my_sold_artwork[index] == target.my_sold_artwork[index]) == false){
					return false;
				}
			}
			return true;
		}

	}

};

	//operator override friend non-member function for adding two art collections together
	ArtCollection operator+(const ArtCollection& collection1, const ArtCollection& collection2){
	
		ArtCollection NewCollection;

		for (int i = 0; i < collection1.my_artwork.size(); i++){
			NewCollection.my_artwork.push_back(collection1.my_artwork[i]);
		}
		for (int i = 0; i < collection1.my_sold_artwork.size(); i++){
			NewCollection.my_sold_artwork.push_back(collection1.my_sold_artwork[i]);
		}
		for (int i = 0; i < collection2.my_artwork.size(); i++){
			NewCollection.my_artwork.push_back(collection2.my_artwork[i]);
		}
		for (int i = 0; i < collection2.my_sold_artwork.size(); i++){
			NewCollection.my_sold_artwork.push_back(collection2.my_sold_artwork[i]);
		}

		return NewCollection;
	}

//test class
class ArtCollectionTest{
	Artwork a1, a2, a3, a4;
	SoldArtwork s1, s2;
	ArtCollection ac1, ac2, ac3;

public:

	void setup(){
		a1 = Artwork("Chris", "Art1", 1999);
		a2 = Artwork("Tina", "Art2", 1998);
		a3 = Artwork("Anne", "Art3", 1997);
		a4 = Artwork("Chris", "Art1", 1999);

		s1 = SoldArtwork("Vivien", "123 Address St.", 100, a1);
		s2 = SoldArtwork("Ding", "789 Road Ave.", 900, a2);
	}
	
	//checks two artworks if they're the same
	bool test_equals_artwork(){
		ASSERT_TRUE((a1 == a4))
		return true;
	}

	//checks two sold artworks if they're the same
	bool test_equals_sold_artwork(){
		ASSERT_TRUE((s1 == s1))
		return true;
	}

	//insert artwork, a different one, and tries inserting the same one again
	bool test_insert_artwork(){
		ac1.insert_artwork(a1);
		ASSERT_TRUE(ac1.my_artwork.size() == 1)
		ac1.insert_artwork(a2);
		ASSERT_TRUE(ac1.my_artwork.size() == 2)
		ac1.insert_artwork(a2);
		ASSERT_TRUE(ac1.my_artwork.size() == 2)
		return true;

	}


	//sell an artwork, sell an artwork not in a collection
	bool test_sell_artwork(){
		ac1.sell_artwork(s1);
		ac2.sell_artwork(s1);
		ASSERT_TRUE(ac1.my_artwork.size() == 1)
		ASSERT_TRUE(ac1.my_sold_artwork.size() == 1)
		ASSERT_FALSE(ac2.my_sold_artwork.size() == 1) //should not be 1 since the artwork was never in ac2
		return true;

	}


	//compare the same art collection, and two art collections that aren't equal
	bool test_equals_artcollection(){
		ac1.insert_artwork(a1);
		ac2.insert_artwork(a2);
		ASSERT_TRUE((ac1 == ac1))
		ASSERT_FALSE((ac1 == ac2))
		return true;
	}

	//test add two art collections, check if resulting vectors are the same size
	bool test_add_artcollection(){
		ac2.insert_artwork(a3);
		ac3 = ac1 + ac2;
		ASSERT_TRUE(ac3.my_artwork.size() == (ac1.my_artwork.size()+ac2.my_artwork.size()))
		ASSERT_TRUE(ac3.my_sold_artwork.size() == (ac1.my_sold_artwork.size()+ac2.my_sold_artwork.size()))
		return true;

	}

	void tear_down(){}

	void run_test() {
		setup();
		cout << ( test_equals_artwork()? "Test equals artwork passed" : "Test equals artwork failed") << endl;
		cout << ( test_equals_sold_artwork()? "Test equals sold artwork passed" : "Test equals sold artwork failed") << endl;
		cout << ( test_equals_artcollection()? "Test equals art collection passed" : "Test equals art collection failed") << endl;
		cout << ( test_insert_artwork()? "Test insert artwork passed" : "Test insert artwork failed") << endl;
		cout << ( test_sell_artwork()? "Test sell artwork passed" : "Test sell artwork failed") << endl;
		cout << ( test_add_artcollection()? "Test add artwork passed" : "Test add artwork failed") << endl;

		tear_down();

	}
	
};


int main(){

	ArtCollectionTest test;
	test.run_test();
}












