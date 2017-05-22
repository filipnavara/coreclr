#include "common.h"
#include <stdlib.h>

#include "assembly.hpp"
#include "mscoree.h"

#include "MonoCoreClr.h"

//-------------------------------------------------------------
// Default constructor, for non-initializing declarations:
//
//      MonoObjectRef or;
//-------------------------------------------------------------
MonoObjectRef::MonoObjectRef()
{
	m_asObj = (MonoObject*)POISONC;
	mono_gc_objectref_new(this);
}

//-------------------------------------------------------------
// Copy constructor, for passing MonoObjectRef's as function arguments.
//-------------------------------------------------------------
MonoObjectRef::MonoObjectRef(const MonoObjectRef & objref)
{
	VALIDATE_MONO_OBJECT(objref.m_asObj);

	// !!! If this assert is fired, there are two possibilities:
	// !!! 1.  You are doing a type cast, e.g.  *(OBJECTREF*)pObj
	// !!!     Instead, you should use ObjectToOBJECTREF(*(Object**)pObj),
	// !!!                          or ObjectToSTRINGREF(*(StringObject**)pObj)
	// !!! 2.  There is a real GC hole here.
	// !!! Either way you need to fix the code.
	MONO_ASSERTE(mono_gc_objectref_valid(&objref));
	if ((objref.m_asObj != 0) && mono_gc_is_heap_pointer((BYTE*)this))
	{
		MONO_ASSERTE(!"Write Barrier violation. Must use SetObjectReference() to assign OBJECTREF's into the GC heap!");
	}
	m_asObj = objref.m_asObj;

	if (m_asObj != 0) {
		mono_gc_enable_stress_heap();
	}

	mono_gc_objectref_new(this);
}

//-------------------------------------------------------------
// To allow NULL to be used as an MonoObjectRef.
//-------------------------------------------------------------
MonoObjectRef::MonoObjectRef(TADDR nul)
{
	m_asObj = (MonoObject*)nul;
	if (m_asObj != NULL)
	{
		VALIDATE_MONO_OBJECT(m_asObj);
		mono_gc_enable_stress_heap();
	}
	mono_gc_objectref_new(this);
}

// allow explict casts
MonoObjectRef::MonoObjectRef(MonoObject *pObject)
{
	if ((pObject != 0) && mono_gc_is_heap_pointer((BYTE*)this))
	{
		MONO_ASSERTE(!"Write Barrier violation. Must use SetObjectReference() to assign OBJECTREF's into the GC heap!");
	}
	m_asObj = pObject;
	VALIDATE_MONO_OBJECT(m_asObj);
	if (m_asObj != 0) {
		mono_gc_enable_stress_heap();
	}
	mono_gc_objectref_new(this);
}

//-------------------------------------------------------------
// Test against NULL.
//-------------------------------------------------------------
int MonoObjectRef::operator!() const
{
	// We don't do any validation here, as we want to allow zero comparison in preemptive mode
	return !m_asObj;
}

//-------------------------------------------------------------
// Compare two MonoObjectRef's.
//-------------------------------------------------------------
int MonoObjectRef::operator==(const MonoObjectRef &objref) const
{
	if (objref.m_asObj != NULL) // Allow comparison to zero in preemptive mode
	{
		VALIDATE_MONO_OBJECT(objref.m_asObj);

		// !!! If this assert is fired, there are two possibilities:
		// !!! 1.  You are doing a type cast, e.g.  *(OBJECTREF*)pObj
		// !!!     Instead, you should use ObjectToOBJECTREF(*(Object**)pObj),
		// !!!                          or ObjectToSTRINGREF(*(StringObject**)pObj)
		// !!! 2.  There is a real GC hole here.
		// !!! Either way you need to fix the code.
		MONO_ASSERTE(mono_gc_objectref_valid(&objref));
		VALIDATE_MONO_OBJECT(m_asObj);
		// If this assert fires, you probably did not protect
		// your OBJECTREF and a GC might have occurred.  To
		// where the possible GC was, set a breakpoint in Thread::TriggersGC 
		MONO_ASSERTE(mono_gc_objectref_valid(this));

		if (m_asObj != 0 || objref.m_asObj != 0) {
			mono_gc_enable_stress_heap();
		}
	}
	return m_asObj == objref.m_asObj;
}


