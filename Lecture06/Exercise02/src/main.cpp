#include <iostream>
#include <unistd.h>
#include "Sender.hpp"
#include "Receiver.hpp"
#include "AI.hpp"

int main(void)
{
	Receiver r;
	r.run();
	Sender s(static_cast<AI*>(&r), 1);
	s.run();

	for(;;)
	{
		sleep(1);
	}
}
