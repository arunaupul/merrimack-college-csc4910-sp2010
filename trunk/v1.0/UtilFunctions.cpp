/** Common functions
 *
 * @file UtilFunctions.h
 * @author  Ryan Fleming <rfleming71@kb71.com>
 * @since 0.2
 */

#include "UtilFunctions.h"

#include <string>
#include <vector>

/** Method to trim white space off a string
 * @param startString string to trim
 * @returns a trimmed string
 */
std::string UtilFunctions::TrimWhiteSpace(const std::string & startString)
{
	std::string::size_type startingPos = startString.find_first_not_of("\t ");
	std::string::size_type endingPos = startString.find_last_not_of("\t ");
	if( startingPos == std::string::npos )
	{
		startingPos = 0;
	}
	if( endingPos == std::string::npos )
	{
		endingPos = 0;
	}
	return startString.substr( startingPos , endingPos - startingPos + 1 );
}

UtilFunctions::StringTokens UtilFunctions::StringTokenizer( const std::string & baseString , const std::string & delimiters )
{
	StringTokens tokens = new StringTokensType();
	
	std::string::size_type lastPos = baseString.find_first_not_of( delimiters , 0 );
    std::string::size_type pos = baseString.find_first_of( delimiters , lastPos );

    while ( std::string::npos != pos || std::string::npos != lastPos )
    {
		tokens->push_back( new std::string( baseString.substr( lastPos , pos - lastPos ) ) );
        lastPos = baseString.find_first_not_of( delimiters , pos );
        pos = baseString.find_first_of( delimiters , lastPos );
    }

	return tokens;
}

UtilFunctions::StringTokens UtilFunctions::StringTokenizer2( const std::string & baseString , const std::string & delimiters )
{
	StringTokens tokens = new StringTokensType();
	
	std::string::size_type starting = 0;
    std::string::size_type ending = baseString.find_first_of( delimiters , starting );
	std::string holding = "";

	while ( ending < baseString.length() )
    {
		holding = baseString.substr( starting , ending - starting );
		while( baseString.at(starting) == '\"' && baseString.at(ending - 1) != '\"' )
		{
			ending = baseString.find_first_of( delimiters , ending + 1 );
			holding = baseString.substr( starting , ending - starting );
		}

		if( baseString.at(starting) == '\"' )
		{
			holding =  baseString.substr( starting + 1 , ending - starting - 2 );
		}

		tokens->push_back( new std::string( holding ) );
		starting = ending + 1;
		ending = baseString.find_first_of( delimiters , starting );
    }

	return tokens;
}

void UtilFunctions::DestroyStringTokens( UtilFunctions::StringTokens tokens )
{
	while( tokens->size() > 0 )
	{
		delete tokens->back();
		tokens->pop_back();
	}
	delete tokens;
}
