#pragma once
#include <iostream>
using namespace std;

template <typename TYPE>
class Array {
protected:
    TYPE* values;
    int size;
    int capacity;
    int startingCapacity;
public:
    Array(int capacity) :
        size(0),
        capacity(capacity),
        startingCapacity(capacity) {
        values = new TYPE[capacity];
    }

    Array() : Array(10) {}

    ~Array() {
        delete[] values;
    }

    int getSize() {
        return this->size;
    }

    TYPE* getValues() {
        return this->values;
    }

    void resize() {
        // Remember location of old array
        TYPE* temp = values;

        // Increase capacity variable for larger array
        capacity += startingCapacity;

        // Create new larger array
        values = new TYPE[capacity];

        // Copy over all values from old array
        for (int i = 0; i < this->size; i++) {
            values[i] = temp[i];
        }

        // Delete the old array
        delete[] temp;
    }

    // READ METHOD
    TYPE get(int index) {
        return values[index];
    }

    // INSERT METHOD
    void add(TYPE value) {
        // Check to see if array is full
        if (this->size == this->capacity)
            this->resize();

        // Insert new value into array
        values[size] = value;
        size++;
    }

    void add(TYPE value, int index) {
        // Check to see if array is full
        if (this->size == this->capacity)
            this->resize();

        // Shift all values to the right after the index
        for (int i = size; i > index; i--) {
            values[i] = values[i - 1];
        }

        // Insert new value at the index requested
        values[index] = value;
        this->size++;
    }

    // DELETION METHOD
    void remove(int index) {
        // Shift all elements after index to the left
        for (int i = index; i < this->size - 1; i++) {
            values[i] = values[i + 1];
        }
        // Adjust the size
        this->size--;
    }

    // SEARCH METHOD
    int search(TYPE value) {
        for (int i = 0; i < this->size; i++) {
            if (this->values[i] == value)
                return i;
        }
        return -1;
    }

    // OVERLOAD << OPERATOR
    friend ostream& operator<<(ostream& os, Array<TYPE>& array) {
        for (int i = 0; i < array.size; i++) {
            os << array.get(i) << ",";
        }
        return os;
    }

    // SWAP METHOD
    void swap(int a, int b) {
        TYPE temp = values[a];
        values[a] = values[b];
        values[b] = temp;
    }

    // BUBBLE SORT
    void bubbleSort() {
        int unsorted = this->size - 1;
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            for (int i = 0; i < unsorted; i++) {
                if (values[i + 1] < values[i]) {
                    swap(i, i + 1);
                    sorted = false;
                }
            }
            unsorted--;
        }
    }

    // SELECTION SORT METHOD
    void selectionSort() {
        int lowestIndex = 0;
        for (int i = 0; i < this->size - 1; i++) {
            lowestIndex = i;
            for (int j = i + 1; j < this->size; j++) {
                if (values[j] < values[lowestIndex])
                    lowestIndex = j;
            }
            if (lowestIndex != i) {
                swap(i, lowestIndex);
            }
        }
    }

    // INSERTION SORT METHOD
    void insertionSort() {
        // Create a variable of type TYPE to store value
        TYPE heldValue;
        // Create an int to hold current gap location
        int gap = 1;
        for (int i = 1; i < size; i++) {
            // Store values[i] in our storedValue variable
            heldValue = values[i];
            // gap location to i - 1
            gap = i - 1;
            // LOOP while gap location >= 0 AND values[gap location] > stored value
//            cout << *this << endl;
            while (gap >= 0 && values[gap] > heldValue) {
                // Shift values[gap + 1] to be what's in values[gap]
                values[gap + 1] = values[gap];
                // Decrement the gap location
                gap--;
            }
            // Store the stored value in values[gap + 1]
            values[gap + 1] = heldValue;
        }
    }

    // BOGOSORT
    // This is a joke, do not use in real life.
    bool isSorted() {
        for (int i = 0; i < this->size - 1; i++) {
            if (this->values[i + 1] < this->values[i])
                return false;
        }
        return true;
    }

    void shuffle() {
        for (int i = 0; i < this->size; i++) {
            swap(i, rand() % this->size);
        }
    }

    void bogoSort() {
        while (!this->isSorted()) {
            this->shuffle();
        }
    }
};
