#pragma once
namespace ASD {
	template<class T>
	class Array
	{
		T * ar;
		unsigned int count, size, grow;
		public:
			Array(unsigned int g = 10);

			Array(Array & copy) { ar = 0; Copy(copy);}

			~Array() { SetSize(0); }

			unsigned int GetCount() { return count; }
			unsigned int GetSize() { return size; }
			unsigned int GetGrow() { return grow; }

			T& operator [](unsigned int i) { return ar[i]; }
			Array & operator = (Array & copy) { return Copy(copy);}

			//todo
			Array & operator<< (Array & copy) { return Copy(copy); }
			//

			Array & SetSize(unsigned int s);
			Array & Copy(Array & copy);
			
			//todo
			Array & Add(Array & copy);
			T & RemoveAt(unsigned int);
			Array Slice(unsigned int start, unsigned int finish);
			Array SubArray(unsigned int i, unsigned int _count);
			unsigned int FindIndex(T);
			//

			Array & Add(T v) {
				if (size == count) { SetSize(size + grow); }
				ar[count++] = v;
				return *this;
			}

			Array & RemoveAll() { count = 0; return *this; }
			Array & FreeExtra() { SetSize(GetCount());  return *this; }
	};

	template<class T>
	Array<T>::Array(unsigned int g) {
		if (g == 0) g = 5;
		grow = g;
		count = 0;
		size = grow;
		ar = 0;
		SetSize(size);
	}

	template<class T>
	Array<T> & Array<T>::Copy(Array & copy) {
		SetSize(0);
		SetSize(copy.GetCount());
		count = copy.GetCount();
		grow = copy.GetGrow();
		for (unsigned int i = 0; i < count; i++)
			ar[i] = copy[i];
		return *this;
	}

	template<class T>
	Array<T> & Array<T>::SetSize(unsigned int s) {
		size = s;
		if (size < count) count = size;
		if (s == 0) {
			delete[]ar;
			ar = 0;
			return *this;
		}
		T *arNew = new T[size];
		if (ar) {
			for (unsigned int i = 0; i < count; i++)
				arNew[i] = ar[i];
			delete[] ar;
		}
		ar = arNew;
		return *this;
	}
}
