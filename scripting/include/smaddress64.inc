//////////////////////////////////////////////////////////////////////////////
// MADE BY NOTNHEAVY. USES GPL-3, AS PER REQUEST OF SOURCEMOD               //
//////////////////////////////////////////////////////////////////////////////

// NOTICE:
// This is a temporary extension. dvander should implement something similar to 
// the likes of this. Please be aware that you may have to update your plugin(s)
// in the future, should you be using this.

#if defined __sm_address64_ext_included
	#endinput
#endif
#define __sm_address64_ext_included

//////////////////////////////////////////////////////////////////////////////
// GLOBALS                                                                  //
//////////////////////////////////////////////////////////////////////////////

#define NULL		({ 0, 0 })

#define UINT64_MAX	({ 0xFFFFFFFF, 0xFFFFFFFF })
#define UINT64_MIN	({ 0, 0 })
#define INT64_MAX	({ 0xFFFFFFFF, 0x7FFFFFFF })
#define INT64_MIN	({ 0x00000000, 0x80000000 })

#define UINT_MAX	(0xFFFFFFFF)
#define UINT_MIN	(0)
#define INT_MAX		(cellmax)
#define INT_MIN		(cellmin)

const NumberType NumberType_Int64 = view_as<NumberType>(3);

enum Architecture
{
	Architecture_x86,
	Architecture_x64
};

//////////////////////////////////////////////////////////////////////////////
// ADDRESS FUNCTIONS                                                        //
//////////////////////////////////////////////////////////////////////////////

/**
 * Get this architecture's pointer size. (4 = 32-bit, 8 = 64-bit)
 * 
 * @return				Pointer size of the architecture used for this program.
 */
stock int GetPointerSize()
{
	return Native_GetPointerSize();
}

/**
 * Returns whether the architecture used currently is x86-32 or x86-64.
 * 
 * @return				The architecture used.
 */
stock Architecture GetArchitecture()
{
	if (GetPointerSize() == 4)
		return Architecture_x86;
	return Architecture_x64;
}

/**
 * Dereferences a 64-bit address.
 * 
 * @param address   	An int64_t address to dereference from.
 * @param size      	The bit-width of the value located at the address.
 * @return          	An int64_t object.
 */
stock int64_t LoadFromAddress64(int64_t address, NumberType size)
{
	any returnBuffer[2];
	Native_LoadFromAddress64(address, size, returnBuffer);
	
	// This has to be done to prevent a packed/unpacked array warning. 
	int64_t returnObj;
	returnObj.low = returnBuffer[0], returnObj.high = returnBuffer[1];
	return returnObj;
}

/**
 * Stores a value into a 64-bit address.
 * 
 * @param address		An int64_t address to store a value in.
 * @param size			The bit-width of the value to store.
 * @param setMemAccess	Sets the memory access if toggled (which is the case by default).
 * 						May be necessary for some regions of memory that are read-only.
 */
stock void StoreToAddress64(int64_t address, NumberType size, int64_t buffer, bool setMemAccess = true)
{
	Native_StoreToAddress64(address, size, buffer, setMemAccess);
}

/**
 * Takes in a pseudo-address (represented in 32 bits) and outputs an absolute int64_t address.
 * 
 * @param pseudoAddress	The pseudo-address to be converted.
 * @return				The absolute address as an int64_t.
 */
stock int64_t FromPseudoAddress(Address pseudoAddress)
{
	any returnBuffer[2];
	Native_FromPseudoAddress(pseudoAddress, returnBuffer);

	int64_t returnObj;
	returnObj.low = returnBuffer[0], returnObj.high = returnBuffer[1];
	return returnObj;
}

/**
 * Takes in an absolute address (represented as int64_t) and outputs a 32-bit pseudo-address.
 * 
 * @param address64		The absolute address to be converted.
 * @return				The pseudo-address represented as a 32-bit value.
 */
stock Address ToPseudoAddress(int64_t address64)
{
	return Native_ToPseudoAddress(address64);
}

/**
 * Gets the entity address of an entity as an int64_t.
 * 
 * @param entity		The entity index (or entity reference) to get the address of.
 * @return				The absolute address of the entity as an int64_t.
 */
