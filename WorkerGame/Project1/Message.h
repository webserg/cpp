#pragma once
#include "BaseGameEntity.h"
#include <string>

enum message_type
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
};


inline std::string MsgToStr(int msg)
{
	switch (msg)
	{
	case Msg_HiHoneyImHome:

		return "HiHoneyImHome";

	case Msg_StewReady:

		return "StewReady";

	default:

		return "Not recognized!";
	}
}

class Message
{	
public:
	const int sender;
	const int receiver;
	const int msg;
	const double delay;
	const double time;
	Message(int sender_i, int receive_i, int msg, double delay);
	~Message();
	bool operator<(const Message& rhs)const;
	bool operator>(const Message& rhs)const;

};

