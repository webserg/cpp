#include "Message.h"
#include <filesystem>
using namespace std::chrono;

Message::Message(int sender_i, int receive_i, int msg, double delay):sender{sender_i},receiver{receive_i},msg{msg},delay{delay},
time{ 1.0 }
{}
Message::~Message()
{
}

bool Message::operator<(const Message& rhs) const{
	return time < rhs.time;
}

bool Message::operator>(const Message& rhs) const
{
	return time > rhs.time;
}