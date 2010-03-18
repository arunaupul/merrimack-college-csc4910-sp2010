/** Common functions
 *
 * @file UtilFunctions.h
 * @author  Ryan Fleming <rfleming71@kb71.com>
 * @since 0.2
 */


#ifndef _UTIL_FUNCTIONS_H_
#define _UTIL_FUNCTIONS_H_

#include <string>
#include <vector>

namespace UtilFunctions
{
	typedef std::vector< std::string * > StringTokensType;
	typedef StringTokensType * StringTokens;

	/** Method to trim white space off a string
	 * @param startString string to trim
	 * @returns a trimmed string
	 */
	std::string TrimWhiteSpace(const std::string & startString);

	UtilFunctions::StringTokens StringTokenizer( const std::string & baseString , const std::string & delimiters );

	UtilFunctions::StringTokens StringTokenizer2( const std::string & baseString , const std::string & delimiters );

	void DestroyStringTokens( UtilFunctions::StringTokens tokens );
};

#endif /* _UTIL_FUNCTIONS_H_ */