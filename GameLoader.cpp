#include "GameLoader.h"

#include <list>
#include <string>
#include <fstream>

#include "LevelObject.h"
#include "WorldObject.h"
#include "GamePiece.h"
#include "UtilFunctions.h"
#include "Converter.h"
#include "GameStructs.h"
#include "GameEnums.h"
#include "GraphicLoaders.h"
#include "GameDude.h"

bool GameLoader::RunLoader( const std::wstring & worldsFileName , std::list<WorldObject *> & list , GameDude * dude )
{
	WorldObject * newWorld = new WorldObject( L"TestWorld" , dude );
	LevelObject * newLevel = new LevelObject( L"TestLevel" );
	LoadLevel( L"GamePackFiles\\level1.ini" , newLevel );
	newWorld->AddLevel( newLevel );
	list.push_back( newWorld );
	return true;
}

bool GameLoader::LoadLevel( const std::wstring & levelFileName , LevelObject * level )
{
	std::ifstream levelFile( levelFileName.c_str() );
	if( !levelFile.is_open() )
	{
		return false;
	}
	std::string readline;
	GraphicLoaders::TextureIdentifier brickTextureId = -1;
	GraphicLoaders::TextureIdentifier ai1TextureId = -1;
	GraphicLoaders::TextureIdentifier ai2TextureId = -1;

	GraphicLoaders::LoadTga( "GamePackFiles\\Images\\GroundBlock.tga" , brickTextureId );

	while( !levelFile.eof() )
	{
		getline( levelFile , readline );
		readline = readline.substr( 0 , readline.find( "#" ) );
		int end = readline.find_last_not_of( " " );
		int start = readline.find_first_not_of( " " );
		start = ( start == std::string::npos ? 0 : start );
		end = ( end == std::string::npos ? readline.length() : end ) - start + 1;
		readline = readline.substr( start , end );
		if( readline == "" )
		{
			continue ;
		}
		UtilFunctions::StringTokens objectTokens = UtilFunctions::StringTokenizer( readline , " \t" );

		if( objectTokens->size() < 3 )
		{
			UtilFunctions::DestroyStringTokens( objectTokens );
			return false;
		}

		int objectId = -1;
		double xLocation = -1;
		double yLocation = -1;

		try
		{
			objectId = Converter::StringToInt( *( objectTokens->at( 0 ) ) );
			xLocation = Converter::StringToDouble( *( objectTokens->at( 1 ) ) );
			yLocation = Converter::StringToDouble( *( objectTokens->at( 2 ) ) );
		}
		catch( Converter::ConverterException & ex )
		{
			UtilFunctions::DestroyStringTokens( objectTokens );
			return false;
		}

		UtilFunctions::DestroyStringTokens( objectTokens );

		switch( objectId )
		{
			case GO_BRICK_BLOCK:
			{
				GamePiece * piece = new GamePiece( GameLoader::GameGridToCoords( xLocation , yLocation ), brickTextureId );
				level->AddGamePiece( piece );
				break;
			}
			case GO_PIPE:
			{
				break;
			}
			case GO_AI_TYPE1:
			{
				break;
			}
			case GO_AI_TYPE2:
			{
				break;
			}
		};

	}
	return true;
}

Square GameLoader::GameGridToCoords( double x , double y )
{
	x *= SQUARE_SIZE;
	y *= SQUARE_SIZE;
	return Square( y + SQUARE_SIZE , y , x , x + SQUARE_SIZE );
}