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
#include "LevelEndObject.h"
#include "AIType1.h"

bool GameLoader::RunLoader( const std::wstring & worldsFileName , std::list<WorldObject *> & worldList , GameDude * dude )
{
	std::ifstream worldFile( worldsFileName.c_str() );
	if( !worldFile.is_open() )
	{
		return false;
	}
	std::string readline;
	WorldObject * currentLoadingWorld = NULL;
	LevelObject * levelToLoad = NULL;
	while( !worldFile.eof() )
	{
		getline( worldFile , readline );
		readline = readline.substr( 0 , readline.find( "#" ) );
		readline = UtilFunctions::TrimWhiteSpace( readline );
		if( readline == "" )
		{
			continue ;
		}
		if( !currentLoadingWorld && readline.compare( "[WORLD]" ) )
		{
			continue;
		}
		if( !readline.compare( "[WORLD]" ) )
		{
			currentLoadingWorld = new WorldObject( L"" , dude );
			worldList.push_back( currentLoadingWorld );
			continue;
		}
		UtilFunctions::StringTokens tokens = UtilFunctions::StringTokenizer( readline , "=" );
		if( tokens->size() != 2 )
		{
			UtilFunctions::DestroyStringTokens( tokens );
			continue;
		}

		if( !tokens->at(0)->compare( "NAME" ) )
		{
			currentLoadingWorld->SetWorldName( Converter::StringToWString( *( tokens->at(1) ) ) );
		}
		else
		{
			levelToLoad = new LevelObject( Converter::StringToWString( *( tokens->at(0) ) ) );
			currentLoadingWorld->AddLevel( levelToLoad );
			GameLoader::LoadLevel( Converter::StringToWString( *( tokens->at(1) ) ) , levelToLoad );
		}

		UtilFunctions::DestroyStringTokens( tokens );
	}
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
	GraphicLoaders::TextureIdentifier levelEndTextureId = -1;

	GraphicLoaders::LoadTga( "GamePackFiles\\Images\\GroundBlock.tga" , brickTextureId );
	GraphicLoaders::LoadTga( "GamePackFiles\\Images\\flag.tga" , levelEndTextureId );
	GraphicLoaders::LoadTga( "GamePackFiles\\Images\\AIType1.tga" , ai1TextureId );

	while( !levelFile.eof() )
	{
		getline( levelFile , readline );
		readline = readline.substr( 0 , readline.find( "#" ) );
		readline = UtilFunctions::TrimWhiteSpace( readline );
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
		catch( Converter::ConverterException & )
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
				AIType1 * newAi = new AIType1( GameLoader::GameGridToCoords( xLocation , yLocation ) , ai1TextureId );
				level->AddAIObject( newAi );
				break;
			}
			case GO_AI_TYPE2:
			{
				break;
			}
			case GO_LEVEL_END:
			{
				Square pos( GameLoader::GameGridToCoords( xLocation , yLocation ) );
				pos.top += 7 * SQUARE_SIZE;
				LevelEndObject * piece = new LevelEndObject( pos , levelEndTextureId );
				level->AddGamePiece( piece );
				level->SetLevelEndObject( piece );
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