#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>
#include "GameStructs.h"
#include "Point.h"

class MenuItem {
public:
	MenuItem( const std::wstring & text , Square pos , int id , unsigned int textBase );
	virtual ~MenuItem();
	bool ContainPoint( const Point & point );
	int GetId();
	void Draw();
	void SetSelectStatus( bool status );
protected:
	Square m_position;
	std::wstring m_text;
	int m_menuId;
	unsigned int m_textBase;
	bool m_selected;
};


#endif /* _MENU_ITEM_H_ */