#include "queue.h"

using std::cout;
using std::endl;

// Constructor to initialize queue
template <typename T>
queue<T>::queue(size_t size)
{
  arr = new T[size];
  capacity = size;
  front = -1;
  rear = -1;
  count = 0;
}

// Destructor to free memory allocated to the queue
template <typename T>
queue<T>::~queue()
{
  delete[] arr;
}

// Utility function to add an element x in the queue
template <typename T>
void queue<T>::push(T value)
{
  if (isFull())
  {
    cout << "Expanding Queue Size\n";
    capacity *= 2;
    T* new_arr = new T[capacity];
    for (size_t i = 0; i < capacity / 2; ++i) { new_arr[i] = arr[i]; }
    delete[] arr;
    arr = new_arr;
  }

  // Check that front exists for a non-empty list;
  if (front == -1)
    ++front;

  // Update current array and increment top value
  ++rear, ++count;
  arr[rear] = value;

  /** Print debugging code to check new values after removal */
//  cout << "\nInserting " << value << ", Front Value: " << arr[front] << ", New value: " << arr[rear];
//  cout << "\nCount: " << count << "\nValues: ";
//  for (size_t i = 0; i < count; ++i) { cout << arr[i] << ", "; }
//  cout << "\n";
//  cout << "Capacity: " << capacity << "\n" << endl;
}

// Utility function to pop top element from the queue
template <typename T>
T queue<T>::pop() {
  if (!isEmpty()) {
    cout << "Removing " << peek() << endl;

    // Update front, rear, and count along with temp value
    --count;
    T temp = arr[front];
    --rear;

    // Adjust capacity accordingly
    if ((count > 1) && (count == capacity / 2)) {
      capacity /= 2;
    }

    // Load new data
    T* new_arr = new T[capacity];
    for (size_t i = 0; i < capacity; ++i) { new_arr[i] = arr[i + 1]; }
    delete[] arr;
    arr = new_arr;

    /** Print debugging code to check new values after removal */
//    cout << "\nRemoval Done. Values: ";
//    for (size_t i = 0; i < count; ++i) { cout << arr[i] << ", "; }
//    cout << "\n";
//    cout << "Capacity: " << capacity << "\n" << endl;

    return temp;
  }
}

// Utility function to return top element in a queue
template <typename T>
T queue<T>::peek()
{
  if (!isEmpty())
    return arr[front];
}

// Utility function to return the size of the queue
template <typename T>
size_t queue<T>::size()
{
  return count;
}

// Utility function to check if the queue is empty or not
template <typename T>
bool queue<T>::isEmpty()
{
  return size() == 0;
}

// Utility function to check if the queue is full or not
template <typename T>
bool queue<T>::isFull()
{
  return capacity == size();
}

template <typename T>
ostream& operator<<(ostream& os, const queue<T>& queue) {
  for (size_t loc = 0; loc < queue.count; ++loc) {
    os << queue.arr[loc];
    // Only print comma if not at end of queue
    if (loc < queue.rear) {
      os << ", ";
    }
  }
  os << "\n";
  return os;
}
