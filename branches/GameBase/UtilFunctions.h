/**
 * @file UtilFunctions.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 2.0
 *
 * This file contains general usage functions
 *
 */


#ifndef _UTIL_FUNCTIONS_H_
#define _UTIL_FUNCTIONS_H_

#include <string>
#include <vector>

/**
 * @namespace UtilFunctions
 * @brief Utility Functions
 * Contains several useful functions that fail to fit elsewhere
 */
namespace UtilFunctions
{
	/**
	 * @typedef StringTokensType
	 * The core data type of the object returned by the string tokenizers
	 */
	typedef std::vector< std::string * > StringTokensType;

	/**
	 * @typedef StringTokens
	 * The full data type of the object returned by the string tokenizers
	 */
	typedef StringTokensType * StringTokens;

	/** Method to trim white space off a string
	 * @param startString string to trim
	 * @returns a trimmed string
	 */
	std::string TrimWhiteSpace(const std::string & startString);

	/**
	 * Method to break up a given string into smaller piece at given points
	 * Method does not return empty tokens
	 * @param baseString String to tokenize
	 * @param delimiters String containing the charaters to break the baseString on
	 * @return StringTokens contains each piece of the broken string
	 */
	UtilFunctions::StringTokens StringTokenizer( const std::string & baseString , const std::string & delimiters );

	/**
	 * Method to break up a given string into smaller piece at given points
	 * Method does return empty tokens
	 * @param baseString String to tokenize
	 * @param delimiters String containing the charaters to break the baseString on
	 * @return StringTokens contains each piece of the broken string
	 */
	UtilFunctions::StringTokens StringTokenizer2( const std::string & baseString , const std::string & delimiters );

	/**
	 * Function to clean up the tokens returned by the tokenizers
	 * @param tokens Tokens to clean up
	 */
	void DestroyStringTokens( UtilFunctions::StringTokens tokens );
};

#endif /* _UTIL_FUNCTIONS_H_ */