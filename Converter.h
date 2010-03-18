#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#include <exception>
#include <string>

namespace Converter
{
	class ConverterException : public std::exception
	{
	public:
		ConverterException( const char * msg ) { _msg = msg; }
		const char * what() { return _msg; }
	private:
		const char * _msg;
	};

	std::string IntToString( const int & value );

	std::string UIntToString( const unsigned int & value );

	int StringToInt( const std::string & value );

	double StringToDouble( const std::string & value );

	unsigned int StringToUInt( const std::string & value );
};

#endif /* _CONVERTER_H_ */