//////////////////////////////////////////////////////////////////////////
//
//			        *** lifeEngine ***
//				Copyright (C) 2018-2020
//
// Repository engine:   https://github.com/zombihello/lifeEngine
// Authors:				Egor Pogulyaka (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef SPRITE_GENERIC_H
#define SPRITE_GENERIC_H

#include "baseshader.h"

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	class SpriteGeneric : public BaseShader
	{
	public:

		//---------------------------------------------------------------------//

		enum SHADER_FLAG
		{
			SF_NONE = 0,
			SF_NORMAL_MAP = 1 << 0,
			SF_SPECULAR_MAP = 1 << 1
		};

		//---------------------------------------------------------------------//

		// IShader
		virtual bool				Initialize( UInt32_t CountParams, IShaderParameter** ShaderParameters );
		virtual void				OnDrawMesh( const Matrix4x4_t& Transformation, ICamera* Camera, ITexture* Lightmap = nullptr );

		virtual const char*			GetName() const;
		virtual const char*			GetFallbackShader() const;

		// SpriteGeneric
		SpriteGeneric();
		~SpriteGeneric();

		void						ClearParameters();

	private:
		ITexture*			baseTexture;
		ITexture*			normalMap;
		ITexture*			specularMap;
		Vector4D_t			textureRect;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !SPRITE_GENERIC_H

