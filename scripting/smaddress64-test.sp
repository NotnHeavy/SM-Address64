//////////////////////////////////////////////////////////////////////////////
// MADE BY NOTNHEAVY. USES GPL-3, AS PER REQUEST OF SOURCEMOD               //
//////////////////////////////////////////////////////////////////////////////

// NOTE: THIS CODE WAS TESTED ON WINDOWS, NOT LINUX.

#include <sourcemod>
#include <sdktools>
#include <smaddress64>

#define PLUGIN_NAME "smaddress64-test"

//////////////////////////////////////////////////////////////////////////////
// PLUGIN INFO                                                              //
//////////////////////////////////////////////////////////////////////////////

public Plugin myinfo =
{
    name = PLUGIN_NAME,
    author = "NotnHeavy",
    description = "Testing plugin for SM-Address64.",
    version = "1.3",
    url = "none"
};

//////////////////////////////////////////////////////////////////////////////
// INITIALISATION                                                           //
//////////////////////////////////////////////////////////////////////////////

public void OnPluginStart()
{
    LoadTranslations("common.phrases");
    PrintToServer("--------------------------------------------------------");
    
    // get the pointer size
    PrintToServer("pointer size: %u\n", GetPointerSize());

    // nt info
    int64_t KUSER_SHARED_DATA = { 0x7FFE0000, 0x00 };
    KUSER_SHARED_DATA.low += 0x26C;

    int64_t version;
    version = LoadFromAddress64(KUSER_SHARED_DATA, NumberType_Int64);
    PrintToServer("nt version: %i.%i\n", version.low, version.high);

    // pseudo address stuff
    GameData config = new GameData(PLUGIN_NAME);
    if (config == null)
        ThrowError("Could not find gamedata \"%s.txt\"", PLUGIN_NAME);
    Address random_subroutine = config.GetMemSig("i_honestly_dont_know_what_function_this_is_i_just_picked_a_random_one_from_ida");
    PrintToServer("random_subroutine: %u", random_subroutine);

    // convert to absolute address
    int64_t random_subroutine_absolute;
    random_subroutine_absolute = FromPseudoAddress(random_subroutine);
    PrintToServer("random_subroutine_absolute: low %u high %u", random_subroutine_absolute.low, random_subroutine_absolute.high);

    // convert back to pseudo-address
    PrintToServer("random_subroutine_absolute to pseduo-address: %u\n", ToPseudoAddress(random_subroutine_absolute));

    // arithmetic tests;
    int64_t a = { 2, 0 };
    int64_t b = { 3, 1 };

    PrintToServer("a: low %u high %u", a.low, a.high);
    a.Add64(b);
    PrintToServer("a + b: low %u high %u", a.low, a.high);

    int64_t c = { 244, 3 };
    int64_t d = { 594, 34134143 };
    int64_t f;

    PrintToServer("c: low %u high %u", c.low, c.high);
    f = MulInt64(c, d);
    PrintToServer("c * d: low %u high %u", f.low, f.high);

    int64_t g = { 489, 1 };
    int h = 1404;
    PrintToServer("g: low %u high %u", g.low, g.high);
    g.Sub(h);
    PrintToServer("g - h: low %u high %u", g.low, g.high);

    int64_t i = { 456, 4 };
    int64_t j = { 234, 0 };
    PrintToServer("j: low %u high %u", j.low, j.high);
    j.Or64(i);
    PrintToServer("j | i: low %u high %u", j.low, j.high);

    int64_t k = { 456, 4 };
    PrintToServer("k: low %u high %u", k.low, k.high);
    k = IntRtsInt64(k, 34);
    PrintToServer("k >> 34: low %u high %u\n", k.low, k.high);

    delete config;
    PrintToServer("\"%s\"::OnPluginStart()\n--------------------------------------------------------", PLUGIN_NAME);
}

public void OnMapStart()
{
    PrintToServer("--------------------------------------------------------");
    
    // entity stuff
    int64_t world_address;
    world_address = GetEntityAddress64(0);
    PrintToServer("world address: low %u high %u", world_address.low, world_address.high);

    // change m_vecOrigin for the giggles
    any m_vecOrigin_offset = FindSendPropInfo("CWorld", "m_vecOrigin");
    PrintToServer("m_vecOrigin::Offset: %u", m_vecOrigin_offset);

    /*
    // pray this doesn't break and cause massive explosions
    world_address.low += m_vecOrigin_offset;
    */

    world_address.Add(m_vecOrigin_offset);
    int64_t newVectorX = { view_as<int>(3124984.00), 0 };
    StoreToAddress64(world_address, NumberType_Int32, newVectorX, .setMemAccess = false);

    // now retrieve the vector using getentpropvector
    float vectorbuffer[3];
    GetEntPropVector(0, Prop_Send, "m_vecOrigin", vectorbuffer);
    PrintToServer("m_vecOrigin::x: %f\n", vectorbuffer[0]);

    PrintToServer("\"%s\"::OnMapStart()\n--------------------------------------------------------", PLUGIN_NAME);
}