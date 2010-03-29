#include "ControlObject.h"
#include <string>
#include <windows.h>
#include <fstream>

ControlObject::ControlObject()
{
	m_controlKeys[ CO_RIGHT ] = VK_RIGHT;
	m_controlKeys[ CO_LEFT ] = VK_LEFT;
	m_controlKeys[ CO_JUMP ] = VK_UP;
	m_controlKeys[ CO_CROUCH ] = VK_DOWN;
}

ControlObject::~ControlObject()
{
}

unsigned int ControlObject::GetControlKey( Controls control )
{
	if( control < CO_MAX_CONTROL )
	{
		return m_controlKeys[ control ];
	}
	return 0;
}

void ControlObject::SetControlKey( Controls control , unsigned int key )
{
	m_controlKeys[control] = key;
}

void ControlObject::LoadControls( const std::wstring & fileName )
{
	std::ifstream controlFile( fileName.c_str() );
	if( !controlFile.is_open() )
	{
		return ;
	}
}