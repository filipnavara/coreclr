#ifndef _MONO_OBJECTREF_H_
#define _MONO_OBJECTREF_H_

#if ENABLE_MONO

#ifdef USE_CHECKED_OBJECTREFS

// MonoObjectRef is a reimplementation of the CLR OBJECTREF in order 
// to provide the same kind of safety guards in debug builds when
// manipulating Object* references

class MonoObjectRef {
private:
	MonoObject* m_asObj;

public:
	//-------------------------------------------------------------
	// Default constructor, for non-initializing declarations:
	//
	//      MonoObjectRef or;
	//-------------------------------------------------------------
	MonoObjectRef();

	//-------------------------------------------------------------
	// Copy constructor, for passing MonoObjectRef's as function arguments.
	//-------------------------------------------------------------
	MonoObjectRef(const MonoObjectRef & objref);

	//-------------------------------------------------------------
	// To allow NULL to be used as an MonoObjectRef.
	//-------------------------------------------------------------
	MonoObjectRef(TADDR nul);

	//-------------------------------------------------------------
	// allow explicit casts
	//-------------------------------------------------------------
	explicit MonoObjectRef(MonoObject *pObject);

	//-------------------------------------------------------------
	// Test against NULL.
	//-------------------------------------------------------------
	int operator!() const;

	//-------------------------------------------------------------
	// Compare two MonoObjectRef's.
	//-------------------------------------------------------------
	int operator==(const MonoObjectRef &objref) const;

	//-------------------------------------------------------------
	// Compare two MonoObjectRef's.
	//-------------------------------------------------------------
	int operator!=(const MonoObjectRef &objref) const;

	//-------------------------------------------------------------
	// Forward method calls.
	//-------------------------------------------------------------
	MonoObject* operator->();
	const MonoObject* operator->() const;

	//-------------------------------------------------------------
	// Assignment. We don't validate the destination so as not
	// to break the sequence:
	//
	//      MonoObjectRef or;
	//      or = ...;
	//-------------------------------------------------------------
	MonoObjectRef& operator=(const MonoObjectRef &objref);
	MonoObjectRef& operator=(TADDR nul);

	void Validate(BOOL bDeep = TRUE, BOOL bVerifyNextHeader = TRUE, BOOL bVerifySyncBlock = TRUE);
};
#define VALIDATE_MONO_OBJECT(obj) do {if ((obj) != NULL) mono_gc_object_validate(obj);} while (0)
#else
typedef MonoObject* MonoObjectRef;
#define VALIDATE_MONO_OBJECT(obj)
#endif

#endif // ENABLE_MONO

#endif // _MONO_METADATA_BLOB_H_
