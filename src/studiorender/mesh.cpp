//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#include "common/meshsurface.h"
#include "common/meshdescriptor.h"
#include "engine/lifeengine.h"
#include "studiorender/studiovertexelement.h"

#include "mesh.h"

// ------------------------------------------------------------------------------------ //
// Создать меш
// ------------------------------------------------------------------------------------ //
void le::Mesh::Create( const MeshDescriptor& MeshDescriptor )
{
	if ( ( MeshDescriptor.sizeVerteces > 0 && !MeshDescriptor.verteces ) || 
		( MeshDescriptor.countIndeces > 0 && !MeshDescriptor.indeces ) )
		return;

	if ( isCreated )		Delete();

	// Запоминаем материалы
	for ( UInt32_t index = 0; index < MeshDescriptor.countMaterials; ++index )
		materials.push_back( MeshDescriptor.materials[ index ] );

	// Запоминаем карты освещений
	for ( UInt32_t index = 0; index < MeshDescriptor.countLightmaps; ++index )
		lightmaps.push_back( MeshDescriptor.lightmaps[ index ] );

	// Запоминаем поверхности
	for ( UInt32_t index = 0; index < MeshDescriptor.countSurfaces; ++index )
		surfaces.push_back( MeshDescriptor.surfaces[ index ] );

	// Загружаем информацию о меше в GPU
	vertexArrayObject.Create();
	vertexBufferObject.Create();
	indexBufferObject.Create();

	vertexBufferObject.Bind();
	vertexBufferObject.Allocate( MeshDescriptor.verteces, MeshDescriptor.sizeVerteces );

	indexBufferObject.Bind();
	indexBufferObject.Allocate( MeshDescriptor.indeces, MeshDescriptor.countIndeces * sizeof( UInt32_t ) );

	VertexBufferLayout				vertexBufferLayout;
	for ( UInt32_t index = 0; index < MeshDescriptor.countVertexElements; ++index )
		switch ( MeshDescriptor.vertexElements[ index ].type )
		{
		case VET_FLOAT:
			vertexBufferLayout.PushFloat( MeshDescriptor.vertexElements[ index ].count );
			break;

		case VET_UNSIGNED_INT:
			vertexBufferLayout.PushUInt( MeshDescriptor.vertexElements[ index ].count );
			break;

		case VET_UNSIGNED_BYTE:
			vertexBufferLayout.PushUByte( MeshDescriptor.vertexElements[ index ].count );
			break;
		}
	
	vertexArrayObject.Bind();
	vertexArrayObject.AddBuffer( vertexBufferObject, vertexBufferLayout );
	vertexArrayObject.AddBuffer( indexBufferObject );

	vertexArrayObject.Unbind();
	vertexBufferObject.Unbind();
	indexBufferObject.Unbind();

	min = MeshDescriptor.min;
	max = MeshDescriptor.max;
	primitiveType = MeshDescriptor.primitiveType;
	isCreated = true;
}

// ------------------------------------------------------------------------------------ //
// Удалить меш
// ------------------------------------------------------------------------------------ //
void le::Mesh::Delete()
{
	vertexArrayObject.Delete();
	vertexBufferObject.Delete();
	indexBufferObject.Delete();

	// TODO: Реализовать удаление материалов и карт освещений

	surfaces.clear();
	materials.clear();
	lightmaps.clear();
	isCreated = false;
}

// ------------------------------------------------------------------------------------ //
// Создан ли меш
// ------------------------------------------------------------------------------------ //
bool le::Mesh::IsCreated() const
{
	return isCreated;
}

// ------------------------------------------------------------------------------------ //
// Получить количество поверхностей
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::Mesh::GetCountSurfaces() const
{
	return surfaces.size();
}

// ------------------------------------------------------------------------------------ //
// Получить поверхность
// ------------------------------------------------------------------------------------ //
const le::MeshSurface& le::Mesh::GetSurface( UInt32_t Index ) const
{
	if ( Index >= surfaces.size() ) return le::MeshSurface();
	return surfaces[ Index ];
}

// ------------------------------------------------------------------------------------ //
// Получить массив поверхностей
// ------------------------------------------------------------------------------------ //
le::MeshSurface* le::Mesh::GetSurfaces() const
{
	return ( MeshSurface* ) surfaces.data();
}

// ------------------------------------------------------------------------------------ //
// Получить количество материалов
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::Mesh::GetCountMaterials() const
{
	return materials.size();
}

// ------------------------------------------------------------------------------------ //
// Получить материал
// ------------------------------------------------------------------------------------ //
le::IMaterial* le::Mesh::GetMaterial( UInt32_t Index ) const
{
	if ( Index >= materials.size() ) return nullptr;
	return materials[ Index ];
}

// ------------------------------------------------------------------------------------ //
// Получить массив материалов
// ------------------------------------------------------------------------------------ //
le::IMaterial** le::Mesh::GetMaterials() const
{
	return ( IMaterial** ) materials.data();
}

// ------------------------------------------------------------------------------------ //
// Получить количество карт освещения
// ------------------------------------------------------------------------------------ //
le::UInt32_t le::Mesh::GetCountLightmaps() const
{
	return lightmaps.size();
}

// ------------------------------------------------------------------------------------ //
// Получить карту освещения
// ------------------------------------------------------------------------------------ //
le::ITexture* le::Mesh::GetLightmap( UInt32_t Index ) const
{
	if ( Index >= lightmaps.size() ) return nullptr;
	return lightmaps[ Index ];
}

// ------------------------------------------------------------------------------------ //
// Получить массив карт освещений
// ------------------------------------------------------------------------------------ //
le::ITexture** le::Mesh::GetLightmaps() const
{
	return ( ITexture** ) lightmaps.data();
}

// ------------------------------------------------------------------------------------ //
// Получить минимальную точку в меше
// ------------------------------------------------------------------------------------ //
const le::Vector3D_t& le::Mesh::GetMin() const
{
	return min;
}

// ------------------------------------------------------------------------------------ //
// Получить максимульную точку в меше
// ------------------------------------------------------------------------------------ //
const le::Vector3D_t& le::Mesh::GetMax() const
{
	return max;
}

// ------------------------------------------------------------------------------------ //
// Конструктор
// ------------------------------------------------------------------------------------ //
le::Mesh::Mesh() :
	isCreated( false ),
	primitiveType( PT_TRIANGLES )
{}

// ------------------------------------------------------------------------------------ //
// Деструктор
// ------------------------------------------------------------------------------------ //
le::Mesh::~Mesh()
{
	Delete();
}
