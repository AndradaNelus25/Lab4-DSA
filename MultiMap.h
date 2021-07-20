#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator
//#include "Header.h"
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
//typedef std::pair<TKey, DA> MyTElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
#define DELETED -222222
class MultiMapIterator;

struct DA { 
	TValue* V;
	int capV;
	int lenV;
};
// dynamic array in which are stored TValue elements

typedef std::pair<TKey, DA> MyTElem; 
// pair of TKey and DA , which i use for my representation of the hashtable
//the elements of the hashtable are of the type MyTElem

class MultiMap
{
	friend class MultiMapIterator;

private:
	MyTElem* T; //elements of hashtable
	int m; //'capacity' of hashtable
	int H(TKey e, int i); // hash function
	int nrKeys; // number of unique keys stored in hashtable
	int nrValues; // number of total values stored in hashtable

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) ;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;
	
	//adds a TValue to an array of TValue elements
	void addValue(TValue v, TValue*& arr, int len, int &cap);

	void resize();

	//doubles capacity of DA
	void resizeDA(TValue *&arr, int len, int &cap);

	//resizes hashtable and rehases elements
	//void rehash();

	//descturctor
	~MultiMap();


};

