#ifndef GUARD_smart_pointer_h
#define GUARD_smart_pointer_h
#include "GlobalIncludes.h"

#ifndef NULL
#define NULL 0
#endif

template<class T>
class SmartPntr
{
	//self note: ref to sec 14.5 of the book if you need hints on how to make unique member fuction.
public:
	SmartPntr(): pntrInfo(NULL) {}

	// Contructor with a pointer to track. pPointee is the pointer to keep 
	// track of. Note that the smart pointer will keep ownership of this 
	// pointer and will delete it itself, so don't delete it  yourself.
	SmartPntr(T* dataPntr);
	

	// Copy constructor. The argument is a smart pointer to make a copy of. 
	// The smart pointer will increment the reference counter of the pointed object.
	SmartPntr(const SmartPntr<T>& rhs);
	

	// Assignment operator. The argument is a smart pointer to make a copy of. 
	// The smart pointer will increment the reference counter of the pointed 
	// object. If the smart pointer was already tracking a variable, the reference 
	// counter for this variable will be decremented (and the pointer destroyed 
	// if it becomes 0).
	SmartPntr<T>& operator=(const SmartPntr<T>& rhs);

	// Destructor. It decrements the shared reference counter. 
	// If it becomes 0, the pointed variable is destroyed.
	~SmartPntr();
	
	// Overloading of the * operator to access the contents of the pointed variable.
	T& operator* () const;

	// Overloading of the -> operator that returns the pointer to the variable.
	T* operator->() const;

	// Check to see if the pointer to the variable is NULL.
	bool isNull() const;

private:
	struct SharedData{
		T* dataPntr;
		size_t numberOfRef;
	};
	SharedData *pntrInfo;
};

template<class T>
SmartPntr<T>::SmartPntr(T* dataPntr)
{
	pntrInfo = new SharedData;
	pntrInfo->dataPntr = dataPntr;
	pntrInfo->numberOfRef = 1;
}


template<class T>
SmartPntr<T>::SmartPntr(const SmartPntr<T>& rhs)
{
	pntrInfo = rhs.pntrInfo;
	if(pntrInfo)
		pntrInfo->numberOfRef++;
}

template<class T>
SmartPntr<T>& SmartPntr<T>::operator=(const SmartPntr<T>& rhs)
{
	//self assignment check
	if(this != &rhs){
		//if pointer refers to something reduce the reference count to the object.
		if(pntrInfo){
			pntrInfo->numberOfRef--;
			//if you are the only one with a reference to the object, delete the data.
			if(pntrInfo->numberOfRef == 0){
				delete pntrInfo->dataPntr;
				delete pntrInfo;
			}
			//no need to delete if numberOfRef is negative since nothing allocated
		}
		//now assign the right hand side and do the necessary book keeping.
		pntrInfo = rhs.pntrInfo;
		//increase reference if pointer refers to something
		if(pntrInfo)
			pntrInfo->numberOfRef++;
	}
	return *this;
}
#include <iostream>
template<class T>
SmartPntr<T>::~SmartPntr()
{
	if(pntrInfo){
		pntrInfo->numberOfRef--;
		if(pntrInfo->numberOfRef == 0){
			
			delete pntrInfo->dataPntr;	//BUG - this only needs to be deleted if the memory was dynamically allocated
			delete pntrInfo;
		}
	}
}

template<class T>
T& SmartPntr<T>::operator* () const
{
	if(pntrInfo != NULL){
		return *(pntrInfo->dataPntr);
	}
	else
		throw std::runtime_error("unbounded smart reference");
}

template<class T>
T* SmartPntr<T>::operator-> () const
{
	if(pntrInfo != NULL){
		return pntrInfo->dataPntr;
	}
	else
		throw std::runtime_error("unbounded smart reference");
}

template<class T>
bool SmartPntr<T>::isNull() const
{
	if(pntrInfo && pntrInfo->dataPntr)
		return false;
	return true;
}

#endif
