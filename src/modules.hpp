#pragma once

#include <chrono>
#include <iostream>
#include <vector>
#include <dlfcn.h>

#include <SDL2/SDL.h>

class Module
{
	private:
	std::chrono::steady_clock::time_point lastCall = std::chrono::steady_clock::now();
	protected:
	public:
	double interval = -1;
	double TimeToCall();
	virtual void Func() = 0;
	void Action();

	virtual ~Module();
};

typedef Module* Import();
typedef Module* Destroy();

class ExternalModule
{
	public:
	Module* module;
	Import* constructor;
	Destroy* destructor;
	void* externalClass;

	void Load( const char * );
	void Unload();
};

class ModuleManager
{
	private:
	std::vector< ExternalModule* > modules;
	public:
	void AddExternal( const char * );
	void AddLocal( Module* );
	size_t Size();
	double TimeToCall( size_t );
	void Remove( size_t );
	void Execute( size_t );

	/*
	~ModuleManager()
	{
		if( modules.size() > 0 )
		{
			for( size_t i=modules.size()-1;i>=0;i--)
			{
				std::cout<<"Hi "<<i<<" "<<modules.size()<<std::endl;
				modules[i]->Unload();
				modules.pop_back();
			}
			modules.clear();
		}
	}
	*/
};
