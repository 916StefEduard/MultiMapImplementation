#include "MultiMapIterator.h"
#include "MultiMap.h"


//Best complexity:Ω(1) ,Worst complexity:O(1) ,Overall complexity:Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap &c) : map(c) {
    this->currentKey = map.head;
    if (this->currentKey != nullptr) {
        this->currentValue = map.head->values->head;
    }
}

//Best complexity:Ω(1) ,Worst complexity:O(1) ,Overall complexity:Theta(1)
TElem MultiMapIterator::getCurrent() const {
    if (!this->valid()) {
        throw std::exception();
    }
    return std::make_pair(this->currentKey->key, this->currentValue->value);
}

//Best complexity:Ω(1) ,Worst complexity:O(1) ,Overall complexity:Theta(1)
bool MultiMapIterator::valid() const {
    return this->currentKey != nullptr;
}

//Best complexity:Ω(1) ,Worst complexity:O(1) ,Overall complexity:Theta(1)
void MultiMapIterator::next() {
    if (!this->valid()) {
        throw std::exception();
    }
    if (this->currentValue->next != nullptr) {
        this->currentValue = this->currentValue->next;
    } else {
        this->currentKey = this->currentKey->next;
        if (this->currentKey != nullptr) {
            this->currentValue = this->currentKey->values->head;
        }
    }
}

//Best complexity:Ω(1) ,Worst complexity:O(1) ,Overall complexity:Theta(1)
void MultiMapIterator::first() {
    this->currentKey = this->map.head;
    if (this->currentKey != nullptr) {
        this->currentValue = map.head->values->head;
    }
}
