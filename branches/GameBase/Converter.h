#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#include <exception>
#include <string>

namespace Converter
{
	class ConverterException : public std::exception
	{
	public:
		ConverterException( const char * msg ) { m_msg = msg; }
		const char * what() { return m_msg; }
	private:
		const char * m_msg;
	};

	std::string IntToString( const int & value );

	std::string UIntToString( const unsigned int & value );

	int StringToInt( const std::string & value );

	double StringToDouble( const std::string & value );

	unsigned int StringToUInt( const std::string & value );

	std::wstring StringToWString( const std::string & stringToConvert );

	std::string WStringToString( const std::wstring & stringToConvert );
};

#endif /* _CONVERTER_H_ */