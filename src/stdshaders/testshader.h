//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef TESTSHADER_H
#define TESTSHADER_H

#include <vector>

#include "common/shaderparaminfo.h"
#include "stdshaders/ishader.h"

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	class IGPUProgram;

	//---------------------------------------------------------------------//

	class TestShader : public IShader
	{
	public:
		// IShader
		virtual bool					InitInstance( UInt32_t CountParams, IShaderParameter** ShaderParameters );
		virtual void					OnDrawMesh( UInt32_t CountParams, IShaderParameter** ShaderParameters, const Matrix4x4_t& Transformation, ICamera* Camera );

		virtual const char*				GetName() const;
		virtual const char*				GetFallbackShader() const;
		virtual UInt32_t				GetCountParams() const;
		virtual ShaderParamInfo*		GetParam( UInt32_t Index ) const;
		virtual ShaderParamInfo*		GetParams() const;

		// TestShader
		TestShader();

	private:
		IGPUProgram*							gpuProgram;
		std::vector< ShaderParamInfo >			shaderParams;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !SHADERDLL_H

