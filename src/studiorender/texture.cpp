//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>

#include "engine/lifeengine.h"
#include "studiorender/studiorendersampler.h"
#include "global.h"
#include "texture.h"

struct OpenGLImageFormat
{
	le::UInt32_t		internalFormat;
	le::UInt32_t		format;
	le::UInt32_t		type;
};

// ------------------------------------------------------------------------------------ //
// Конвертировать формат тип формата изображения движка в формат OpenGL'a
// ------------------------------------------------------------------------------------ //
inline OpenGLImageFormat TextureImageFormat_EnumToOpenGLFormat( le::IMAGE_FORMAT ImageFormat )
{
	switch ( ImageFormat )
	{
	case le::IF_RGBA_8UNORM:		return { GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE };
	case le::IF_RGB_8UNORM:			return { GL_RGB, GL_RGB, GL_UNSIGNED_BYTE };
	case le::IF_RGBA_16FLOAT:		return { GL_RGBA16F, GL_RGBA, GL_FLOAT };
	case le::IF_RGB_16FLOAT:		return { GL_RGB16F, GL_RGB, GL_FLOAT };
	case le::IF_DEPTH24_STENCIL8:	return { GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8 };
	}
}

// ------------------------------------------------------------------------------------ //
// Конвертировать тип фильтра текстуры движка в формат OpenGL'a
// ------------------------------------------------------------------------------------ //
inline le::UInt32_t TextureSampler_EnumToOpenGLSampler( le::SAMPLER_FILTER Filter )
{
	switch ( Filter )
	{
	case le::SF_LINEAR:						return GL_LINEAR;
	case le::SF_NEAREST:					return GL_NEAREST;
	case le::SF_NEAREST_MIPMAP_NEAREST:		return GL_NEAREST_MIPMAP_NEAREST;
	case le::SF_NEAREST_MIPMAP_LINEAR:		return GL_NEAREST_MIPMAP_LINEAR;
	case le::SF_LINEAR_MIPMAP_NEAREST:		return GL_LINEAR_MIPMAP_NEAREST;
	case le::SF_LINEAR_MIPMAP_LINEAR:		return GL_LINEAR_MIPMAP_LINEAR;
	default:								return 0;
	}
}

// ------------------------------------------------------------------------------------ //
// Конвертировать режим адрессации в текстуре в формат OpenGL'a
// ------------------------------------------------------------------------------------ //
inline le::UInt32_t ConvertEngineSamplerAddressMode_To_OpenGLTextureAddressMode( le::SAMPLER_ADDRESS_MODE AddressMode )
{
	switch ( AddressMode )
	{
	case le::SAM_BORDER:					return GL_CLAMP_TO_BORDER;
	case le::SAM_CLAMP:						return GL_CLAMP_TO_EDGE;
	case le::SAM_MIRROR:					return GL_MIRRORED_REPEAT;
	case le::SAM_REPEAT:					return GL_REPEAT;
	default:								return 0;
	}
}

// ------------------------------------------------------------------------------------ //
// Создать текстуру
// ------------------------------------------------------------------------------------ //
void le::Texture::Initialize( TEXTURE_TYPE TextureType, IMAGE_FORMAT ImageFormat, UInt32_t Width, UInt32_t Height, UInt32_t CountMipmap )
{
	if ( handle ) Delete();

	glGenTextures( 1, &handle );

	type = TextureType;	
	imageFormat = ImageFormat;
	width = Width;
	height = Height;
	countMipmaps = CountMipmap;
	isCreated = true;
}

// ------------------------------------------------------------------------------------ //
// Удалить текстуру
// ------------------------------------------------------------------------------------ //
void le::Texture::Delete()
{
	LIFEENGINE_ASSERT( handle );

	glDeleteTextures( 1, &handle );

	width = 0;
	height = 0;
	handle = 0;
	countMipmaps = 0;
	isCreated = false;
}

// ------------------------------------------------------------------------------------ //
// Активировать текстуру
// ------------------------------------------------------------------------------------ //
void le::Texture::Bind( UInt32_t Layer )
{
	LIFEENGINE_ASSERT( handle );
	
	glActiveTexture( GL_TEXTURE0 + Layer );
	glBindTexture( GL_TEXTURE_2D, handle );	
	layer = Layer;
}

// ------------------------------------------------------------------------------------ //
// Деактивировать текстуру
// ------------------------------------------------------------------------------------ //
void le::Texture::Unbind()
{
	LIFEENGINE_ASSERT( handle );

	glActiveTexture( GL_TEXTURE0 + layer );
	glBindTexture( GL_TEXTURE_2D, 0 );
	layer = 0;
}

