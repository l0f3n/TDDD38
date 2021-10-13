#include "Queue.h"

#include <array>
#include <stdexcept>
#include <string>

queue_error::queue_error(const std::string& what_arg) : std::runtime_error{what_arg} {
}

template <typename T, unsigned N>
Queue<T, N>::Queue() : head{0}, tail{0}, elements{std::array<T, N>{}} {
}

template <typename T, unsigned N>
Queue<T, N>::Queue(Queue<T, N> const &o) : head{o.head}, tail{o.tail}, elements{o.elements} {
}

template <typename T, unsigned N>
void Queue<T, N>::enqueue(T value) {
	if (full())
		throw queue_error{"Can't enqueue value, queue is full"};

	elements[(tail++) % N] = value;
}

template <typename T, unsigned N>
T Queue<T, N>::dequeue() {
	if (empty())
		throw queue_error{"Can't dequeue value, queue is empty"};

	return elements[(head++) % N];
}

template <typename T, unsigned N>
bool Queue<T, N>::empty() const {
	return head == tail; 
}

template <typename T, unsigned N>
bool Queue<T, N>::full() const {
	return tail - head == N; 
}

template <typename T, unsigned N>
void Queue<T, N>::clear() {
	head = 0;
	tail = 0;
}

template <typename T, unsigned N>
T const & Queue<T, N>::front() const {
	if (empty())
		throw queue_error{"Can't peek front value, queue is empty"};

	return elements[head % N]; 
}

template <typename T, unsigned N>
template <unsigned M>
Queue<T, N+M> Queue<T, N>::copy_and_expand() const {
	Queue<T, N+M> q{};
	for (size_t i{head}; i < tail; i++) 
		q.elements[(i-head)%N] = elements[i%N];
	q.head = 0;
	q.tail = tail - head;
	return q;
}

