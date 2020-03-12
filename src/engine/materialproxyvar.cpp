//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2020
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "materialproxyvar.h"

// ------------------------------------------------------------------------------------ //
// Очистить переменную
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::Clear()
{
    if ( !isDefined ) return;

    switch ( type )
    {
    case MPVT_INT:                  delete static_cast< int* >( value );                        break;
    case MPVT_FLOAT:                delete static_cast< float* >( value );                      break;
    case MPVT_BOOL:                 delete static_cast< bool* >( value );                       break;
    case MPVT_VECTOR_2D:            delete static_cast< Vector2D_t* >( value );                 break;
    case MPVT_VECTOR_3D:            delete static_cast< Vector3D_t* >( value );                 break;
    case MPVT_VECTOR_4D:            delete static_cast< Vector4D_t* >( value );                 break;
    case MPVT_ARRAY_FLOAT:          delete static_cast< std::vector< float >* >( value );       break;
    case MPVT_ARRAY_INT:            delete static_cast< std::vector< int >* >( value );         break;
    case MPVT_ARRAY_VECTOR_2D:      delete static_cast< std::vector< Vector2D_t >* >( value );  break;
    case MPVT_ARRAY_VECTOR_3D:      delete static_cast< std::vector< Vector3D_t >* >( value );  break;
    case MPVT_ARRAY_VECTOR_4D:      delete static_cast< std::vector< Vector4D_t >* >( value );  break;
    }

    type = MPVT_NONE;
    isDefined = false;
}

