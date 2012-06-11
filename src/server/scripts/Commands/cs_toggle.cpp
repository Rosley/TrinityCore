/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
Name: toggle_commandscript
%Complete: 100
Comment: All toggle related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"

class toggle_commandscript : public CommandScript
{
public:
    toggle_commandscript() : CommandScript("toggle_commandscript") { }

    ChatCommand* GetCommands() const
    {

        static ChatCommand toggleCommandTable[] =
        {
            { "modify",         SEC_MODERATOR,      false, &HandleToggleModifyCommand,         "", NULL },
            { "appear",         SEC_MODERATOR,      false, &HandleToggleAppearCommand,         "", NULL },
            { "summon",         SEC_MODERATOR,      false, &HandleToggleSummonCommand,         "", NULL },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "toggle",         SEC_GAMEMASTER,     false, NULL,                  "", toggleCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    static bool HandleToggleModifyCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
		    if (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_MODIFY))
			    argstr = "off";	
		    else
			    argstr = "on";
	    }

	    if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleModify = true;
		    handler->SendSysMessage("Modify is ON. Players can use commands on you.");
		    return true;
	    }
	    else if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleModify = false;
		    handler->SendSysMessage("Modify is OFF. Players can't use commands on you.");
		    return true;
	    }
		    
        return false;
    }

    static bool HandleToggleAppearCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
		    if (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_APPEAR))
			    argstr = "off";	
		    else
			    argstr = "on";
	    }

	    if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleAppear = true;
		    handler->SendSysMessage("Appear is ON. Players can appear to you.");
		    return true;
	    }
	    else if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleAppear = false;
		    handler->SendSysMessage("Appear is OFF. Players can't appear to you.");
		    return true;
	    }
		    
        return false;
    }

    static bool HandleToggleSummonCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
		    if (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_SUMMON))
			    argstr = "off";	
		    else
			    argstr = "on";
	    }

	    if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleSummon = true;
		    handler->SendSysMessage("Summon is ON. Players can summon you.");
		    return true;
	    }
	    else if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleSummon = false;
		    handler->SendSysMessage("Summon is OFF. Players can't summon you.");
		    return true;
	    }
		    
        return false;
    }

};

void AddSC_toggle_commandscript()
{
    new toggle_commandscript();
}