//-------------------------------------------------------------
// Compare two MonoObjectRef's.
//-------------------------------------------------------------
int MonoObjectRef::operator!=(const MonoObjectRef &objref) const
{
	if (objref.m_asObj != NULL)  // Allow comparison to zero in preemptive mode
	{
		VALIDATE_MONO_OBJECT(objref.m_asObj);

		// !!! If this assert is fired, there are two possibilities:
		// !!! 1.  You are doing a type cast, e.g.  *(OBJECTREF*)pObj
		// !!!     Instead, you should use ObjectToOBJECTREF(*(Object**)pObj),
		// !!!                          or ObjectToSTRINGREF(*(StringObject**)pObj)
		// !!! 2.  There is a real GC hole here.
		// !!! Either way you need to fix the code.
		MONO_ASSERTE(mono_gc_objectref_valid(&objref));
		VALIDATE_MONO_OBJECT(m_asObj);
		// If this assert fires, you probably did not protect
		// your OBJECTREF and a GC might have occurred.  To
		// where the possible GC was, set a breakpoint in Thread::TriggersGC 
		MONO_ASSERTE(mono_gc_objectref_valid(this));

		if (m_asObj != 0 || objref.m_asObj != 0) {
			mono_gc_enable_stress_heap();
		}
	}

	return m_asObj != objref.m_asObj;
}

//-------------------------------------------------------------
// Forward method calls.
//-------------------------------------------------------------
MonoObject* MonoObjectRef::operator->()
{
	VALIDATE_MONO_OBJECT(m_asObj);
	// If this assert fires, you probably did not protect
	// your OBJECTREF and a GC might have occurred.  To
	// where the possible GC was, set a breakpoint in Thread::TriggersGC 
	MONO_ASSERTE(mono_gc_objectref_valid(this));

	if (m_asObj != 0) {
		mono_gc_enable_stress_heap();
	}

	// if you are using OBJECTREF directly,
	// you probably want an Object *
	return (MonoObject*)m_asObj;
}

const MonoObject* MonoObjectRef::operator->() const
{
	VALIDATE_MONO_OBJECT(m_asObj);
	// If this assert fires, you probably did not protect
	// your OBJECTREF and a GC might have occurred.  To
	// where the possible GC was, set a breakpoint in Thread::TriggersGC 
	MONO_ASSERTE(mono_gc_objectref_valid(this));

	if (m_asObj != 0) {
		mono_gc_enable_stress_heap();
	}

	// if you are using OBJECTREF directly,
	// you probably want an Object *
	return (MonoObject *)m_asObj;
}

//-------------------------------------------------------------
// Assignment. We don't validate the destination so as not
// to break the sequence:
//
//      MonoObjectRef or;
//      or = ...;
//-------------------------------------------------------------
MonoObjectRef& MonoObjectRef::operator=(const MonoObjectRef &objref)
{
	VALIDATE_MONO_OBJECT(objref.m_asObj);

	// !!! If this assert is fired, there are two possibilities:
	// !!! 1.  You are doing a type cast, e.g.  *(OBJECTREF*)pObj
	// !!!     Instead, you should use ObjectToOBJECTREF(*(Object**)pObj),
	// !!!                          or ObjectToSTRINGREF(*(StringObject**)pObj)
	// !!! 2.  There is a real GC hole here.
	// !!! Either way you need to fix the code.
	MONO_ASSERTE(mono_gc_objectref_valid(&objref));

	if ((objref.m_asObj != 0) && mono_gc_is_heap_pointer((BYTE*)this))
	{
		MONO_ASSERTE(!"Write Barrier violation. Must use SetObjectReference() to assign OBJECTREF's into the GC heap!");
	}
	mono_gc_objectref_assign(this);

	m_asObj = objref.m_asObj;
	if (m_asObj != 0) {
		mono_gc_enable_stress_heap();
	}
	return *this;
}

MonoObjectRef& MonoObjectRef::operator=(TADDR nul)
{
	MONO_ASSERTE(nul == 0);
	mono_gc_objectref_assign(this);
	m_asObj = (MonoObject*)nul;
	if (m_asObj != 0) {
		mono_gc_enable_stress_heap();
	}
	return *this;
}

void MonoObjectRef::Validate(BOOL bDeep, BOOL bVerifyNextHeader, BOOL bVerifySyncBlock)
{
	mono_gc_object_validate(m_asObj);
}
// END MonoObjectRef
