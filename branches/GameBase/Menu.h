#ifndef _MENU_H_
#define _MENU_H_

#include "GlFrameworkObject.h"
#include "MenuItem.h"
#include "GameStructs.h"
#include <list>
#include <string>

class Menu : public GlFrameworkObject{
public:
	Menu( unsigned int textBase );
	~Menu();
	void Update( int ticks );
	void Draw();
	void AddMenuItem( const std::wstring text , int id , const Square & pos );
	int GetSelectedItemId();
	void Click( const Point & point );
protected:
	std::list<MenuItem *> m_items;
	unsigned int m_textBase;
	int m_clickedId;
};

#endif /* _MENU_H_ */