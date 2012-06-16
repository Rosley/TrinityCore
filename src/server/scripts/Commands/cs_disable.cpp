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
Name: disable_commandscript
%Complete: 100
Comment: All disable related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "DisableMgr.h"

class disable_commandscript : public CommandScript
{
public:
    disable_commandscript() : CommandScript("disable_commandscript") { }

    ChatCommand* GetCommands() const
    {

        static ChatCommand disableCommandTable[] =
        {
            { "spell",          SEC_GAMEMASTER,     false, &HandleDisableSpellCommand,         "", NULL },
            { "displayid",      SEC_GAMEMASTER,     false, &HandleDisableDisplayIdCommand,     "", NULL },
            { "zone",           SEC_GAMEMASTER,     false, &HandleDisableZoneCommand,          "", NULL },
            { "gobject",        SEC_GAMEMASTER,     false, &HandleDisableGobjectCommand,       "", NULL },
            { "npc",            SEC_GAMEMASTER,     false, &HandleDisableNpcCommand,           "", NULL },
            { "item",           SEC_GAMEMASTER,     false, &HandleDisableItemCommand,          "", NULL },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "disable",        SEC_GAMEMASTER,     false, NULL,                "", disableCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    
    static void HandleDisables(ChatHandler* handler, char const* args, uint8 disableType)
    {
        if (!*args)
            return false;

        char* entryStr = strtok((char*)args, " ");
        uint32 entry = atoi((char*)spellIdStr);
        std::string disableTypeStr = "";

        switch(disableType)
        {
            case DISABLE_TYPE_SPELL:
                disableTypeStr = "spell";
                break;
            case DISABLE_TYPE_DISPLAYID:
                disableTypeStr = "displayid";
                break;
            case DISABLE_TYPE_ITEM:
                disableTypeStr = "item";
                break;
            case DISABLE_TYPE_NPC:
                disableTypeStr = "NPC";
                break;
            case DISABLE_TYPE_GOBJECT:
                disableTypeStr = "gameobject";
                break;
            case DISABLE_TYPE_ZONE:
                disableTypeStr = "zone";
                break;
            default:
                disableTypeStr = "[unknown disable type]";
                break;
        }

        if (entry <= 0)
            return false;

        std::string disableComment = strtok((std::string)NULL, " ");
    
        result = WorldDatabase.PQuery("SELECT * FROM disables WHERE entry = %u AND sourceType = %u", entry, disableType;

        if (result)
        {
            handler->PSendSysMessage("This %s (id %u) is already disabled.", disableTypeStr.c_str(), entry);
            return true;
        }

        PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_DISABLE);
        stmt->SetUint32(0, spellId);
        stmt->SetUint8(1, disableType);
        WorldDatabase.Execute(stmt);
                
        handler->PSendSysMessage("Disabled %s id %u for reason %s", disableTypeStr.c_str(), entry, disableComment.c_str());
        return true;
        
    }
    
    static bool HandleDisableSpellCommand(ChatHandler* handler, char const* args)
    {
        HandleDisables(handler, args, DISABLE_TYPE_SPELL);
        return true;
    }

    static bool HandleDisableZoneCommand(ChatHandler* handler, char const* args)
    {
        HandleDisables(handler, args, DISABLE_TYPE_ZONE);
        return true;
    }

    static bool HandleDisableNpcCommand(ChatHandler* handler, char const* args)
    {
        HandleDisables(handler, args, DISABLE_TYPE_NPC);
        return true;
    }

    static bool HandleDisableGobjectCommand(ChatHandler* handler, char const* args)
    {
        HandleDisables(handler, args, DISABLE_TYPE_GOBJECT);
        return true;
    }

    static bool HandleDisableDisplayIdCommand(ChatHandler* handler, char const* args)
    {
        HandleDisables(handler, args, DISABLE_TYPE_DISPLAYID);
        return true;
    }

    static bool HandleDisableItemCommand(ChatHandler* handler, char const* args)
    {
        HandleDisables(handler, args, DISABLE_TYPE_ITEM);
        return true;
    }

};

void AddSC_disable_commandscript()
{
    new disable_commandscript();
}
