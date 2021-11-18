#pragma once

#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int, int>(-111111, -111111)

class MultiMapIterator;

class MultiMap {
    friend class MultiMapIterator;

private:
    class DLLNode {
    public:
        TValue value = NULL_TVALUE;
        DLLNode *next = nullptr;
        DLLNode *previous= nullptr;
    };

    class DLLLIST {
    public:
        DLLNode *head = nullptr;
        DLLNode *tail= nullptr;
        int size = 0;

        ~DLLLIST() {
            while (this->head != nullptr) {
                auto current = this->head;
                this->head = this->head->next;
                delete current;
            }
        }
    };

    class MMNode {
    public:
        TKey key{};
        DLLLIST *values = new DLLLIST();
        MMNode *next = nullptr;
        MMNode *previous= nullptr;
        ~MMNode() {
            delete this->values;
        }
    };

    MMNode *head = nullptr;
    MMNode *tail= nullptr;
public:
    //adds a key value pair to the multimap
    void add(TKey c, TValue v);

    //removes a key value pair from the multimap
    //returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey c, TValue v);

    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    vector<TValue> search(TKey c) const;

    //returns the number of pairs from the multimap
    int size() const;

    //checks whether the multimap is empty
    bool isEmpty() const;

    //returns an iterator for the multimap
    MultiMapIterator iterator() const;

    //descturctor
    ~MultiMap();

    vector<TValue> get_keys() const;
};
