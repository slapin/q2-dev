#include <stddef.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "microgame.h"

static game_import_t *gi;
static game_export_t globals;
static game_locals_t game;
static edict_t *g_edicts;

static cvar_t *gun_x, *gun_y, *gun_z;
static cvar_t *sv_rollspeed, *sv_rollangle, *sv_maxvelocity,
	      *sv_gravity, *dedicated, *sv_cheats;
static cvar_t *oldsave, *maxentities, *maxclients;

/* ent - item, other - client */
static qboolean Pickup_Squishy(edict_t *ent, edict_t *other)
{
	return true;
}
gitem_t	itemlist[] = 
{
	{
		NULL
	},	// leave index 0 alone

	//
	// ARMOR
	//

/*QUAKED item_squishy (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_squishy", 
		Pickup_Squishy,
		NULL,
		NULL,
		NULL,
		"misc/squishy_pkup.wav",
		"models/items/squishy/tris.md2", 0,
		NULL,
/* icon */		"i_squishy",
/* pickup */	"Squishy",
/* width */		3,
		0,
		NULL,
		0,
		0,
		NULL,
		0,
/* precache */ ""
	},
	{
		NULL
	},	// end
};



/* Killme */

static void InitItems (void)
{
	game.num_items = sizeof(itemlist)/sizeof(itemlist[0]) - 1;
}

/*
============
InitGame

This will be called when the dll is first loaded, which
only happens when a new game is started or a save game
is loaded.
============
*/
static void InitGame (void)
{
	gi->dprintf ("InitGame\n");

	gun_x = gi->cvar ("gun_x", "0", 0);
	gun_y = gi->cvar ("gun_y", "0", 0);
	gun_z = gi->cvar ("gun_z", "0", 0);
	oldsave = gi->cvar("oldsave", "0", CVAR_ARCHIVE);
	//FIXME: sv_ prefix is wrong for these
	sv_rollspeed = gi->cvar ("sv_rollspeed", "200", 0);
	sv_rollangle = gi->cvar ("sv_rollangle", "2", 0);
	sv_maxvelocity = gi->cvar ("sv_maxvelocity", "2000", 0);
	sv_gravity = gi->cvar ("sv_gravity", "800", 0);

	// noset vars
	dedicated = gi->cvar ("dedicated", "0", CVAR_NOSET);

	// latched vars
	sv_cheats = gi->cvar ("cheats", "0", CVAR_SERVERINFO|CVAR_LATCH);
	gi->cvar ("gamename", GAMEVERSION , CVAR_SERVERINFO | CVAR_LATCH);
	gi->cvar ("gamedate", __DATE__ , CVAR_SERVERINFO | CVAR_LATCH);

	maxclients = gi->cvar ("maxclients", "4", CVAR_SERVERINFO | CVAR_LATCH);
#if 0
	maxspectators = gi->cvar ("maxspectators", "4", CVAR_SERVERINFO);
	deathmatch = gi->cvar ("deathmatch", "0", CVAR_LATCH);
	coop = gi->cvar ("coop", "0", CVAR_LATCH);
	skill = gi->cvar ("skill", "1", CVAR_LATCH);
#endif
	maxentities = gi->cvar ("maxentities", "1024", CVAR_LATCH);

#if 0
	// change anytime vars
	dmflags = gi->cvar ("dmflags", "0", CVAR_SERVERINFO);
	fraglimit = gi->cvar ("fraglimit", "0", CVAR_SERVERINFO);
	timelimit = gi->cvar ("timelimit", "0", CVAR_SERVERINFO);
	password = gi->cvar ("password", "", CVAR_USERINFO);
	spectator_password = gi->cvar ("spectator_password", "", CVAR_USERINFO);
	needpass = gi->cvar ("needpass", "0", CVAR_SERVERINFO);
	filterban = gi->cvar ("filterban", "1", 0);

	g_select_empty = gi->cvar ("g_select_empty", "0", CVAR_ARCHIVE);

	run_pitch = gi->cvar ("run_pitch", "0.002", 0);
	run_roll = gi->cvar ("run_roll", "0.005", 0);
	bob_up  = gi->cvar ("bob_up", "0.005", 0);
	bob_pitch = gi->cvar ("bob_pitch", "0.002", 0);
	bob_roll = gi->cvar ("bob_roll", "0.002", 0);

	// flood control
	flood_msgs = gi->cvar ("flood_msgs", "4", 0);
	flood_persecond = gi->cvar ("flood_persecond", "4", 0);
	flood_waitdelay = gi->cvar ("flood_waitdelay", "10", 0);

	// dm map list
	sv_maplist = gi->cvar ("sv_maplist", "", 0);
#endif

	// items
	InitItems();

	strcpy(game.helpmessage1, "");
	strcpy(game.helpmessage2, "");
	// initialize all entities for this game
	game.maxentities = maxentities->value;
	g_edicts =  gi->TagMalloc (game.maxentities * sizeof(g_edicts[0]), TAG_GAME);
	globals.edicts = g_edicts;
	globals.max_edicts = game.maxentities;

	// initialize all clients for this game
	game.maxclients = maxclients->value;
	game.clients = gi->TagMalloc (game.maxclients * sizeof(game.clients[0]), TAG_GAME);
	globals.num_edicts = game.maxclients+1;
}

