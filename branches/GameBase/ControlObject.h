#ifndef _CONTROL_OBJECT_H_
#define _CONTROL_OBJECT_H_

#include <string>

enum Controls {
	CO_RIGHT = 0,
	CO_LEFT = 1,
	CO_JUMP = 2,
	CO_CROUCH = 3,
	CO_MAX_CONTROL
};

class ControlObject {
public:
	ControlObject();
	virtual ~ControlObject();
	unsigned int GetControlKey( Controls control );
	void SetControlKey( Controls control , unsigned int key );
	void LoadControls( const std::wstring & fileName );
private:
	unsigned int m_controlKeys[CO_MAX_CONTROL];
};

#endif /* _CONTROL_OBJECT_H_ */