/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Namespace to load different graphic formats into openGL textures
 *
 */
#ifndef _GRAPHIC_LOADERS_H_
#define _GRAPHIC_LOADERS_H_

#include <string>

namespace GraphicLoaders
{
	typedef unsigned int TextureIdentifier;
	bool LoadNewBitmap( const std::wstring & fileName , TextureIdentifier & textureId );
	bool LoadTga( const std::wstring & fileName , TextureIdentifier & textureId );
	bool LoadTga( const std::string & fileName , TextureIdentifier & textureId );
}

#endif /* _GRAPHIC_LOADERS_H_ */