//------------------------------------------------------------------------------------ //
// Задать имя переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetName( const char* Name )
{
    name = Name;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueInt( int Value )
{   
   if ( isDefined && type != MPVT_INT )     Clear();
   if ( !isDefined )                        value = new int;

    *static_cast< int* >( value ) = Value;
    type = MPVT_INT;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueFloat( float Value )
{
    if ( isDefined && type != MPVT_FLOAT )      Clear();
    if ( !isDefined )                           value = new float;

    *static_cast< float* >( value ) = Value;
    type = MPVT_FLOAT;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueBool( bool Value )
{
    if ( isDefined && type != MPVT_BOOL )       Clear();
    if ( !isDefined )                           value = new bool;

    *static_cast< bool* >( value ) = Value;
    type = MPVT_BOOL;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueVector2D( const Vector2D_t& Value )
{
    if ( isDefined && type != MPVT_VECTOR_2D )          Clear();
    if ( !isDefined )                                   value = new Vector2D_t();

    *static_cast< Vector2D_t* >( value ) = Value;
    type = MPVT_VECTOR_2D;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueVector3D( const Vector3D_t& Value )
{
    if ( isDefined && type != MPVT_VECTOR_3D )          Clear();
    if ( !isDefined )                                   value = new Vector3D_t();

    *static_cast< Vector3D_t* >( value ) = Value;
    type = MPVT_VECTOR_3D;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueVector4D( const Vector4D_t& Value )
{
    if ( isDefined && type != MPVT_VECTOR_4D )          Clear();
    if ( !isDefined )                                   value = new Vector4D_t();

    *static_cast< Vector4D_t* >( value ) = Value;
    type = MPVT_VECTOR_4D;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueShaderParameter( IShaderParameter* Value )
{
    if ( isDefined && type != MPVT_SHADER_PARAMETER )          Clear();

    value = Value;
    type = MPVT_SHADER_PARAMETER;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueArrayFloat( float* Array, UInt32_t Count )
{
    if ( isDefined && type != MPVT_ARRAY_FLOAT )            Clear();
    if ( !isDefined )                                       value = new std::vector< float >();

    auto            valueArray = static_cast< std::vector< float >* >( value );
    valueArray->resize( Count );
    memcpy( valueArray->data(), Array, Count * sizeof( float ) );

    type = MPVT_ARRAY_FLOAT;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueArrayInt( int* Array, UInt32_t Count )
{
    if ( isDefined && type != MPVT_ARRAY_INT )              Clear();
    if ( !isDefined )                                       value = new std::vector< int >();

    auto            valueArray = static_cast< std::vector< int >* >( value );
    valueArray->resize( Count );
    memcpy( valueArray->data(), Array, Count * sizeof( int ) );

    type = MPVT_ARRAY_INT;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueArrayVector2D( Vector2D_t* Array, UInt32_t Count )
{
    if ( isDefined && type != MPVT_ARRAY_VECTOR_2D )        Clear();
    if ( !isDefined )                                       value = new std::vector< Vector2D_t >();

    auto            valueArray = static_cast< std::vector< Vector2D_t >* >( value );
    valueArray->resize( Count );
    memcpy( valueArray->data(), Array, Count * sizeof( Vector2D_t ) );

    type = MPVT_ARRAY_VECTOR_2D;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueArrayVector3D( Vector3D_t* Array, UInt32_t Count )
{
    if ( isDefined && type != MPVT_ARRAY_VECTOR_3D )        Clear();
    if ( !isDefined )                                       value = new std::vector< Vector3D_t >();

    auto            valueArray = static_cast< std::vector< Vector3D_t >* >( value );
    valueArray->resize( Count );
    memcpy( valueArray->data(), Array, Count * sizeof( Vector3D_t ) );

    type = MPVT_ARRAY_VECTOR_3D;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Задать значение переменной
// ------------------------------------------------------------------------------------ //
void le::MaterialProxyVar::SetValueArrayVector4D( Vector4D_t* Array, UInt32_t Count )
{
    if ( isDefined && type != MPVT_ARRAY_VECTOR_4D )        Clear();
    if ( !isDefined )                                       value = new std::vector< Vector4D_t >();

    auto            valueArray = static_cast< std::vector< Vector4D_t >* >( value );
    valueArray->resize( Count );
    memcpy( valueArray->data(), Array, Count * sizeof( Vector4D_t ) );

    type = MPVT_ARRAY_VECTOR_4D;
    isDefined = true;
}

// ------------------------------------------------------------------------------------ //
// Определена ли переменна
// ------------------------------------------------------------------------------------ //
bool le::MaterialProxyVar::IsDefined() const
{
    return isDefined;
}

// ------------------------------------------------------------------------------------ //
// Получить имя переменной
// ------------------------------------------------------------------------------------ //
const char* le::MaterialProxyVar::GetName() const
{
    return name.c_str();
}

// ------------------------------------------------------------------------------------ //
// Получить тип переменной
// ------------------------------------------------------------------------------------ //
le::MATERIAL_PROXY_VAR_TYPE le::MaterialProxyVar::GetType() const
{
    return type;
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
int le::MaterialProxyVar::GetValueInt() const
{
    if ( type != MPVT_INT )     return 0;
    return *static_cast< int* >( value );
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
float le::MaterialProxyVar::GetValueFloat() const
{
    if ( type != MPVT_FLOAT )     return 0.f;
    return *static_cast< float* >( value );
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
bool le::MaterialProxyVar::GetValueBool() const
{
    if ( type != MPVT_BOOL )     return false;
    return *static_cast< bool* >( value );
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
const le::Vector2D_t& le::MaterialProxyVar::GetValueVector2D() const
{
    return *static_cast< Vector2D_t* >( value );
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
const le::Vector3D_t& le::MaterialProxyVar::GetValueVector3D() const
{
    return *static_cast< Vector3D_t* >( value );
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
const le::Vector4D_t& le::MaterialProxyVar::GetValueVector4D() const
{
    return *static_cast< Vector4D_t* >( value );
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
le::IShaderParameter* le::MaterialProxyVar::GetValueShaderParameter() const
{
    if ( type != MPVT_SHADER_PARAMETER )     return nullptr;
    return static_cast< IShaderParameter* >( value );
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
float* le::MaterialProxyVar::GetValueArrayFloat( UInt32_t& Count )
{
    if ( type != MPVT_ARRAY_FLOAT )
    {
        Count = 0;
        return nullptr;
    }

    auto        value = static_cast< std::vector< float >* >( this->value );
    Count = value->size();
    return value->data();
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
int* le::MaterialProxyVar::GetValueArrayInt( UInt32_t& Count )
{
    if ( type != MPVT_ARRAY_INT )     return nullptr;

    auto        value = static_cast< std::vector< int >* >( this->value );
    Count = value->size();
    return value->data();
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
le::Vector2D_t* le::MaterialProxyVar::GetValueArrayVector2D( UInt32_t& Count )
{
    if ( type != MPVT_ARRAY_VECTOR_2D )
    {
        Count = 0;
        return nullptr;
    }

    auto        value = static_cast< std::vector< Vector2D_t >* >( this->value );
    Count = value->size();
    return value->data();
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
le::Vector3D_t* le::MaterialProxyVar::GetValueArrayVector3D( UInt32_t& Count )
{
    if ( type != MPVT_ARRAY_VECTOR_3D )
    {
        Count = 0;
        return nullptr;
    }

    auto        value = static_cast< std::vector< Vector3D_t >* >( this->value );
    Count = value->size();
    return value->data();
}

// ------------------------------------------------------------------------------------ //
// Получить переменную
// ------------------------------------------------------------------------------------ //
le::Vector4D_t* le::MaterialProxyVar::GetValueArrayVector4D( UInt32_t& Count )
{
    if ( type != MPVT_ARRAY_VECTOR_4D )
    {
        Count = 0;
        return nullptr;
    }

    auto        value = static_cast< std::vector< Vector4D_t >* >( this->value );
    Count = value->size();
    return value->data();
}

// ------------------------------------------------------------------------------------ //
// Конструктор
// ------------------------------------------------------------------------------------ //
le::MaterialProxyVar::MaterialProxyVar() :
    isDefined( false ),
    value( nullptr ),
    type( MPVT_NONE )
{}

// ------------------------------------------------------------------------------------ //
// Деструктор
// ------------------------------------------------------------------------------------ //
le::MaterialProxyVar::~MaterialProxyVar()
{
    Clear();
}