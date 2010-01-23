#ifndef _GRAPHIC_LOADERS_H_
#define _GRAPHIC_LOADERS_H_

#include <string>

namespace GraphicLoaders
{
	typedef unsigned int TextureIdentifier;
	bool LoadNewBitmap( const std::wstring & fileName , TextureIdentifier & textureId );
}

#endif /* _GRAPHIC_LOADERS_H_ */
