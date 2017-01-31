// Copyright � 2014-2017  Zhirnov Andrey. All rights reserved.

#pragma once

#include "Projects/ShaderEditor/Core/ISample.h"
#include "Projects/ShaderEditor/Tiles/Tile.h"

namespace ShaderEditor
{
	
	//
	// Simple Landscape Sample
	//

	class SimpleLandscapeSample : public ISample
	{
	// types
	private:

		class TileInitializer : public ITileInitializer
		{
		// variables
		private:
			IGeneratorPtr			_landscapeGen;
			IShaderPtr				_shader;
			MeshGenerator::Mesh		_planeMesh;

			
		// methods
		public:
			TileInitializer (const SubSystemsRef ss) : ITileInitializer(ss) {}

			void Init ();
			void Reload ();

			void InitTile (const TilePtr &tile) override;
		};


	// variables
	private:
		TileInitializer		_tileInitializer;
		RenderState			_renderState;

		IShaderPtr			_shader;


	// methods
	private:
		SimpleLandscapeSample (const SubSystemsRef ss);

		static uint	_GetTileMeshVertices ()		{ return 257; }

	public:
		void Init () override;
		void Release () override;
		void Reload () override;

		void Draw (const RenderTargetPtr &rt, TimeD globalTime) override;
		void Update (TimeD dt) override;
		
		bool Next () override;

		static ISamplePtr  New (const SubSystemsRef ss);
	};


}	// ShaderEditor