#include "Singleton.h"

Singleton::Singleton()
{
}

Singleton::~Singleton()
{
}

Singleton * Singleton::Instance()
{
	if( !m_instance )
	{
		m_instance = new Singleton();
	}
	return m_instance;
}

// Stub
Singleton::Singleton( const Singleton & temp )
{
}

// Stub
Singleton & Singleton::operator=( const Singleton & temp )
{
	return *((Singleton *)0);
}

Singleton * Singleton::m_instance = 0;