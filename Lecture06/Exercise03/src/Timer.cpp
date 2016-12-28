#include "Timer.hpp"

Timer::Timer() : AI("Timer")
{
	Send(ID_TIMER_CLOCK, NULL);
}

void Timer::addEvent(AI* ai, unsigned int sleeptime, unsigned long id, Message* reply)
{
	Event* event = new Event(ai, sleeptime, id, reply);
	Send(ID_TIMER_NEW_EVENT, event);
}


void Timer::executeEvent(Event* event)
{
	event->ptr->Send(event->id, event->msg);
}

void Timer::handleClock()
{
	std::cout << getName() << "\tClock" << std::endl;
	for (auto it = events.begin(); it!=events.end();)
	{
		if ((*it)->sleeptime == 0)
		{
			executeEvent(*it);
			it = events.erase(it);
		} else {
			(*it)->sleeptime -= 1;
			++it;
		}
	}
	sleep(1);
	Send(ID_TIMER_CLOCK, NULL);
}

void Timer::handleNewEvent(Event* event)
{
	events.push_back(event);
}

void Timer::handleMsg(unsigned long id, Message*& msg)
{
	switch(id)
	{
		case ID_TIMER_CLOCK:
			handleClock();
			break;
		case ID_TIMER_NEW_EVENT:
			handleNewEvent(static_cast<Event*>(msg));
			msg = NULL;
			break;
		default:
			break;
	}
}
