//////////////////////////////////////////////////////////////////////////
//
//			*** lifeEngine (Двигатель жизни) ***
//				Copyright (C) 2018-2019
//
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// Авторы:				Егор Погуляка (zombiHello)
//
//////////////////////////////////////////////////////////////////////////

#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <unordered_map>

#include "engine/ilevel.h"
#include "engine/camera.h"
#include "studiorender/istudiorender.h"
#include "studiorender/imesh.h"
#include "bsp.h"
#include "bitset.h"

//---------------------------------------------------------------------//

namespace le
{
	//---------------------------------------------------------------------//

	class Model;
	class Sprite;

	//---------------------------------------------------------------------//

    class Level : public ILevel
	{
	public:
        // IReferenceObject
        virtual void                    IncrementReference();
        virtual void                    DecrementReference();
        virtual void                    Release();
        virtual UInt32_t                GetCountReferences() const;

		// ILevel
		virtual bool					Load( const char* Path, IFactory* GameFactory );
        virtual void					Update();
        virtual void                    Render();
		virtual void					Clear();
		virtual void					AddCamera( ICamera* Camera );
		virtual void					AddEntity( IEntity* Entity );
		virtual void					RemoveCamera( ICamera* Camera );
		virtual void					RemoveCamera( UInt32_t Index );
		virtual void					RemoveEntity( IEntity* Entity );
		virtual void					RemoveEntity( UInt32_t Index );

		virtual bool					IsLoaded() const;
		virtual const char*				GetNameFormat() const;
		virtual UInt32_t				GetCountCameras() const;
		virtual ICamera*				GetCamera( UInt32_t Index ) const;
		virtual UInt32_t				GetCountEntityes() const;
		virtual IEntity*				GetEntity( UInt32_t Index ) const;

		// Level
		Level();
		~Level();

		int						FindLeaf( const Vector3D_t& Position ) const;
		inline int				FindLeaf( Camera* Camera ) const
		{
			return FindLeaf( Camera->GetPosition() );
		}

		bool					IsClusterVisible( int CurrentCluster, int TestCluster ) const;

	private:

		//---------------------------------------------------------------------//

		struct Entity
		{
			Entity();

			Model*												model;
			IBody*												body;

			std::string											className;
			std::unordered_map< std::string, std::string >		values;
		};

		//---------------------------------------------------------------------//

		void					EntitiesParse( std::vector< Entity >& ArrayEntities, BSPEntities& BSPEntities, UInt32_t Size );

		bool								isLoaded;
		BSPVisData							visData;
		Bitset								facesDraw;
		IMesh*								mesh;
        UInt32_t                            countReferences;

		std::vector< BSPNode >				arrayBspNodes;
		std::vector< BSPLeaf >				arrayBspLeafs;
		std::vector< BSPPlane >				arrayBspPlanes;	
		std::vector< int >					arrayBspLeafsFaces;

		std::vector< ITexture* >			arrayLightmaps;
		std::vector< Camera* >				arrayCameras;
		std::vector< Model* >				arrayModels;
		std::vector< IEntity* >				arrayEntities;
		std::vector< IBody* >				arrayBodes;
	};

	//---------------------------------------------------------------------//
}

//---------------------------------------------------------------------//

#endif // !LEVEL_H
