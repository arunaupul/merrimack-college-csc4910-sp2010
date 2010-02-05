#include "GlApplication.h"
#include <windows.h>
#include <gl\gl.h>
#include "GraphicLoaders.h"

class TestApp : public GlApplication
{
public:
	TestApp();
	~TestApp();
	void Draw();
	bool InitApp();
private:
	GraphicLoaders::TextureIdentifier m_textureId;

};
