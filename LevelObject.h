#ifndef _LEVEL_OBJECT_H_
#define _LEVEL_OBJECT_H_

#include <string>
#include <list>

#include "AIObject.h"
#include "GamePiece.h"
#include "BackGroundManager.h"
#include "GameDude.h"
#include "LevelEndObject.h"

class LevelObject
{
public:
	LevelObject( const std::wstring & levelName );
	virtual ~LevelObject();
	void Draw();
	bool Update( int ticks , GameDude * gameDude );
	double Move( double distance );
	void AddGamePiece( GamePiece * piece );
	void AddAIObject( AIObject * object );
	void Start();
	void SetLevelEndObject( LevelEndObject * object );
	void SetLevelFileName( const std::wstring & levelFileName );
	bool Load();
	bool Reload();
protected:
	std::list<GamePiece *> m_levelObjects;
	std::list<AIObject *> m_passiveAIList;
	std::wstring m_levelName;
	double m_xOffset;
	double m_maxXOffset;
	BackGroundManager * m_backGroundManager;
	double m_screenWidth;
private:
	std::list<AIObject *> m_activeAIList;
	std::list<GamePiece *>::iterator m_screenEndIter;
	std::list<GamePiece *>::iterator m_screenStartIter;
	LevelEndObject * m_levelEndObject;
	std::wstring m_levelFileName;
	int m_timer;
};

#endif /* _LEVL_OBJECT_H_ */