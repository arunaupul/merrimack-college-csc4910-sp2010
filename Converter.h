/**
 * @file Converter.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * This is the converter utility functions
 * This namespace supplies funtions to perform
 * basic string conversions
 *
 */
#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#include <exception>
#include <string>

/**
 * @namespace Converter
 * @brief Conversion Functions
 *
 * This is the converter utility functions
 * This namespace supplies funtions to perform
 * basic string conversions
 */
namespace Converter
{
	/**
	 * @class ConverterException
	 * @brief Converter Exception
	 * 
	 * Class used to represent an error in the conversion process
	 */
	class ConverterException : public std::exception 	{
	public:
		ConverterException( const char * msg ) { m_msg = msg; }
		const char * what() { return m_msg; }
	private:
		const char * m_msg;
	};

	/**
	 * Function to convert an interger into a string
	 * @param value integer to convert
	 * @return interger as a string
	 */
	std::string IntToString( const int & value );

	/**
	 * Function to convert an unsigned interger into a string
	 * @param value unsigned integer to convert
	 * @return interger as a string
	 */
	std::string UIntToString( const unsigned int & value );

	/**
	 * Function to convert a string into a signed integer
	 * @param value string to convert
	 * @return signed interger
	 */
	int StringToInt( const std::string & value );

	/**
	 * Function to convert a string into a double
	 * @param value string to convert
	 * @return double
	 */
	double StringToDouble( const std::string & value );

	/**
	 * Function to convert a string into an unsigned integer
	 * @param value string to convert
	 * @return unsigned interger
	 */
	unsigned int StringToUInt( const std::string & value );

	/**
	 * Function to convert a string into a wstring
	 * @param stringToConvert string to convert
	 * @return convert string
	 */
	std::wstring StringToWString( const std::string & stringToConvert );

	/**
	 * Function to convert a wstring into a string
	 * @param stringToConvert string to convert
	 * @return convert string
	 */
	std::string WStringToString( const std::wstring & stringToConvert );
};

#endif /* _CONVERTER_H_ */