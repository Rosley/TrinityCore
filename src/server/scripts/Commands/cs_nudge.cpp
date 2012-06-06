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
Name: nudge_commandscript
%Complete: 100
Comment: All nudge related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"

class nudge_commandscript : public CommandScript
{
public:
    nudge_commandscript() : CommandScript("nudge_commandscript") { }

    ChatCommand* GetCommands() const
    {

        static ChatCommand nudgeCommandTable[] =
        {
            { "x",              SEC_GAMEMASTER,     false, &HandleNudgeXCommand,               "", NULL },
            { "y",              SEC_GAMEMASTER,     false, &HandleNudgeYCommand,               "", NULL },
            { "z",              SEC_GAMEMASTER,     false, &HandleNudgeZCommand,               "", NULL },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "nudge",          SEC_GAMEMASTER,     false, NULL,                  "", nudgeCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    static bool HandleNudgeXCommand(ChatHandler* handler, const char* args)
    {

        Player* player = handler->GetSession()->GetPlayer();

        float x = player->GetPositionX() + player->GetNudgeDistance();
        float y = player->GetPositionY();
        float z = player->GetPositionZ();
        uint32 mapid = player->GetMapId();

        // Knock them off the FP if they're flying, then continue
        if (player->isInFlight())
        {
            player->GetMotionMaster()->MovementExpired();
            player->CleanupAfterTaxiFlight();
        }

        // We aren't flying, time to move.
        player->TeleportTo(mapid, x, y, z, player->GetOrientation());
        return true;
    }

    static bool HandleNudgeYCommand(ChatHandler* handler, const char* args)
    {

        Player* player = handler->GetSession()->GetPlayer();

        float x = player->GetPositionX();
        float y = player->GetPositionY() + player->GetNudgeDistance();
        float z = player->GetPositionZ();
        uint32 mapid = player->GetMapId();

        // Knock them off the FP if they're flying, then continue
        if (player->isInFlight())
        {
            player->GetMotionMaster()->MovementExpired();
            player->CleanupAfterTaxiFlight();
        }

        // We aren't flying, time to move.
        player->TeleportTo(mapid, x, y, z, player->GetOrientation());
        return true;
    }

    static bool HandleNudgeZCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        std::string argstr = (char*)args;

        Player* player = handler->GetSession()->GetPlayer();

        uint32 mapid = player->GetMapId();
        float x = player->GetPositionX();
        float y = player->GetPositionY();
        float z;
    
        if (argstr == "up")
            z = player->GetPositionZ() + player->GetNudgeDistance();
        else if (argstr == "down")
            z = player->GetPositionZ() - player->GetNudgeDistance();
        else
        {
            handler->SendSysMessage("Only 'down' or 'up' are valid arguments");
            return true;
        }

        // Knock them off the FP if they're flying, then continue
        if (player->isInFlight())
        {
            player->GetMotionMaster()->MovementExpired();
            player->CleanupAfterTaxiFlight();
        }
    
        // We aren't flying, time to move.
        else
            player->SaveRecallPosition();
        player->TeleportTo(mapid, x, y, z, player->GetOrientation());

        return true;
    }
};

void AddSC_nudge_commandscript()
{
    new nudge_commandscript();
}
