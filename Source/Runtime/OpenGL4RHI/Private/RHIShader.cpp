// Copyright BSOD-Games, All Rights Reserved.
// Authors: Egor Pogulyaka (zombiHello)

#include <GL/glew.h>

#include "Logging/LogMacros.h"
#include "RHIShader.h"

/**
 * Constructor
 */
le::RHIShader::RHIShader() :
    vertexShader( 0 ),
    geometryShader( 0 ),
    pixelShader( 0 ),
    gpuProgram( 0 )
{}

/**
 * Destructor
 */
le::RHIShader::~RHIShader()
{
    Destroy();
}

/**
 * Compile shader
 */
bool le::RHIShader::Compile( const std::string& InCode, EShaderType InShaderType, std::vector< std::string >* InDefines, std::string* OutError )
{
    if ( InCode.empty() )
    {
        if ( !OutError )    return false;
        
        *OutError = "Code is empty";
        return false;
    }

    std::string             code = InCode;

    if ( InDefines )
    {
        std::string         defineSection;
        for ( uint32 index = 0; index < InDefines->size(); ++index )
            defineSection += "#define " + InDefines->at( index ) + "\n";

        InsertDefinesToCode( code, defineSection );
    }

    switch ( InShaderType )
    {
    case ST_Vertex:
    {
        if ( vertexShader )     Destroy( ST_Vertex );

        const char*     cCode = code.c_str();
        vertexShader = glCreateShader( GL_VERTEX_SHADER );
        glShaderSource( vertexShader, 1, &cCode, nullptr );
        glCompileShader( vertexShader );

        // Check result compilation
        int             error = 0;
        glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &error );
        if ( error != GL_TRUE )
        {
            if ( !OutError )    return false;

            GetErrorCompilation( ST_Vertex, *OutError );
            return false;
        }
        break;
    }

    case ST_Geometry:
    {
        if ( geometryShader )      Destroy( ST_Geometry );

        const char* cCode = code.c_str();
        geometryShader = glCreateShader( GL_GEOMETRY_SHADER );
        glShaderSource( geometryShader, 1, &cCode, nullptr );
        glCompileShader( geometryShader );

        // Check result compilation
        int             error = 0;
        glGetShaderiv( geometryShader, GL_COMPILE_STATUS, &error );    
        if ( error != GL_TRUE )
        {
            if ( !OutError )    return false;

            GetErrorCompilation( ST_Geometry, *OutError );
            return false;
        }
        break;
    }

    case ST_Pixel:
    {
        if ( pixelShader )      Destroy( ST_Pixel );

        const char* cCode = code.c_str();
        pixelShader = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( pixelShader, 1, &cCode, nullptr );
        glCompileShader( pixelShader );

        // Check result compilation
        int             error = 0;
        glGetShaderiv( pixelShader, GL_COMPILE_STATUS, &error );
        if ( error != GL_TRUE )
        {
            if ( !OutError )    return false;

            GetErrorCompilation( ST_Pixel, *OutError );
            return false;
        }
        break;
    }
    }

    return true;
}

/**
 * Link shader
 */
bool le::RHIShader::Link( std::string* OutError )
{
    gpuProgram = glCreateProgram();

    if ( vertexShader )     glAttachShader( gpuProgram, vertexShader );
    if ( geometryShader )   glAttachShader( gpuProgram, geometryShader );
    if ( pixelShader )      glAttachShader( gpuProgram, pixelShader );

    // Link program and check on error
    glLinkProgram( gpuProgram );

    int         error = 0;
    glGetProgramiv( gpuProgram, GL_LINK_STATUS, &error );
    if ( error != GL_TRUE )
    { 
        if ( !OutError )        return false;

        int         length = 0;
        glGetProgramiv( gpuProgram, GL_INFO_LOG_LENGTH, &length );
        glGetProgramInfoLog( gpuProgram, length, &length, ( char* ) OutError->data() );
        return false;
    }

    if ( vertexShader )     Destroy( ST_Vertex );
    if ( geometryShader )   Destroy( ST_Geometry );
    if ( pixelShader )      Destroy( ST_Pixel );

    return true;
}

/**
 * Destroy shader
 */
void le::RHIShader::Destroy()
{
    if ( vertexShader )     Destroy( ST_Vertex );
    if ( geometryShader )   Destroy( ST_Geometry );
    if ( pixelShader )      Destroy( ST_Pixel );
    if ( gpuProgram )
    {
        glDeleteProgram( gpuProgram );
        gpuProgram = 0;
    }
}

/**
 * Is loaded shader
 */
bool le::RHIShader::IsLoaded() const
{
    return gpuProgram > 0;
}

/**
 * Insert defines to shader code
 */
void le::RHIShader::InsertDefinesToCode( std::string& InOutCode, const std::string& InDefinesSection )
{
    if ( InDefinesSection.empty() ) return;

    uint32		    defineInsertPoint = 0;
    uint32          versionIndex = InOutCode.find( "#version" );
    
    if ( versionIndex != std::string::npos )
        defineInsertPoint = InOutCode.find( "\n", versionIndex ) + 1;
    else
    {
        defineInsertPoint = 0;
        LIFEENGINE_LOG_WARNING( "OpenGL4RHI", "Missing #version xxx in shader" );
    }

    InOutCode.insert( defineInsertPoint, InDefinesSection );
}

/**
 * Destroy shader type
 */
void le::RHIShader::Destroy( EShaderType InShaderType )
{
    switch ( InShaderType )
    {
    case ST_Vertex:
        if ( !vertexShader ) return;

        glDeleteShader( vertexShader );
        vertexShader = 0;
        break;

    case ST_Geometry:
        if ( !geometryShader ) return;

        glDeleteShader( geometryShader );
        geometryShader = 0;
        break;

    case ST_Pixel:
        if ( !pixelShader ) return;

        glDeleteShader( pixelShader );
        pixelShader = 0;
        break;
    }
}

/**
 * Get error compilation
 */
void le::RHIShader::GetErrorCompilation( EShaderType InShaderType, std::string& OutError )
{
    uint32      shaderHandle = 0;
    switch ( InShaderType )
    {
    case ST_Vertex:
        if ( !vertexShader )            return;
        shaderHandle = vertexShader;
        break;

    case ST_Geometry:
        if ( !geometryShader )          return;
        shaderHandle = geometryShader;
        break;

    case ST_Pixel:
        if ( !pixelShader )             return;
        shaderHandle = pixelShader;
        break;
    }

    int			lengtMessage = 0;
    glGetShaderiv( shaderHandle, GL_INFO_LOG_LENGTH, &lengtMessage );

    OutError.resize( lengtMessage );
    glGetShaderInfoLog( shaderHandle, lengtMessage, &lengtMessage, ( char* ) OutError.data() );
}
