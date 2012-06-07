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
            { NULL,             0,                  false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "toggle",         SEC_GAMEMASTER,     false, NULL,                  "", toggleCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }
};

void AddSC_toggle_commandscript()
{
    new toggle_commandscript();
}
