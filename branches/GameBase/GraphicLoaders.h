/**
 * @file GraphicLoaders.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Namespace to load different graphic formats into openGL textures
 *
 */
#ifndef _GRAPHIC_LOADERS_H_
#define _GRAPHIC_LOADERS_H_

#include <string>

/**
 * @namespace GraphicLoaders
 * @brief Loads Graphics
 *
 * Namespace to load different graphic formats into openGL textures
 * This namespace primarily wraps the SOIL libary
 */
namespace GraphicLoaders
{
	/**
	 * ID used to represent a openGL texture
	 */
	typedef unsigned int TextureIdentifier;

	/**
	 * Loads a Bitmap image into openGL
	 * @param fileName File to load
	 * @param textureId Storage location for the textureId
	 * @return True is successful
	 */
	bool LoadNewBitmap( const std::wstring & fileName , TextureIdentifier & textureId );

	/**
	 * Loads a Bitmap image into openGL
	 * @param fileName File to load
	 * @param textureId Storage location for the textureId
	 * @return True is successful
	 */
	bool LoadTga( const std::wstring & fileName , TextureIdentifier & textureId );

	/**
	 * @overload bool GraphicLoaders::LoadTga( const std::string & fileName , TextureIdentifier & textureId )
	 */
	bool LoadTga( const std::string & fileName , TextureIdentifier & textureId );
}

#endif /* _GRAPHIC_LOADERS_H_ */
