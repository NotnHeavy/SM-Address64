//////////////////////////////////////////////////////////////////////////////
// MADE BY NOTNHEAVY. USES GPL-3, AS PER REQUEST OF SOURCEMOD               //
//////////////////////////////////////////////////////////////////////////////

// CALL THESE FUNCTIONS SAFELY!

#include <cstdint>

#include <sourcehook.h>
#include <sh_memory.h>

#include "addressing.hpp"
#include "extension.hpp"

//////////////////////////////////////////////////////////////////////////////
// GLOBALS                                                                  //
//////////////////////////////////////////////////////////////////////////////

enum struct NumberType
{
    NumberType_Int8,
    NumberType_Int16,
    NumberType_Int32,
    NumberType_Int64
};

//////////////////////////////////////////////////////////////////////////////
// ADDRESS NATIVES                                                          //
//////////////////////////////////////////////////////////////////////////////

static cell_t Native_GetPointerSize(IPluginContext* pContext, const cell_t* params)
{
    return sizeof(void*);
}

static cell_t Native_LoadFromAddress64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    uintptr_t* buffer;
    uintptr_t* address;
    uintptr_t** addressBuffer;
    const NumberType type = static_cast<NumberType>(params[2]);

    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&buffer));
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&addressBuffer));
    address = *addressBuffer;

    // Dereference the address and store its value into the return buffer (3rd parameter).
    switch (type)
    {
    case NumberType::NumberType_Int8:
        *buffer = *(int8_t*)(address);
        break;
    case NumberType::NumberType_Int16:
        *buffer = *(int16_t*)(address);
        break;
    case NumberType::NumberType_Int32:
        *buffer = *(int32_t*)address;
        break;
    case NumberType::NumberType_Int64:
        *buffer = *(int64_t*)address;
        break;
    default:
        pContext->ReportError("Invalid NumberType value %d", type);
        return 1;
    }

    return 0;
}

static cell_t Native_StoreToAddress64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    uintptr_t* buffer;
    uintptr_t* address;
    uintptr_t** addressBuffer;
    const NumberType type = static_cast<NumberType>(params[2]);
    const bool updateMemAccess = params[4];

    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&buffer));
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&addressBuffer));
    address = *addressBuffer;

    // Store the buffer value into the addres.
    switch (type)
    {
    case NumberType::NumberType_Int8:
        if (updateMemAccess)
            SourceHook::SetMemAccess(address, sizeof(int8_t), SH_MEM_READ | SH_MEM_WRITE | SH_MEM_EXEC);
        *(int8_t*)address = *(int8_t*)buffer;
        break;
    case NumberType::NumberType_Int16:
        if (updateMemAccess)
            SourceHook::SetMemAccess(address, sizeof(int16_t), SH_MEM_READ | SH_MEM_WRITE | SH_MEM_EXEC);
        *(int16_t*)address = *(int16_t*)buffer;
        break;
    case NumberType::NumberType_Int32:
        if (updateMemAccess)
            SourceHook::SetMemAccess(address, sizeof(int32_t), SH_MEM_READ | SH_MEM_WRITE | SH_MEM_EXEC);
        *(int32_t*)address = *(int32_t*)buffer;
        break;
    case NumberType::NumberType_Int64:
        if (updateMemAccess)
            SourceHook::SetMemAccess(address, sizeof(int64_t), SH_MEM_READ | SH_MEM_WRITE | SH_MEM_EXEC);
        *(int64_t*)address = *(int64_t*)buffer;
        break;
    default:
        pContext->ReportError("Invalid NumberType value %d", type);
        return 1;
    }

    return 0;
}

static cell_t Native_FromPseudoAddress(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    uintptr_t* buffer;
    const uint32_t pseudoAddress = static_cast<uint32_t>(params[1]);

    // Get the address to the address buffer parameter.
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&buffer));

    // Convert the pseudo-address to an absolute address.