static void ShutdownGame(void)
{
	gi->dprintf("ShutdownGame\n");
	gi->FreeTags(TAG_LEVEL);
	gi->FreeTags(TAG_GAME);
}

static void SpawnEntities(char *mapname, char *entities, char *spawnpoint)
{
	gi->dprintf("SpawnEntities mapname: %s, entities: %s, spawnpoint: %s\n", mapname,
			entities, spawnpoint);
}
static void WriteGame(char *filename, qboolean autosave)
{
	gi->dprintf("WriteGame: %s\n", filename);
}
static void ReadGame(char *filename)
{
	gi->dprintf("ReadGame: %s\n", filename);
}

static void WriteLevel (char *filename)
{
	gi->dprintf("WriteLevel: %s\n", filename);
}

static void ReadLevel (char *filename)
{
	gi->dprintf("ReadLevel: %s\n", filename);
}


static void ClientThink(edict_t *ent, usercmd_t *cmd)
{
	gi->dprintf("ClientThink\n");
}
/*
===============
Info_ValueForKey

Searches the string for the given
key and returns the associated value, or an empty string.
===============
*/
static char *Info_ValueForKey (char *s, char *key)
{
	char	pkey[512];
	static	char value[2][512];	// use two buffers so compares
								// work without stomping on each other
	static	int	valueindex;
	char	*o;
	
	valueindex ^= 1;
	if (*s == '\\')
		s++;
	while (1)
	{
		o = pkey;
		while (*s != '\\')
		{
			if (!*s)
				return "";
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value[valueindex];

		while (*s != '\\' && *s)
		{
			if (!*s)
				return "";
			*o++ = *s++;
		}
		*o = 0;

		if (!strcmp (key, pkey) )
			return value[valueindex];

		if (!*s)
			return "";
		s++;
	}
}


/*
===========
ClientConnect

Called when a player begins connecting to the server.
The game can refuse entrance to a client by returning false.
If the client is allowed, the connection process will continue
and eventually get to ClientBegin()
Changing levels will NOT cause this to be called again, but
loadgames will.
============
*/
static void ClientUserinfoChanged(edict_t *ent, char *userinfo);
qboolean ClientConnect (edict_t *ent, char *userinfo)
{
	char	*value;

	gi->dprintf("ClientConnect: %s\n", userinfo);
#if 0
	// check to see if they are on the banned IP list
	value = Info_ValueForKey (userinfo, "ip");
	if (SV_FilterPacket(value)) {
		Info_SetValueForKey(userinfo, "rejmsg", "Banned.");
		return false;
	}

	// check for a spectator
	value = Info_ValueForKey (userinfo, "spectator");
	if (deathmatch->value && *value && strcmp(value, "0")) {
		int i, numspec;

		if (*spectator_password->string && 
			strcmp(spectator_password->string, "none") && 
			strcmp(spectator_password->string, value)) {
			Info_SetValueForKey(userinfo, "rejmsg", "Spectator password required or incorrect.");
			return false;
		}

		// count spectators
		for (i = numspec = 0; i < maxclients->value; i++)
			if (g_edicts[i+1].inuse && g_edicts[i+1].client->pers.spectator)
				numspec++;

		if (numspec >= maxspectators->value) {
			Info_SetValueForKey(userinfo, "rejmsg", "Server spectator limit is full.");
			return false;
		}
	} else {
		// check for a password
		value = Info_ValueForKey (userinfo, "password");
		if (*password->string && strcmp(password->string, "none") && 
			strcmp(password->string, value)) {
			Info_SetValueForKey(userinfo, "rejmsg", "Password required or incorrect.");
			return false;
		}
	}
#endif


	// they can connect
	ent->client = game.clients + (ent - g_edicts - 1);

	// if there is already a body waiting for us (a loadgame), just
	// take it, otherwise spawn one from scratch
	if (ent->inuse == false)
	{
		// clear the respawning variables
		InitClientResp(ent->client);
		if (!game.autosaved || !ent->client->pers.weapon)
			InitClientPersistant (ent->client);
	}

	ClientUserinfoChanged(ent, userinfo);

	if (game.maxclients > 1)
		gi->dprintf ("%s connected\n", ent->client->pers.netname);

	ent->svflags = 0; // make sure we start with known default
	ent->client->pers.connected = true;
	return true;
}

/*
==================
Info_Validate

Some characters are illegal in info strings because they
can mess up the server's parsing
==================
*/
static qboolean Info_Validate (char *s)
{
	if (strstr (s, "\""))
		return false;
	if (strstr (s, ";"))
		return false;
	return true;
}
/*
============
va

does a varargs printf into a temp buffer, so I don't need to have
varargs versions of all text functions.
FIXME: make this buffer size safe someday
============
*/
static char *va(char *format, ...)
{
	va_list		argptr;
	static char		string[1024];
	
	va_start (argptr, format);
	vsnprintf (string, 1024, format, argptr);
	va_end (argptr);

	return string;	
}



/*
===========
ClientUserInfoChanged

called whenever the player updates a userinfo variable.

The game can override any of the settings in place
(forcing skins or names, etc) before copying it off.
============
*/
static void ClientUserinfoChanged (edict_t *ent, char *userinfo)
{
	char	*s;
	int		playernum;

	gi->dprintf("ClientUserinfoChanged: %s\n", userinfo);
	// check for malformed or illegal info strings
	if (!Info_Validate(userinfo))
	{
		strcpy (userinfo, "\\name\\badinfo\\skin\\male/grunt");
	}

	// set name
	s = Info_ValueForKey (userinfo, "name");
	strncpy (ent->client->pers.netname, s, sizeof(ent->client->pers.netname)-1);

	// set spectator
	s = Info_ValueForKey (userinfo, "spectator");
#if 0
	// spectators are only supported in deathmatch
	if (deathmatch->value && *s && strcmp(s, "0"))
		ent->client->pers.spectator = true;
	else
		ent->client->pers.spectator = false;
#endif

	// set skin
	s = Info_ValueForKey (userinfo, "skin");

	playernum = ent-g_edicts-1;

	// combine name and skin into a configstring
	gi->configstring (CS_PLAYERSKINS+playernum, va("%s\\%s", ent->client->pers.netname, s) );

#if 0
	// fov
	if (deathmatch->value && ((int)dmflags->value & DF_FIXED_FOV))
	{
		ent->client->ps.fov = 90;
	}
	else
	{
		ent->client->ps.fov = atoi(Info_ValueForKey(userinfo, "fov"));
		if (ent->client->ps.fov < 1)
			ent->client->ps.fov = 90;
		else if (ent->client->ps.fov > 160)
			ent->client->ps.fov = 160;
	}
#else
	ent->client->ps.fov = atoi(Info_ValueForKey(userinfo, "fov"));
	if (ent->client->ps.fov < 1)
		ent->client->ps.fov = 90;
	else if (ent->client->ps.fov > 160)
		ent->client->ps.fov = 160;
#endif

	// handedness
	s = Info_ValueForKey (userinfo, "hand");
	if (strlen(s))
	{
		ent->client->pers.hand = atoi(s);
	}

	// save off the userinfo in case we want to check something later
	strncpy (ent->client->pers.userinfo, userinfo, sizeof(ent->client->pers.userinfo)-1);
}


/*
===========
ClientDisconnect

Called when a player drops from the server.
Will not be called between levels.
============
*/
static void ClientDisconnect (edict_t *ent)
{
	int		playernum;

	gi->dprintf("ClientDisconnect\n");
	if (!ent->client)
		return;

	gi->bprintf(PRINT_HIGH, "%s disconnected\n", ent->client->pers.netname);

	// send effect
	gi->WriteByte(svc_muzzleflash);
	gi->WriteShort(ent-g_edicts);
	gi->WriteByte(MZ_LOGOUT);
	gi->multicast(ent->s.origin, MULTICAST_PVS);

	gi->unlinkentity(ent);
	ent->s.modelindex = 0;
	ent->solid = SOLID_NOT;
	ent->inuse = false;
	ent->classname = "disconnected";
	ent->client->pers.connected = false;

	playernum = ent-g_edicts-1;
	gi->configstring (CS_PLAYERSKINS+playernum, "");
}


static void ClientBegin(edict_t *ent)
{
	gi->dprintf("ClientBegin\n");
}

static void ClientCommand(edict_t *ent)
{
	gi->dprintf("ClientCommand\n");
}

static void G_RunFrame(void)
{
	gi->dprintf("G_RunFrame\n");
}

/* PATCH: matt */
/* use our own strncasecmp instead of this implementation */
#ifdef sun

#define Q_strncasecmp(s1, s2, n) (strncasecmp(s1, s2, n))

int Q_stricmp (char *s1, char *s2) {
        return strcasecmp(s1, s2);
}

#else

// FIXME: replace all Q_stricmp with Q_strcasecmp
int Q_stricmp (char *s1, char *s2)
{
#if defined(WIN32)
	return _stricmp (s1, s2);
#else
	return strcasecmp (s1, s2);
#endif
}
#endif

static void Svcmd_Test_f (void)
{
	gi->cprintf (NULL, PRINT_HIGH, "Svcmd_Test_f()\n");
}


/*
=================
ServerCommand

ServerCommand will be called when an "sv" command is issued.
The game can issue gi.argc() / gi.argv() commands to get the rest
of the parameters
=================
*/
static void ServerCommand (void)
{
	char	*cmd;

	cmd = gi->argv(1);
	if (Q_stricmp (cmd, "test") == 0)
		Svcmd_Test_f ();
	else
		gi->cprintf (NULL, PRINT_HIGH, "Unknown server command \"%s\"\n", cmd);
}


game_export_t *GetGameAPI (game_import_t *import)
{
	gi = import;
	globals.apiversion = GAME_API_VERSION;
	globals.Init = InitGame;
	globals.Shutdown = ShutdownGame;
	globals.SpawnEntities = SpawnEntities;
	globals.WriteGame = WriteGame;
	globals.ReadGame = ReadGame;
	globals.WriteLevel = WriteLevel;
	globals.ReadLevel = ReadLevel;
	globals.ClientThink = ClientThink;
	globals.ClientConnect = ClientConnect;
	globals.ClientUserinfoChanged = ClientUserinfoChanged;
	globals.ClientDisconnect = ClientDisconnect;
	globals.ClientBegin = ClientBegin;
	globals.ClientCommand = ClientCommand;

	globals.RunFrame = G_RunFrame;

	globals.ServerCommand = ServerCommand;

	globals.edict_size = sizeof(edict_t);

	return &globals;
}
