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
Name: cheat_commandscript
%Complete: 100
Comment: All cheat related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"

class cheat_commandscript : public CommandScript
{
public:
    cheat_commandscript() : CommandScript("cheat_commandscript") { }

    ChatCommand* GetCommands() const
    {

        static ChatCommand cheatCommandTable[] =
        {
            { "god",            SEC_GAMEMASTER,     false, &HandleGodModeCheatCommand,         "", NULL },
            { "casttime",       SEC_GAMEMASTER,     false, &HandleCasttimeCheatCommand,        "", NULL },
            { "castwhilemoving",SEC_GAMEMASTER,     false, &HandleCastWhileMovingCheatCommand, "", NULL },
            { "cooldown",       SEC_GAMEMASTER,     false, &HandleCoolDownCheatCommand,        "", NULL },
            { "fly",            SEC_GAMEMASTER,     false, &HandleFlyCheatCommand,             "", NULL },
            { "power",          SEC_GAMEMASTER,     false, &HandlePowerCheatCommand,           "", NULL },
            { "waterwalk",      SEC_GAMEMASTER,     false, &HandleWaterWalkCheatCommand,       "", NULL },
            { "triggerpass",    SEC_GAMEMASTER,     false, &HandleTriggerPassCheatCommand,     "", NULL },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "cheat",          SEC_GAMEMASTER,     false, NULL,                  "", cheatCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    static bool HandleGodModeCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
            argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_GOD)) ? "off" : "on";
		    /*if (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_GOD))
			    argstr = "off";	
		    else
			    argstr = "on";*/
	    }

	    if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatGod = false;
		    handler->SendSysMessage("Godmode is OFF. You can take damage.");
		    return true;
	    }
	    else if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatGod = true;
		    handler->SendSysMessage("Godmode is ON. You won't take damage.");
		    return true;
	    }
		
        return false;
    }

    static bool HandleCasttimeCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
		    argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_CASTTIME)) ? "off" : "on";
            /*if (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_CASTTIME))
			    argstr = "off";	
		    else
			    argstr = "on";*/
	    }

	    if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatCastTime = false;
		    handler->SendSysMessage("CastTime cheat is OFF. Your spells will have a casttime.");
		    return true;
	    }
	    else if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatCastTime = true;
		    handler->SendSysMessage("CastTime cheat is ON. Your spells won't have a casttime.");
		    return true;
	    }
		
        return false;
    }

    static bool HandleCoolDownCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
		    argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_COOLDOWN)) ? "off" : "on";
            /*if (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_COOLDOWN))
			    argstr = "off";	
		    else
			    argstr = "on";*/
	    }

	    if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatCoolDown = false;
		    handler->SendSysMessage("Cooldowncheat is OFF. You are on the global cooldown.");
		    return true;
	    }
	    else if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatCoolDown = true;
		    handler->SendSysMessage("Cooldowncheat is ON. You are not on the global cooldown.");
		    return true;
	    }

		return false;
    }

    static bool HandleFlyCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	    WorldPacket data(12);
	
	    if (!*args)
	    {
		    argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_FLY)) ? "off" : "on";
		    /*if (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_FLY))
			    argstr = "off";	
		    else
			    argstr = "on";*/
	    }
		
	    if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatFly = true;
		    data.SetOpcode(SMSG_MOVE_SET_CAN_FLY);
		    handler->SendSysMessage("Flymode Enabled.");
		    data.append(handler->GetSession()->GetPlayer()->GetPackGUID());
		    data << uint32(0);                                      // unknown
		    handler->GetSession()->GetPlayer()->SendMessageToSet(&data, true);
		    return true;
	    }
	    else if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatFly = false;
		    data.SetOpcode(SMSG_MOVE_UNSET_CAN_FLY);
		    handler->SendSysMessage("Flymode Disabled.");
		    data.append(handler->GetSession()->GetPlayer()->GetPackGUID());
		    data << uint32(0);                                      // unknown
		    handler->GetSession()->GetPlayer()->SendMessageToSet(&data, true);
		    return true;
	    }
		    
        return false;
    }

    static bool HandlePowerCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
            argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_POWER)) ? "off" : "on";
		    /*if (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_POWER))
			    argstr = "off";	
		    else
			    argstr = "on";*/
	    }

	    if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatPower = false;
		    handler->SendSysMessage("Powercheat is OFF. You need mana/rage/energy to use spells.");
		    return true;
	    }
	    else if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatPower = true;
		    handler->SendSysMessage("Powercheat is ON. Don't need mana/rage/energy to use spells.");
		    return true;
	    }
	
        return false;
    }

    static bool HandleWaterWalkCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
		    argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_WATERWALK)) ? "off" : "on";
		    if (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_WATERWALK))
			    argstr = "off";	
		    else
			    argstr = "on";
	    }

	    if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatWaterWalk = false;
		    handler->GetSession()->GetPlayer()->SetMovement(MOVE_LAND_WALK);                // OFF
		    handler->SendSysMessage("Waterwalking is OFF. You can't walk on water.");
		    return true;
	    }
	    else if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatWaterWalk = true;
		    handler->GetSession()->GetPlayer()->SetMovement(MOVE_WATER_WALK);               // ON
		    handler->SendSysMessage("Waterwalking is ON. You can walk on water.");
		    return true;
	    }
	
	    return false;
    }

    static bool HandleTriggerPassCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
	    {
		    argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_TRIGGERPASS)) ? "off" : "on";
		
		    /* if (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_TRIGGERPASS))
			    argstr = "off";	
		    else
			    argstr = "on"; */
	    }

	    if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatTriggerPass = false;
		    handler->SendSysMessage("Triggerpass is OFF. You need to be in a raidgroup to enter raids.");
		    return true;
	    }
	    else if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatTriggerPass = true;
		    handler->SendSysMessage("Triggerpass is ON. You can enter a raid without a group.");
		    return true;
	    }
		    
        return false;
    }

    static bool HandleCastWhileMovingCheatCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;
	
	    if (!*args)
		    argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(CHEAT_CASTWHILEMOVE)) ? "off" : "on";

	    if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatCastWhileMoving = false;
		    handler->SendSysMessage("CastMove is OFF. You can't cast while moving.");
		    return true;
	    }
	    else if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_cheatCastWhileMoving = true;
		    handler->SendSysMessage("CastMove is ON. You can can while moving.");
		    return true;
	    }
		    
        return false;
    }
};

void AddSC_cheat_commandscript()
{
    new cheat_commandscript();
}
