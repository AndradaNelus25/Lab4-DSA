#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


int MultiMap::H(TKey e, int i)
{
	return ((e % this->m + i) % this->m);
}
//theta(1)


MultiMap::MultiMap() {
	this->nrKeys = 0;
	this->nrValues = 0;
	this->m = 10;
	this->T = new MyTElem[this->m];
	
	for (int i = 0; i < this->m; i++) {
		this->T[i].first = NULL_TVALUE; //NULL_TVALUE means that the position is empty
		this->T[i].second.capV = 1;
		this->T[i].second.lenV = 0;
		this->T[i].second.V = new TValue[this->T[i].second.capV];
	}
}
//theta(m)

void MultiMap::add(TKey c, TValue v) {
	int i = 0;
	int delete_pos = -1;
	bool ok = false;
	int pos = H(c, i);

	while ((i < this->m) && (this->T[pos].first != NULL_TVALUE) && (this->T[pos].first != c)) { // checks if key is already in the array 
		if (this->T[pos].first == DELETED && ok == false) { //if we find a deleted pos
			pos = delete_pos; // deleted_pos = pos of el
			ok = true; // we found a deleted pos
		}
		i++; // go on
		pos = H(c, i); // compute hash function again
	}
	if (this->T[pos].first == c) { //if the key is already in the array 
		
		addValue(v, this->T[pos].second.V, this->T[pos].second.lenV, this->T[pos].second.capV); //we add the value to the DA corresponding to the given found key
		this->nrValues++; //increase number of values
	}
	else if (this->T[pos].first == NULL_TVALUE) { //if the key is not in the array and we find an empty pos for it
		if (ok == true) { //if we have a deleted position where we can put the element
			pos = delete_pos; //we set the pos of the el with the deleted pos we have available 
		}
		this->T[pos].first = c; //we put the key 
		
		addValue(v, this->T[pos].second.V, this->T[pos].second.lenV, this->T[pos].second.capV); //add corresponding value to DA
		

		this->nrKeys++;
		this->nrValues++;
	}
	else if (i == this->m) { //if the key is not in the array and we have no empty pos for it
		if (ok == true) { // if we have a deleted pos suitable for it
			pos = delete_pos; //we set pos of el to deleted_pos

			this->T[pos].first = c; //put the key
			
			addValue(v, this->T[pos].second.V, this->T[pos].second.lenV, this->T[pos].second.capV); //add value
			

			this->nrKeys++;
			this->nrValues++;
		}
		else { //if there is not deleted pos available
			resize(); //resize + rehash hash table
			int i = 0;
			pos = H(c, i);
			while (this->T[pos].first != NULL_TVALUE) { //compute hash function until we reach an empty pos
				i++;
				pos = H(c, i);
			}
			this->T[pos].first = c; //put in key
			
			addValue(v, this->T[pos].second.V, this->T[pos].second.lenV, this->T[pos].second.capV);

			this->nrKeys++;
			this->nrValues++;
		}
	}
}
//Complexity : Best case: Theta(1) , Worst case: Theta(lenV+m), Overall complexity : O(lenV+m) 

bool MultiMap::remove(TKey c, TValue v) {
	int i = 0;
	int pos = H(c, i);
	bool removed;

	while ((i < this->m) && (this->T[pos].first != NULL_TVALUE) && (this->T[pos].first != c)) { //check if key is already in array
		i++;
		pos = H(c, i);
	}

	if (this->T[pos].first == NULL_TVALUE || i == this->m) //if key is not in the array
		return false;

	else if (this->T[pos].first == c) // if key is in array
	{ 
		if (this->T[pos].second.lenV > 1) //if the key has at least one associated value
		{ 
			removed = false;
			int j = 0;
			while (j < this->T[pos].second.lenV && removed == false) { //we check if the value that we are looking for is in the DA associated to the key given
				if (this->T[pos].second.V[j] == v) 
				{
					if (j != this->T[pos].second.lenV - 1) { //if it isn't the last value we replace it with the last value
						this->T[pos].second.V[j] = this->T[pos].second.V[this->T[pos].second.lenV - 1];
					}
					this->T[pos].second.lenV--; //decrease len of DA
					this->nrValues--;
					removed = true; //we removed it
					return true;
				}
				j++;
			}
			if (removed == false) { //if the value corresponding to the key is not in the DA
				return false;
			}
		}
		else if (this->T[pos].second.lenV == 1 && this->T[pos].second.V[0] != v) { //if there is only one value in the DA and it's not the value that we are looking for
			return false;
		}
		else if (this->T[pos].second.lenV == 1 && this->T[pos].second.V[0] == v) { //if there is only one value in the DA and it's the value that we are looking for
			
			this->T[pos].second.lenV = 0; //set len of DA to 0 aka delete el
			this->T[pos].first = DELETED; //set key to DELETED

			this->nrKeys--;
			this->nrValues--;
			return true;
		}
	}
	return false;

}
//Complexity : Best case: Theta(1) , Worst case: Theta(lenV+m), Overall complexity : O(lenV+m)

