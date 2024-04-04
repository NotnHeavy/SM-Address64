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

// Assumes that values are stored in little endian.
enum struct int64_t
{
    int low;
    int high;
}
#define NULL ({0, 0})

const NumberType NumberType_Int64 = view_as<NumberType>(3);

//////////////////////////////////////////////////////////////////////////////
// EXPOSED FUNCTIONS                                                        //
//////////////////////////////////////////////////////////////////////////////

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
// NATIVES                                                                  //
//////////////////////////////////////////////////////////////////////////////

native void Native_LoadFromAddress64(any address[2], NumberType size, any buffer[2]);
native void Native_StoreToAddress64(any address[2], NumberType size, any buffer[2], bool setMemAccess = true);
native void Native_FromPseudoAddress(Address pseudoAddress, any address64[2]);
native Address Native_ToPseudoAddress(any address64[2]);
native void Native_GetEntityAddress64(int entity, any address64[2]);

//////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT BELOW THIS LINE                                              //
//////////////////////////////////////////////////////////////////////////////

public Extension __ext_sm_address64 = 
{
	name = "SM-Address64",
	file = "sm-address64.ext.dll",
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