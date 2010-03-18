#include "Converter.h"

#include <sstream>
#include <string>

std::string Converter::IntToString( const int & value )
{
	std::stringstream convertStream;
	convertStream << value;
	return convertStream.str();	
}

std::string Converter::UIntToString( const unsigned int & value )
{
	std::stringstream convertStream;
	convertStream << value;
	return convertStream.str();	
}

int Converter::StringToInt( const std::string & value )
{
	std::istringstream convertStream(value);
	int returnValue;
	if( convertStream >> returnValue )
	{
		return returnValue;
	}
	else
	{
		throw ConverterException("Unable to convert");
	}
}

unsigned int Converter::StringToUInt( const std::string & value )
{
	std::istringstream convertStream(value);
	unsigned int returnValue;
	if( convertStream >> returnValue )
	{
		return returnValue;
	}
	else
	{
		throw ConverterException("Unable to convert");
	}
}

double Converter::StringToDouble( const std::string & value )
{
	std::istringstream convertStream(value);
	double returnValue;
	if( convertStream >> returnValue )
	{
		return returnValue;
	}
	else
	{
		throw ConverterException("Unable to convert");
	}
}