#ifdef PLATFORM_X86
    *buffer = pseudoAddress;
#else
    *buffer = (uintptr_t)smutils->FromPseudoAddress(pseudoAddress);
#endif
    return 0;
}

static cell_t Native_ToPseudoAddress(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    uintptr_t* address;

    // Get the address to the address buffer parameter.
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&address));

    // Convert the absolute address to a pseudo-address.
#ifdef PLATFORM_X86
    return *address; // Just return the original address.
#else
    return smutils->ToPseudoAddress(reinterpret_cast<void*>(*address)); // no uintptr_t?
#endif
}

static cell_t Native_GetEntityAddress64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    CBaseEntity* pEntity = gamehelpers->ReferenceToEntity(params[1]);
    uintptr_t* buffer;

    // Obtain address to the entity address buffer and verify entity address.
    if (!pEntity)
    {
        pContext->ReportError("Entity %d (%d) is invalid", gamehelpers->ReferenceToIndex(params[1]), params[1]);
        return 1;
    }
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&buffer));

    // Store the entity address into the address buffer.
    *buffer = reinterpret_cast<uintptr_t>(pEntity);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
// INT64 ARITHMETIC NATIVES                                                 //
//////////////////////////////////////////////////////////////////////////////

static cell_t Native_AddInt64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    int64_t* left;
    int64_t* right;
    int64_t* result;
    
    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&left));
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&right));
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&result));

    // Perform add and return.
    *result = *left + *right;
    return 0;
}

static cell_t Native_SubInt64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    int64_t* left;
    int64_t* right;
    int64_t* result;
    
    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&left));
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&right));
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&result));

    // Perform add and return.
    *result = *left - *right;
    return 0;
}

static cell_t Native_MulInt64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    int64_t* left;
    int64_t* right;
    int64_t* result;
    
    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&left));
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&right));
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&result));

    // Perform add and return.
    *result = *left * *right;
    return 0;
}

static cell_t Native_DivInt64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    int64_t* left;
    int64_t* right;
    int64_t* result;
    
    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&left));
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&right));
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&result));

    // Perform add and return.
    *result = *left * *right;
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
// INT64 BITSHIFT NATIVES                                                   //
//////////////////////////////////////////////////////////////////////////////

static cell_t Native_LtsInt64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    int64_t* left;
    int64_t* right;
    int64_t* result;
    
    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&left));
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&right));
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&result));

    // Perform add and return.
    *result = *left << *right;
    return 0;
}

static cell_t Native_RtsInt64(IPluginContext* pContext, const cell_t* params)
{
    // Obtain parameters.
    int64_t* left;
    int64_t* right;
    int64_t* result;
    
    // Obtain addresses to buffers.
    pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&left));
    pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&right));
    pContext->LocalToPhysAddr(params[3], reinterpret_cast<cell_t**>(&result));

    // Perform add and return.
    *result = *left >> *right;
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
// NATIVE EXPORTS                                                           //
//////////////////////////////////////////////////////////////////////////////

sp_nativeinfo_t g_AddressNatives[] = {
    { "Native_GetPointerSize", Native_GetPointerSize },
    { "Native_LoadFromAddress64",   Native_LoadFromAddress64 },
    { "Native_StoreToAddress64",    Native_StoreToAddress64 },
    { "Native_FromPseudoAddress",   Native_FromPseudoAddress },
    { "Native_ToPseudoAddress",     Native_ToPseudoAddress },
    { "Native_GetEntityAddress64",  Native_GetEntityAddress64 },

    { "Native_AddInt64",            Native_AddInt64 },
    { "Native_SubInt64",            Native_SubInt64 },
    { "Native_MulInt64",            Native_MulInt64 },
    { "Native_DivInt64",            Native_DivInt64 },

    { "Native_LtsInt64",            Native_LtsInt64 },
    { "Native_RtsInt64",            Native_RtsInt64 },

    { nullptr,                      nullptr }
};