stock int64_t GetEntityAddress64(int entity)
{
	any returnBuffer[2];
	Native_GetEntityAddress64(entity, returnBuffer);

	int64_t returnObj;
	returnObj.low = returnBuffer[0], returnObj.high = returnBuffer[1];
	return returnObj;
}

//////////////////////////////////////////////////////////////////////////////
// INT64_T ARITHMETIC FUNCTIONS                                             //
//////////////////////////////////////////////////////////////////////////////

/**
 * Adds an int64_t to an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t AddInt64(int64_t left, int64_t right)
{
	int64_t result;
	Native_AddInt64(left, right, result);
	return result;
}

/**
 * Subs an int64_t from an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t SubInt64(int64_t left, int64_t right)
{
	int64_t result;
	Native_SubInt64(left, right, result);
	return result;
}

/**
 * Multiplies an int64_t by an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t MulInt64(int64_t left, int64_t right)
{
	int64_t result;
	Native_MulInt64(left, right, result);
	return result;
}

/**
 * Divides an int64_t by an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t DivInt64(int64_t left, int64_t right)
{
	int64_t result;
	Native_DivInt64(left, right, result);
	return result;
}

/**
 * Adds an int to an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntAddInt64(int64_t left, int right)
{
	int64_t result;
	int64_t buffer;
	buffer.low = right;
	Native_AddInt64(left, buffer, result);
	return result;
}

/**
 * Subtracts an int from an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntSubInt64(int64_t left, int right)
{
	int64_t result;
	int64_t buffer;
	buffer.low = right;
	Native_SubInt64(left, buffer, result);
	return result;
}

/**
 * Multiplies an int64_t by an int.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntMulInt64(int64_t left, int right)
{
	int64_t result;
	int64_t buffer;
	buffer.low = right;
	Native_MulInt64(left, buffer, result);
	return result;
}

/**
 * Divides an int64_t by an int.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntDivInt64(int64_t left, int right)
{
	int64_t result;
	int64_t buffer;
	buffer.low = right;
	Native_DivInt64(left, buffer, result);
	return result;
}

//////////////////////////////////////////////////////////////////////////////
// INT64_T BITWISE FUNCTIONS                                                //
//////////////////////////////////////////////////////////////////////////////

/**
 * ANDs an int64_t with an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t AndInt64(int64_t left, int64_t right)
{
	int64_t result;
	result.low = left.low & right.low, result.high = left.high & right.high;
	return result;
}

/**
 * ORs an int64_t with an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t OrInt64(int64_t left, int64_t right)
{
	int64_t result;
	result.low = left.low | right.low, result.high = left.high | right.high;
	return result;
}

/**
 * XORs an int64_t with an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t XorInt64(int64_t left, int64_t right)
{
	int64_t result;
	result.low = left.low ^ right.low, result.high = left.high ^ right.high;
	return result;
}

/**
 * Shifts an int64_t left by an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t LtsInt64(int64_t left, int64_t right)
{
	int64_t result;
	Native_LtsInt64(left, right, result);
	return result;
}

/**
 * Shifts an int64_t right by an int64_t.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int64_t value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t RtsInt64(int64_t left, int64_t right)
{
	int64_t result;
	Native_RtsInt64(left, right, result);
	return result;
}

/**
 * ANDs an int64_t with an int.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntAndInt64(int64_t left, int right)
{
	int64_t result;
	result.low = left.low & right, result.high = 0;
	return result;
}

/**
 * ORs an int64_t with an int.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntOrInt64(int64_t left, int right)
{
	int64_t result;
	result.low = left.low | right, result.high = left.high;
	return result;
}

/**
 * XORs an int64_t with an int.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntXorInt64(int64_t left, int right)
{
	int64_t result;
	result.low = left.low ^ right, result.high = left.high;
	return result;
}

/**
 * Shifts an int64_t left by an int.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntLtsInt64(int64_t left, int right)
{
	int64_t result;
	int64_t buffer;
	buffer.low = right;
	Native_LtsInt64(left, buffer, result);
	return result;
}

/**
 * Shifts an int64_t right by an int.
 * 
 * @param left			The left-most int64_t value.
 * @param right			The right-most int value.
 * @return				The result of the operation as an int64_t.
 */
