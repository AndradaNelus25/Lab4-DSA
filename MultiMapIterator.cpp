#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->currentKey = 0;
	while (this->currentKey < this->col.m && (this->col.T[currentKey].first == NULL_TVALUE || this->col.T[currentKey].first == DELETED))
		this->currentKey++;
	this->currentValue = 0;
}
//Complexity : Best case: Theta(1) , Worst case: Theta(m), Overall complexity : O(m) 

TElem MultiMapIterator::getCurrent() const{
	if (this->currentKey>=this->col.m || this->currentValue>=this->col.T[currentKey].second.lenV)
		throw exception();
	TElem elem;
	elem.first = this->col.T[this->currentKey].first;
	elem.second = this->col.T[currentKey].second.V[currentValue];

	return elem;
}
//theta(1)

bool MultiMapIterator::valid() const {
	return (this->currentKey < this->col.m);
		
}
//theta(1)

void MultiMapIterator::next() {
	if (this->currentKey >= this->col.m || this->currentValue >= this->col.T[currentKey].second.lenV)
		throw exception();

	this->currentValue++;
	if (this->currentValue >= this->col.T[currentKey].second.lenV) {
		this->currentKey++;
		while (this->currentKey < this->col.m && ((this->col.T[currentKey].first == NULL_TVALUE) || (this->col.T[currentKey].first == DELETED))) {
			this->currentKey++;
		}
		this->currentValue = 0;
	}

}
//theta(1)

void MultiMapIterator::first() {
	this->currentKey = 0;
	while (this->currentKey < this->col.m && (this->col.T[currentKey].first == NULL_TVALUE || this->col.T[currentKey].first == DELETED))
		this->currentKey++;
	this->currentValue = 0;
}
//theta(1)
