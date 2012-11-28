/*
   Copyright (C) 1999-2007 id Software, Inc. and contributors.
   For a list of contributors, see the accompanying CONTRIBUTORS file.

   This file is part of GtkRadiant.

   GtkRadiant is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   GtkRadiant is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GtkRadiant; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "plugin.h"
#include "ufoai_filters.h"

#define CMD_SEP "-"
#define CMD_ABOUT "About..."
// =============================================================================
// Globals

// function tables
_QERFuncTable_1 g_FuncTable;
_QERQglTable g_QglTable;
_QERFileSystemTable g_FileSystemTable;
_QEREntityTable g_EntityTable;
_QERAppDataTable g_DataTable;

// the gtk widget
void *g_pMainWidget;

// =============================================================================
// plugin implementation

#define PLUGIN_NAME "UFO:AI plugin"
#define PLUGIN_VERSION "0.1"

//backwards for some reason
static const char *PLUGIN_COMMANDS = CMD_ABOUT ";" CMD_SEP;
static const char *PLUGIN_ABOUT = _( "UFO: Alien Invasion plugin " PLUGIN_VERSION "\nby Martin Gerhardy" );

#define NUM_TOOLBAR_BUTTONS FILTER_MAX
typedef struct toolbar_button_info_s
{
	const char *image;
	const char *text;
	const char *tip;
	void ( *func )();
	IToolbarButton::EType type;
} toolbar_button_info_t;

static const toolbar_button_info_t toolbar_buttons[NUM_TOOLBAR_BUTTONS] =
{
	{
		"ufoai_actorclip.bmp",
		_( "Filter actorclip" ),
		_( "Actorclip" ),
		DoActorClipFiltering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_weaponclip.bmp",
		_( "Filter weaponclip" ),
		_( "Weaponclip" ),
		DoWeaponClipFiltering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_nodraw.bmp",
		_( "Filter nodraw" ),
		_( "NoDraw" ),
		DoNoDrawFiltering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_stepon.bmp",
		_( "Filter stepon" ),
		_( "Stepon" ),
		DoSteponFiltering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level1.bmp",
		_( "Filter level1" ),
		_( "Level 1" ),
		DoLevel1Filtering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level2.bmp",
		_( "Filter level2" ),
		_( "Level 2" ),
		DoLevel2Filtering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level3.bmp",
		_( "Filter level3" ),
		_( "Level 3" ),
		DoLevel3Filtering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level4.bmp",
		_( "Filter level4" ),
		_( "Level 4" ),
		DoLevel4Filtering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level5.bmp",
		_( "Filter level5" ),
		_( "Level 5" ),
		DoLevel5Filtering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level6.bmp",
		_( "Filter level6" ),
		_( "Level 6" ),
		DoLevel6Filtering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level7.bmp",
		_( "Filter level7" ),
		_( "Level 7" ),
		DoLevel7Filtering,
		IToolbarButton::eToggleButton
	},
	{
		"ufoai_level8.bmp",
		_( "Filter level8" ),
		_( "Level 8" ),
		DoLevel8Filtering,
		IToolbarButton::eToggleButton
	},
};

class UFOAIButton : public IToolbarButton
{
public:
const toolbar_button_info_s *bi;
virtual const char* getImage() const {
	return bi->image;
}
virtual const char* getText() const {
	return bi->text;
}
virtual const char* getTooltip() const {
	return bi->tip;
}
virtual void activate() const {
	bi->func();
	return ;
}
virtual EType getType() const {
	return bi->type;
}
};

UFOAIButton g_ufoaibuttons[NUM_TOOLBAR_BUTTONS];

unsigned int ToolbarButtonCount( void ){
	return NUM_TOOLBAR_BUTTONS;
}

const IToolbarButton* GetToolbarButton( unsigned int index ){
	g_ufoaibuttons[index].bi = &toolbar_buttons[index];
	return &g_ufoaibuttons[index];
}

extern "C" const char* QERPlug_Init( void *hApp, void* pMainWidget ){
	g_pMainWidget = pMainWidget;

	UFOAIFilterInit();

	return PLUGIN_NAME;
}

extern "C" const char* QERPlug_GetName( void ){
	return (char *) PLUGIN_NAME;
}

extern "C" const char* QERPlug_GetCommandList( void ){
	return (char *) PLUGIN_COMMANDS;
}

extern "C" void QERPlug_Dispatch( const char *p, vec3_t vMin, vec3_t vMax, bool bSingleBrush ){
	if ( !strcmp( p, CMD_ABOUT ) ) {
		g_FuncTable.m_pfnMessageBox( NULL, PLUGIN_ABOUT, _( "About" ), MB_OK, NULL );
	}
	else {
		Sys_Printf( "Message: %s\n", p );
	}
}

// =============================================================================
// SYNAPSE

CSynapseServer* g_pSynapseServer = NULL;
CSynapseClientUFOAI g_SynapseClient;

#if __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif
extern "C" CSynapseClient * SYNAPSE_DLL_EXPORT Synapse_EnumerateInterfaces( const char *version, CSynapseServer *pServer ){
#if __GNUC__ >= 4
#pragma GCC visibility pop
#endif
	if ( strcmp( version, SYNAPSE_VERSION ) ) {
		Syn_Printf( "ERROR: synapse API version mismatch: should be '" SYNAPSE_VERSION "', got '%s'\n", version );
		return NULL;
	}
	g_pSynapseServer = pServer;
	g_pSynapseServer->IncRef();
	Set_Syn_Printf( g_pSynapseServer->Get_Syn_Printf() );

	g_SynapseClient.AddAPI( TOOLBAR_MAJOR, UFOAI_MINOR, sizeof( _QERPlugToolbarTable ) );
	g_SynapseClient.AddAPI( PLUGIN_MAJOR, UFOAI_MINOR, sizeof( _QERPluginTable ) );

	g_SynapseClient.AddAPI( RADIANT_MAJOR, NULL, sizeof( g_FuncTable ), SYN_REQUIRE, &g_FuncTable );
	g_SynapseClient.AddAPI( QGL_MAJOR, NULL, sizeof( g_QglTable ), SYN_REQUIRE, &g_QglTable );
	g_SynapseClient.AddAPI( VFS_MAJOR, "*", sizeof( g_FileSystemTable ), SYN_REQUIRE, &g_FileSystemTable );
	// get worldspawn
	g_SynapseClient.AddAPI( ENTITY_MAJOR, NULL, sizeof( g_EntityTable ), SYN_REQUIRE, &g_EntityTable );
	// selected brushes
	g_SynapseClient.AddAPI( DATA_MAJOR, NULL, sizeof( g_DataTable ), SYN_REQUIRE, &g_DataTable );

	return &g_SynapseClient;
}

bool CSynapseClientUFOAI::RequestAPI( APIDescriptor_t *pAPI ){
	if ( !strcmp( pAPI->major_name, PLUGIN_MAJOR ) ) {
		_QERPluginTable* pTable = static_cast<_QERPluginTable*>( pAPI->mpTable );

		pTable->m_pfnQERPlug_Init = QERPlug_Init;
		pTable->m_pfnQERPlug_GetName = QERPlug_GetName;
		pTable->m_pfnQERPlug_GetCommandList = QERPlug_GetCommandList;
		pTable->m_pfnQERPlug_Dispatch = QERPlug_Dispatch;
		return true;
	}
	else if ( !strcmp( pAPI->major_name, TOOLBAR_MAJOR ) ) {
		_QERPlugToolbarTable* pTable = static_cast<_QERPlugToolbarTable*>( pAPI->mpTable );

		pTable->m_pfnToolbarButtonCount = &ToolbarButtonCount;
		pTable->m_pfnGetToolbarButton = &GetToolbarButton;
		return true;
	}

	Syn_Printf( "ERROR: RequestAPI( '%s' ) not found in '%s'\n", pAPI->major_name, GetInfo() );
	return false;
}

#include "version.h"

const char* CSynapseClientUFOAI::GetInfo(){
	return PLUGIN_NAME " plugin built " __DATE__ " " RADIANT_VERSION;
}

const char* CSynapseClientUFOAI::GetName(){
	return PLUGIN_NAME;
}
