#include "ControlObject.h"
#include <string>
#include <windows.h>
#include <fstream>
#include "UtilFunctions.h"
#include "Converter.h"

ControlObject::ControlObject()
{
	m_controlKeys[ CO_RIGHT ] = VK_RIGHT;
	m_controlKeys[ CO_LEFT ] = VK_LEFT;
	m_controlKeys[ CO_JUMP ] = VK_UP;
	m_controlKeys[ CO_CROUCH ] = VK_DOWN;
	m_controlKeys[ CO_PAUSE ] = VK_ESCAPE;
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
	std::string readLine;
	UtilFunctions::StringTokens tokens = NULL;
	while( !controlFile.eof() )
	{
		getline( controlFile , readLine );
		tokens = UtilFunctions::StringTokenizer( readLine , "=" );
		if( tokens->size() == 2 )
		{
			if( !tokens->at(0)->compare( "LEFT" ) )
			{
				SetControlKey( CO_LEFT , StringToKey( tokens->at(1) ) );
			}
			else if( !tokens->at(0)->compare( "RIGHT" ) )
			{
				SetControlKey( CO_RIGHT , StringToKey( tokens->at(1) ) );
			}
			else if( !tokens->at(0)->compare( "JUMP" ) )
			{
				SetControlKey( CO_JUMP , StringToKey( tokens->at(1) ) );
			}
			else if( !tokens->at(0)->compare( "CROUCH" ) )
			{
				SetControlKey( CO_CROUCH , StringToKey( tokens->at(1) ) );
			}
			else if( !tokens->at(0)->compare( "PAUSE" ) )
			{
				SetControlKey( CO_PAUSE , StringToKey( tokens->at(1) ) );
			}
		}
		UtilFunctions::DestroyStringTokens( tokens );
	}
}

unsigned int ControlObject::StringToKey( const std::string * keyString )
{
	std::string trimmedString = UtilFunctions::TrimWhiteSpace( *keyString );
	if( trimmedString.length() == 1 )
	{
		return trimmedString[0];
	}
	else if( !trimmedString.compare( "LEFT" ) )
	{
		return VK_LEFT;
	}
	else if( !trimmedString.compare( "RIGHT" ) )
	{
		return VK_RIGHT;
	}
	else if( !trimmedString.compare( "UP" ) )
	{
		return VK_UP;
	}
	else if( !trimmedString.compare( "DOWN" ) )
	{
		return VK_DOWN;
	}
	else if( !trimmedString.compare( "ESC" ) )
	{
		return VK_ESCAPE;
	}
	else if( !trimmedString.compare( "SPACE" ) )
	{
		return VK_SPACE;
	}
	else
	{
		try
		{
			return Converter::StringToUInt( trimmedString );
		}
		catch( Converter::ConverterException & )
		{
			return -1;
		}
	}
}