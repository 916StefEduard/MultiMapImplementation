#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//Best complexity:Ω(1) , Worst complexity:O(number of keys) , Overall complexity:Theta(number of keys)
void MultiMap::add(TKey key, TValue value) {
    auto current = this->head;
    while (current != nullptr && current->key != key) {
        current = current->next;
    }
    if (current == nullptr) { // key does not exist
        auto mmNode = new MMNode();
        mmNode->key = key;
        auto dllNode = new DLLNode();
        dllNode->value = value;
        mmNode->values->size += 1;
        mmNode->values->head = dllNode;
        mmNode->values->tail = dllNode;
        mmNode->next = nullptr;
        mmNode->previous = this->tail;
        if (this->head == nullptr) {
            this->head = mmNode;
            this->tail = mmNode;
        } else {
            this->tail->next = mmNode;
            this->tail = mmNode;
        }
    } else {
        auto dllNode = new DLLNode();
        dllNode->value = value;
        current->values->size += 1;
        dllNode->next = nullptr;
        dllNode->previous = current->values->tail;
        if (current->values->head == nullptr) {
            current->values->head = dllNode;
            current->values->tail = dllNode;
        } else {
            current->values->tail->next = dllNode;
            current->values->tail = dllNode;
        }
    }
}

//Best complexity:Ω(1),Worst complexity:O(number_of_keys*number_of_values of the last elem),Overall complexity:Theta(number_of_keys*number_of_values of the last elem)
bool MultiMap::remove(TKey key, TValue value) {
    auto currentKey = this->head;
    while (currentKey != nullptr && currentKey->key != key) {
        currentKey = currentKey->next;
    }
    if (currentKey == nullptr) { // key does not exist
        return false;
    }
    auto currentValue = currentKey->values->head;
    while (currentValue != nullptr && currentValue->value != value) {
        currentValue = currentValue->next;
    }
    if (currentValue == nullptr) { // value for existing key does not exist
        return false;
    }
    currentKey->values->size -= 1;
    if (currentValue == currentKey->values->head) {
        if (currentValue == currentKey->values->tail) {
            currentKey->values->head = nullptr;
            currentKey->values->tail = nullptr;
        } else {
            currentKey->values->head = currentKey->values->head->next;
            currentKey->values->head->previous = nullptr;
        }
    } else if (currentValue == currentKey->values->tail) {
        currentKey->values->tail = currentKey->values->tail->previous;
        currentKey->values->tail->next = nullptr;
    } else {
        currentValue->next->previous = currentValue->previous;
        currentValue->previous->next = currentValue->next;
    }
    delete currentValue;
    if (currentKey->values->head == nullptr && currentKey->values->tail == nullptr) {
        if (currentKey == this->head) {
            if (currentKey == this->tail) {
                this->head = nullptr;
                this->tail = nullptr;
            } else {
                this->head = this->head->next;
                this->head->previous = nullptr;
            }
        } else if (currentKey == this->tail) {
            this->tail = this->tail->previous;
            this->tail->next = nullptr;
        } else {
            currentKey->next->previous = currentKey->previous;
            currentKey->previous->next = currentKey->next;
        }
        delete currentKey;
    }
    return true;
}

//Best complexity:Ω(1) ,Worst complexity:O(number of keys) ,Overall complexity:Theta(number of keys)
vector<TValue> MultiMap::search(TKey key) const {
    std::vector<TValue> values;
    auto current = this->head;
    while (current != nullptr && current->key != key) {
        current = current->next;
    }
    if (current == nullptr) {
        return values;
    }
    auto currentValue = current->values->head;
    while (currentValue != nullptr) {
        values.push_back(currentValue->value);
        currentValue = currentValue->next;
    }
    return values;
}

//Best complexity:Ω(number of keys) ,Worst complexity:O(number of keys) ,Overall complexity:Theta(number of keys)
vector<TValue>MultiMap::get_keys() const{
    std::vector<TValue> values;
    auto current=this->head;
    while(current!= nullptr){
        values.push_back(current->key);
        current=current->next;
    }
    return values;
}

//Best complexity:Ω(number of keys) ,Worst complexity:O(number of keys) ,Overall complexity:Theta(number of keys)
int MultiMap::size() const {
    int size = 0;
    auto current = this->head;
    while (current != nullptr) {
        size += current->values->size;
        current = current->next;
    }
    return size;
}


//Best complexity:Ω(1) ,Worst complexity:O(1) ,Overall complexity:Theta(1)
bool MultiMap::isEmpty() const {
    return this->head == nullptr;
}


MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}


//Best complexity:Ω(number of keys) ,Worst complexity:O(number of keys) ,Overall complexity:Theta(number of keys)
MultiMap::~MultiMap() {
    while (this->head != nullptr) {
        auto current = this->head;
        this->head = this->head->next;
        delete current;
    }
}