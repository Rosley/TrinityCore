#include "ScriptPCH.h"
#include "Chat.h"

#define FACTION_SPECIFIC 0

std::string GetNameLink(Player* player)
{
	std::string name = player->GetName();
	std::string color;
	switch (player->getClass())
	{
	case CLASS_DEATH_KNIGHT:
		color = "|cffff0000";
		break;
	case CLASS_DRUID:
		color = "|cffff0000";
		break;
	case CLASS_HUNTER:
		color = "|cffff0000";
		break;
	case CLASS_MAGE:
		color = "|cffff0000";
		break;
	case CLASS_PALADIN:
		color = "|cffff0000";
		break;
	case CLASS_PRIEST:
		color = "|cffff0000";
		break;
	case CLASS_ROGUE:
		color = "|cffff0000";
		break;
	case CLASS_SHAMAN:
		color = "|cffff0000";
		break;
	case CLASS_WARLOCK:
		color = "|cffff0000";
		break;
	case CLASS_WARRIOR:
		color = "|cffff0000";
		break;
	}
	return "|Hplayer:" + name + "|h|cffFFFFFF[" + color + name + "|cffFFFFFF]|h|r";
}

class cs_world_chat : public CommandScript
{
public:
	cs_world_chat() : CommandScript("cs_world_chat"){}

	ChatCommand * GetCommands() const
	{
		static ChatCommand WorldChatCommandTable[] =
		{
			{ "announce", rbac::RBAC_PERM_COMMAND_WORLD_CHAT, true, &HandleWorldChatCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};

		return WorldChatCommandTable;
	}

	static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
	{
		if (!handler->GetSession()->GetPlayer()->CanSpeak())
			return false;
		std::string temp = args;

		if (!args || temp.find_first_not_of(' ') == std::string::npos)
			return false;

		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();

		switch (player->GetSession()->GetSecurity())
		{
			// Player
		case SEC_PLAYER:
			msg += "|c1f40af20[Viral-WoW] |cffffff00<Player> ";
			msg += GetNameLink(player);
			msg += " |c1f40af20announces:|cffffff00 ";
			break;
			// Contributor
		case SEC_MODERATOR:
			msg += "|c1f40af20[Viral-WoW] |cffff6060<Contributor> ";
			msg += GetNameLink(player);
			msg += " |c1f40af20announces:|cffffff00 ";
			break;
			// Moderator
		case SEC_GAMEMASTER:
			msg += "|c1f40af20[Viral-WoW] |cff71C671<Moderator> ";
			msg += GetNameLink(player);
			msg += " |c1f40af20announces:|cffffff00 ";
			break;
			// Developer
		case SEC_ADMINISTRATOR:
			msg += "|c1f40af20[Viral-WoW] |cffDA70D6<Developer> ";
			msg += GetNameLink(player);
			msg += " |c1f40af20announces:|cffffff00 ";
			break;
			// Administrator
		case SEC_CONSOLE:
			msg += "|c1f40af20[Viral-WoW] |cff00ffff<Administrator> ";
			msg += GetNameLink(player);
			msg += " |c1f40af20announces:|cffffff00 ";
			break;

		}

		msg += args;
		if (FACTION_SPECIFIC)
		{
			SessionMap sessions = sWorld->GetAllSessions();
			for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
				if (Player* plr = itr->second->GetPlayer())
					if (plr->GetTeam() == player->GetTeam())
						sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), plr);
		}
		else
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);

		return true;
	}
};

void AddSC_cs_world_chat()
{
	new cs_world_chat();
}