stock int64_t IntRtsInt64(int64_t left, int right)
{
	int64_t result;
	int64_t buffer;
	buffer.low = right;
	Native_RtsInt64(left, buffer, result);
	return result;
}

/**
 * Inverts all of the bits in an int64_t value.
 * 
 * @param value			The int64_t value.
 * @return				An int64_t value after the NOT operation.
 */
stock int64_t NotInt64(int64_t value)
{
	int64_t result;
	result.low = ~value.low, result.high = ~value.high;
	return result;
}

//////////////////////////////////////////////////////////////////////////////
// INT64_T ENUM STRUCT                                                      //
//////////////////////////////////////////////////////////////////////////////

// A little-endian 64-bit integer structure.
enum struct int64_t
{
	// Fields.
    int low;
    int high;

	// Assignment.
	void Assign(int right)
	{
		this.low = right;
		this.high = 0;
	}
	void Assign64(int64_t right)
	{
		this.low = right.low;
		this.high = right.high;
	}

	// Arithmetic operations.
	void Add(int right)
	{
		int64_t buffer;
		buffer.low = right;
		Native_AddInt64(this, buffer, this);
	}
	void Sub(int right)
	{
		int64_t buffer;
		buffer.low = right;
		Native_SubInt64(this, buffer, this);
	}
	void Mul(int right)
	{
		int64_t buffer;
		buffer.low = right;
		Native_MulInt64(this, buffer, this);
	}
	void Div(int right)
	{
		int64_t buffer;
		buffer.low = right;
		Native_DivInt64(this, buffer, this);
	}
	void Add64(int64_t right)
	{
		Native_AddInt64(this, right, this);
	}
	void Sub64(int64_t right)
	{
		Native_SubInt64(this, right, this);
	}
	void Mul64(int64_t right)
	{
		Native_MulInt64(this, right, this);
	}
	void Div64(int64_t right)
	{
		Native_DivInt64(this, right, this);
	}

	// Bitwise operations.
	void And(int right)
	{
		this.low &= right;
		this.high = 0;
	}
	void Or(int right)
	{
		this.low |= right;
	}
	void Xor(int right)
	{
		this.low ^= right;
	}
	void Lts(int right)
	{
		int64_t buffer;
		buffer.low = right;
		Native_LtsInt64(this, buffer, this);
	}
	void Rts(int right)
	{
		int64_t buffer;
		buffer.low = right;
		Native_RtsInt64(this, buffer, this);
	}
	void And64(int64_t right)
	{
		this.low &= right.low;
		this.high = right.high;
	}
	void Or64(int64_t right)
	{
		this.low |= right.low;
		this.high |= right.high;
	}
	void Xor64(int64_t right)
	{
		this.low ^= right.low;
		this.high &= right.high;
	}
	void Lts64(int64_t right)
	{
		Native_LtsInt64(this, right, this);
	}
	void Rts64(int64_t right)
	{
		Native_RtsInt64(this, right, this);
	}
	void Not()
	{
		this.low = ~this.low;
		this.high = ~this.high;
	}
}

//////////////////////////////////////////////////////////////////////////////
// NATIVES                                                                  //
//////////////////////////////////////////////////////////////////////////////

native int Native_GetPointerSize();
native void Native_LoadFromAddress64(any address[2], NumberType size, any buffer[2]);
native void Native_StoreToAddress64(any address[2], NumberType size, any buffer[2], bool setMemAccess = true);
native void Native_FromPseudoAddress(Address pseudoAddress, any address64[2]);
native Address Native_ToPseudoAddress(any address64[2]);
native void Native_GetEntityAddress64(int entity, any address64[2]);

native void Native_AddInt64(any left[2], any right[2], any result[2]);
native void Native_SubInt64(any left[2], any right[2], any result[2]);
native void Native_MulInt64(any left[2], any right[2], any result[2]);
native void Native_DivInt64(any left[2], any right[2], any result[2]);

native void Native_LtsInt64(any left[2], any right[2], any result[2]);
native void Native_RtsInt64(any left[2], any right[2], any result[2]);

//////////////////////////////////////////////////////////////////////////////
// EXTENSION INTERFACE                                                      //
//////////////////////////////////////////////////////////////////////////////

public Extension __ext_sm_address64 = 
{
	name = "SM-Address64",
	file = "sm-address64.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};
