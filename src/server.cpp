#include <iostream>

#include <SDL2/SDL.h>

#include "server.hpp"
#include "modules.hpp"

void DaffodilServer::MainLoop()
{
	while( serverIsRunning_ )
	{
		for( unsigned int i=0;i<modules.Size();i++ )
			if( modules.TimeToCall(i) <= 0 )
				modules.Execute(i, db);

		if( modules.Size() > 0 )
		{
			double downtime = modules.TimeToCall(0);
			for( unsigned int i=1;i<modules.Size();i++ )
				downtime = std::min( downtime, modules.TimeToCall(i) );

			// convert from seconds to miliseconds
			SDL_Delay( downtime*1000 );
		}else
		{
			SDL_Delay( 200 );
		}
	}
}

void DaffodilServer::Start()
{
	StartServer();
	MainLoop();
}

void DaffodilServer::Quit()
{
	serverIsRunning_ = false;
	std::cout<<"Quitting...\n";
}