// ------------------------------------------------------------------------------------ //
// Сгенерировать лоды для текстур
// ------------------------------------------------------------------------------------ //
void le::Texture::GenerateMipmaps()
{
	LIFEENGINE_ASSERT( handle && layer );

	glGenerateMipmap( GL_TEXTURE_2D );
	countMipmaps = floor( log2( glm::max( width, height ) ) );
}

// ------------------------------------------------------------------------------------ //
// Загрузить данные текстуры
// ------------------------------------------------------------------------------------ //
void le::Texture::Append( const UInt8_t* Data, UInt32_t MipmapLevel )
{
	LIFEENGINE_ASSERT( MipmapLevel >= 0 && MipmapLevel < countMipmaps && handle && layer );

	OpenGLImageFormat		openglImageFormat = TextureImageFormat_EnumToOpenGLFormat( imageFormat );
	UInt32_t				width = GetWidth( MipmapLevel );
	UInt32_t				height = GetHeight( MipmapLevel );
	
	glTexImage2D( GL_TEXTURE_2D, MipmapLevel, openglImageFormat.internalFormat, width, height, 0, openglImageFormat.format, openglImageFormat.type, Data );
}

// ------------------------------------------------------------------------------------ //
// Обновить данные текстуры
// ------------------------------------------------------------------------------------ //
void le::Texture::Update( UInt32_t X, UInt32_t Y, UInt32_t Width, UInt32_t Height, const UInt8_t* Data, UInt32_t MipmapLevel )
{
	LIFEENGINE_ASSERT( MipmapLevel >= 0 && MipmapLevel < countMipmaps && Width <= GetWidth( MipmapLevel ) && Height <= GetHeight( MipmapLevel ) && handle && layer );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );	
	glTexSubImage2D( GL_TEXTURE_2D, MipmapLevel, X, Y, Width, Height, TextureImageFormat_EnumToOpenGLFormat( imageFormat ).format, GL_UNSIGNED_BYTE, Data );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
}

// ------------------------------------------------------------------------------------ //
// Задать семплер текстуры
// ------------------------------------------------------------------------------------ //
void le::Texture::SetSampler( const StudioRenderSampler& Sampler )
{
	LIFEENGINE_ASSERT( handle && layer );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertEngineSamplerAddressMode_To_OpenGLTextureAddressMode( Sampler.addressU ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertEngineSamplerAddressMode_To_OpenGLTextureAddressMode( Sampler.addressV ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, ConvertEngineSamplerAddressMode_To_OpenGLTextureAddressMode( Sampler.addressW ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureSampler_EnumToOpenGLSampler( Sampler.minFilter ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureSampler_EnumToOpenGLSampler( Sampler.magFilter ) );
	glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, Sampler.borderColor );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, Sampler.minLod );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, Sampler.maxLod );
}

// ------------------------------------------------------------------------------------ //
// Создана ли текстура
// ------------------------------------------------------------------------------------ //
bool le::Texture::IsCreated() const
{
	return isCreated;
}

// ------------------------------------------------------------------------------------ //
// Получить ширину текстуры
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::Texture::GetWidth( UInt32_t MipmapLevel ) const
{
	LIFEENGINE_ASSERT( MipmapLevel >= 0 && MipmapLevel < countMipmaps );

	UInt32_t			width = this->width >> MipmapLevel;
	return width >= 1 ? width : 1;
}

// ------------------------------------------------------------------------------------ //
// Получить высоту текстуры
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::Texture::GetHeight( UInt32_t MipmapLevel ) const
{
	LIFEENGINE_ASSERT( MipmapLevel >= 0 && MipmapLevel < countMipmaps );

	UInt32_t			height = this->height >> MipmapLevel;
	return height >= 1 ? height : 1;
}

// ------------------------------------------------------------------------------------ //
// Получить количество лодов текстуры
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::Texture::GetCountMipmaps() const
{
	return countMipmaps;
}

// ------------------------------------------------------------------------------------ //
// Получить тип текстуры
// ------------------------------------------------------------------------------------ //
le::TEXTURE_TYPE le::Texture::GetType() const
{
	return type;
}

// ------------------------------------------------------------------------------------ //
// Конструктор
// ------------------------------------------------------------------------------------ //
le::Texture::Texture() :
	isCreated( false ),
	handle( 0 ),
	width( 0 ),
	height( 0 ),
	countMipmaps( 0 ),
	layer( 0 )
{}

// ------------------------------------------------------------------------------------ //
// Деструктор
// ------------------------------------------------------------------------------------ //
le::Texture::~Texture()
{
	Delete();
}