vector<TValue> MultiMap::search(TKey c) {
	vector<TValue> elems;
	int i = 0;
	int pos;
	pos = H(c, i);
	while ((i < this->m) && (this->T[pos].first != NULL_TVALUE) && (this->T[pos].first != c)) { //check if key is in the array
			i++;
			pos = H(c, i);
	}
	if (this->T[pos].first == c) { //if we find the key
		for (int j = 0; j < this->T[pos].second.lenV; j++) {
			elems.push_back(this->T[pos].second.V[j]); //put corresponding values in vector
		}
	}
	return elems;
}
//Complexity : Best case: Theta(1) , Worst case: Theta(lenV+m), Overall complexity : O(lenV+m)

int MultiMap::size() const {
	return this->nrValues; 
}
//theta(1)

bool MultiMap::isEmpty() const {
	if (this->nrValues == 0) {
		return true;
	}
	return false;
}
//theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
//theta(1)

void MultiMap::addValue(TValue v, TValue*& arr, int len, int& cap)
{
	resizeDA(arr, len, cap);
	arr[len] = v;
	len++;
}
//Best case : theta(1), worst case : theta(n), overall complexity : O(n);


void MultiMap::resizeDA(TValue*& arr, int len, int& cap)
{
	if (len == cap) {
		cap = cap * 2;
		TValue* newarray = new TValue[cap];
		for (int i = 0; i <= len; i++) {
			newarray[i] = arr[i];
		}
		delete[] arr;
		arr = newarray;
	}
}
//Best case : theta(1), worst case : theta(n), overall complexity : O(n);



void MultiMap::resize()
{
	int newM, newPos, newKey, newNrKeys = 0;
	newM = this->m * 2;
	MyTElem* newT = new MyTElem[newM];

	for (int i = 0; i < newM; i++) { //create new empty hashtable with double the capacity
		newT[i].first = NULL_TVALUE;
		newT[i].second.capV = 1;
		newT[i].second.lenV = 0;
		newT[i].second.V = new TValue[newT[i].second.capV];
	}

	for (int i = 0; i < newM; i++)  // go through new hashtable
	{
		if (this->T[i].first != NULL_TVALUE && this->T[i].first != DELETED) //if we find a key in the old hashtable
		{
			newNrKeys++;
			newKey = this->T[i].first;
			int j = 0;
			newPos = H(newKey, j);
			while (newT[newPos].first != NULL_TVALUE) { //compute hash function until we find an empty pos
				j++;
				newPos = H(newKey, j);
			}
			newT[newPos].first = this->T[i].first;
			for (int k = 0; k < this->T[i].second.lenV; k++) {
				newT[newPos].second.V[k] = this->T[i].second.V[k];
			}
			newT[newPos].second.capV = this->T[i].second.capV;
			newT[newPos].second.lenV = this->T[i].second.lenV;

		}
	}
	
	this->nrKeys = newNrKeys;
	delete[] this->T;
	this->m = newM;
	this->T = newT;
}
//theta(m)


MultiMap::~MultiMap() {
	for (int i = 0; i < this->nrValues; i++)
		delete[] this->T[i].second.V;
	delete[] this->T;
	
}

