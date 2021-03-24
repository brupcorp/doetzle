#ifndef STR_H_
#define STR_H_

#define str(x) (Str() + x).c_str()
#define strn(x) (Str() + x)

#if __x86_64__
typedef long long long64;
typedef unsigned long long ul64;
typedef unsigned int uint32;
#else
typedef long long64;
typedef unsigned long ul64;
typedef unsigned int uint32;
#endif

class Str {
private:
	char* strPtr;

	static char* strcpy(char* dest, const char* src) {
		for (; *src != '\0'; *dest++ = *src++);
		return &(*dest = '\0');
	}

	static ul64 strlen(const char* str) {
		ul64 len; for (len = 0; *(str + len) != '\0'; len++);
		return len;
	}

	static char* strcat(const char* src, const char* concat) {
		char* concatted = new char[strlen(src) + strlen(concat) + 1];
		strcpy(strcpy(concatted, src), concat);
		return concatted;
	}

	static char* itoa(long64 value) {
		static char buf[32] = { 0 };
		int i = 30;
		ul64 abs = value < 0 ? (ul64)-value : (ul64)value;
		for (; abs && i; abs /= 10) buf[i--] = "0123456789"[abs % 10];
		if (value < 0) buf[i] = '-';
		if (value == 0) buf[i] = '0';
		return &buf[i + (value > 0)];
	}

	static char* ptrtoa(void* value) {
		static char buf[19] = { 0 };
		int i = 17;
		ul64 abs = (ul64)value;
		for (; abs && i; abs /= 16) buf[i--] = "0123456789ABCDEF"[abs % 16];
		if (value == 0) buf[i--] = '0';
		buf[i--] = 'x';
		buf[i] = '0';
		return &buf[i];
	}

	static void updateStr(char** pointer, char* newPointer) {
		delete[] * pointer;
		*pointer = newPointer;
	}

	static void strshift(char* toShift, char rangeTop, char rangeLower, char toAdd) {
		for (; *toShift != '\0'; toShift++)
			*toShift += toAdd * ((*toShift) <= rangeTop && (*toShift) >= rangeLower);
	}

	static bool strcmp(const char* first, const char* second) {
		bool eq = true;
		for (; eq && *first != '\0' || *second != '\0'; first++, second++) eq = *first == *second;
		return eq;
	}

	void init(const char* str) {
		strPtr = new char[strlen(str) + 1]; strcpy(strPtr, str);
	}

public:

	~Str() { delete[] strPtr; };

	const char* c_str() { return strPtr; }
	ul64 len() { return strlen(strPtr); }
	void toLower() { strshift(strPtr, 'Z', 'A', 32); }
	void toUpper() { strshift(strPtr, 'z', 'a', -32); }
	void replace(char what, char replace) { strshift(strPtr, what, what, replace - what); };

	Str() { init(""); }
	Str(const char* str) { init(str); }
	Str(const Str& str) { init(str.strPtr); }
	//Str(long64 num) { init(itoa(num)); }
	Str(int num) { init(itoa(num)); }

	Str operator=(const char* str) { return Str(str); }
	Str operator=(const Str& str) { return Str(str); }
	//Str operator=(long64 num) { return Str(num); }

	bool operator==(const char* str) { return strcmp(strPtr, str); }
	bool operator==(const Str& str) { return strcmp(strPtr, str.strPtr); }

	void operator+=(const char* concat) { updateStr(&strPtr, strcat(strPtr, concat)); }
	void operator+=(const Str& concat) { operator+=(concat.strPtr); }
	void operator+=(int num) { operator+=(itoa(num)); }
	void operator+=(void* addr) { operator+=(ptrtoa(addr)); }

	Str operator+(const char* concat) {
		char* cat = strcat(strPtr, concat);
		Str x(cat);
		delete[] cat;
		return x;
	}
	Str operator+(const Str& concat) { return operator+(concat.strPtr); }
	Str operator+(int num) { return operator+(itoa(num)); }
	Str operator+(void* addr) { return operator+(ptrtoa(addr)); }

	char& operator[](ul64 index) { return index >= len() ? *(char*)0 : strPtr[index]; }

        //64Bit stuff
#if __x86_64__
        Str operator+(long64 num) { return operator+(itoa(num)); }
        void operator+=(long64 num) { operator+=(itoa(num)); }
#endif

};
#endif
