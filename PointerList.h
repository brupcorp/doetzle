#ifndef PTRLIST_H
#define PTRLIST_H

template <class T> struct Element {

	T* ptr;
	Element<T>* next;
	Element() : ptr(0), next(0) {}
};

template <class T> class Iter {
  public:
	Element<T>* _root;
	Iter(Element<T>* node) { this->_root = node; }
	T& operator*() { return *(_root->ptr); }
	void operator++() { _root = _root->next; }
	bool operator!=(const Iter& cmp) { return cmp._root != _root->next; }
};

template <class T> class PointerList {

  private:
	size_t len;
	Element<T>* firstElement;

  public:
	PointerList() : len(0), firstElement(new Element<T>()) {}

	size_t length() { return len; }
	void clear() {
		for(size_t i = 0; i <= len; i++) delete pop();
	}
	bool contains(T* val) { return index_of(val) == -1 ? false : true; }

	void append(T* val) {
		Element<T>* cur = firstElement;
		while(cur->next != 0) cur = cur->next;
		cur->next = new Element<T>();
		cur->ptr = val;
		len++;
	}

	void append(T val) {
		Element<T>* cur = firstElement;
		while(cur->next != 0) cur = cur->next;
		cur->next = new Element<T>();
		cur->ptr = new T(val);
		len++;
	}

	void push(T* val) {
		firstElement->next = new Element<T>(*firstElement);
		firstElement->ptr = val;
		len++;
	}

	T* pop() {
		if(firstElement->next == 0) return 0;

		Element<T>* top = firstElement;
		T* ptr = top->ptr;
		firstElement = top->next;

		delete top;

		len--;

		return ptr;
	}

	T* remove_last() {
		if(firstElement->next == 0) return 0;

		Element<T>* cur = firstElement;
		while(cur->next->next != 0) cur = cur->next;

		T* ptr = cur->ptr;
		cur->ptr = 0;

		delete cur->next;
		cur->next = 0;

		len--;

		return ptr;
	}

	T* remove(size_t n) {
		if(n + 1 > len) return 0;

		Element<T>* cur = firstElement;
		for(size_t i = 0; i < n; i++) cur = cur->next;

		T* ptr = cur->ptr;
		Element<T>* trgt = cur->next;

		cur->ptr = trgt->ptr;
		cur->next = trgt->next;
		delete trgt;

		len--;

		return ptr;
	}

	T* get(size_t n) {
		if(n + 1 > len) return 0;
		Element<T>* cur = firstElement;
		for(size_t i = 0; i < n; i++) cur = cur->next;
		return cur->ptr;
	}

	bool set(int n, T* val) {
		if(n + 1 > len) return false;
		Element<T>* cur = firstElement;
		for(size_t i = 0; i < n; i++) cur = cur->next;
		delete cur->ptr;
		cur->ptr = val;
		return true;
	}

	int index_of(T* val) {
		if(len == 0) return -1;

		Element<T>* cur = firstElement;
		size_t index = 0;
		while(cur->ptr != val) {
			if(cur->next->next == 0) return -1;
			cur = cur->next;
			index++;
		}
		return index;
	}

	T& operator[](size_t index) { return *get(index); }

	Iter<T> begin() { return Iter<T>(firstElement); }
	Iter<T> end() { return Iter<T>(0); }
};

#endif