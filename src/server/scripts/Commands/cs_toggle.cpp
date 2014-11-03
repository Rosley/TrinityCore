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
#include "Language.h"
#include "Player.h"
#include "ChannelMgr.h"

class toggle_commandscript : public CommandScript
{
public:
	toggle_commandscript() : CommandScript("toggle_commandscript") { }

	ChatCommand* GetCommands() const
	{

		static ChatCommand toggleCommandTable[] =
		{
			{ "appear", rbac::RBAC_PERM_COMMAND_TOGGLE_APPEAR, false, &HandleToggleAppearCommand, "", NULL },
			{ "summon", rbac::RBAC_PERM_COMMAND_TOGGLE_SUMMON, false, &HandleToggleSummonCommand, "", NULL },
			{ "modify", rbac::RBAC_PERM_COMMAND_TOGGLE_MODIFY, false, &HandleToggleModifyCommand, "", NULL },
			{ "whispers", rbac::RBAC_PERM_COMMAND_WHISPERS,    false, &HandleWhispersCommand,     "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};

		static ChatCommand commandTable[] =
		{
			{ "toggle", rbac::RBAC_PERM_COMMAND_TOGGLE, false, NULL, "", toggleCommandTable },
			{ NULL, 0, false, NULL, "", NULL }
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

	static bool HandleWhispersCommand(ChatHandler* handler, char const* args)
	{
		if (!*args)
		{
			handler->PSendSysMessage(LANG_COMMAND_WHISPERACCEPTING, handler->GetSession()->GetPlayer()->isAcceptWhispers() ? handler->GetTrinityString(LANG_ON) : handler->GetTrinityString(LANG_OFF));
			return true;
		}

		std::string argStr = strtok((char*)args, " ");
		// whisper on
		if (argStr == "on")
		{
			handler->GetSession()->GetPlayer()->SetAcceptWhispers(true);
			handler->SendSysMessage(LANG_COMMAND_WHISPERON);
			return true;
		}

		// whisper off
		if (argStr == "off")
		{
			// Remove all players from the Gamemaster's whisper whitelist
			handler->GetSession()->GetPlayer()->ClearWhisperWhiteList();
			handler->GetSession()->GetPlayer()->SetAcceptWhispers(false);
			handler->SendSysMessage(LANG_COMMAND_WHISPEROFF);
			return true;
		}

		if (argStr == "remove")
		{
			std::string name = strtok(NULL, " ");
			if (normalizePlayerName(name))
			{
				if (Player* player = sObjectAccessor->FindPlayerByName(name))
				{
					handler->GetSession()->GetPlayer()->RemoveFromWhisperWhiteList(player->GetGUID());
					handler->PSendSysMessage(LANG_COMMAND_WHISPEROFFPLAYER, name.c_str());
					return true;
				}
				else
				{
					handler->PSendSysMessage(LANG_PLAYER_NOT_FOUND, name.c_str());
					handler->SetSentErrorMessage(true);
					return false;
				}
			}
		}
		handler->SendSysMessage(LANG_USE_BOL);
		handler->SetSentErrorMessage(true);
		return false;
	}

};

void AddSC_toggle_commandscript()
{
	new toggle_commandscript();
}