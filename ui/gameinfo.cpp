//
// gameinfo.c
//

// *** This file is used by both the game and the user interface ***


#include "gameinfo.h"
#include "../game/weapons.h"


// Not "gi": g_main.cpp has a game_import_t of that name in the same module.
// MSVC mangles the type into a variable's symbol so the two never met; the
// Itanium ABI mangles by name alone and reports a duplicate.
gameinfo_import_t	gameinfoImport;

weaponData_t weaponData[WP_NUM_WEAPONS];
ammoData_t ammoData[AMMO_MAX];

extern void WP_LoadWeaponParms (void);

//
// Initialization - Read in files and parse into infos
//

/*
===============
GI_Init
===============
*/
void GI_Init( gameinfo_import_t *import ) {
	gameinfoImport = *import;

	WP_LoadWeaponParms ();
}
