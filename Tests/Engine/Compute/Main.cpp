// Copyright � 2014-2017  Zhirnov Andrey. All rights reserved.

#include "Engine/Compute/Engine.Compute.h"

using namespace Engine;
using namespace Engine::Base;
using namespace Engine::Compute;


class TestApplication : public GameUtils::GameApplication
{
// variables
public:
	GraphicsEngine	_graphicsEngine;
	ComputeEngine	_computeEngine;


// methods
public:
	TestApplication (const IParallelThreadPtr &thread) :
		GameApplication( thread ),
		_graphicsEngine( SubSystems() ), _computeEngine( SubSystems() )
	{
		CHECK( SubSystems()->Get< FileManager >()->FindAndSetCurrentDir( "Tests/Engine/Compute" ) );

		CHECK( Logger::GetInstance()->Open( "log", false ) );
	}


	// GameApplication //
	void _Update (TimeD dt, bool forceRedraw)
	{
	}

	void _OnInit ()
	{
		CHECK( SubSystems()->Get< Platform >()->
			InitWindow( Platform::WindowDesc( "Test", uint2(800, 600), MinValue<int2>(), false, true ) ) );
		
		CHECK( SubSystems()->Get< Platform >()->
			InitRender( VideoSettings() ) );
	}

	void _OnSurfaceCreated ()
	{
		CHECK( SubSystems()->Get< GraphicsEngine >()->Initialize() );
		CHECK( SubSystems()->Get< ComputeEngine >()->Initialize() );
		
		// setup shader manager
		{
			Ptr< ShaderManager >	sm = SubSystems()->Get< GraphicsEngine >()->GetShaderManager();

			sm->AddIncludeDirectory( "" );
			sm->AddImportDirectory( "" );
			sm->SetDebugOutputFolder( "_DebugOutput" );
		}

		ComputeFunctionPtr	kernel	= New<ComputeFunction>( SubSystems() );

		kernel->Load( "prog.glcs", EShaderCompilationFlags::DefaultCompute );

		kernel->Run( uint3(1) );

		/*ComputeProgramPtr	program = New<ComputeProgram>( SubSystems() );
		ComputeFunctionPtr	kernel	= New<ComputeFunction>( SubSystems() );
		ComputeImagePtr		image	= New<ComputeImage>( SubSystems() );
		const uint2			dim		= uint2( 1024 );

		CHECK( program->Create( "prog", EProgramUnitFlags::Default ) );

		CHECK( image->Create( uint4( dim ), ETexture::Tex2D, EPixelFormat::RGBA8_UNorm ) );

		kernel->Create( program, "Main" );

		kernel->SetArg( "outImage", image );

		kernel->Run( uint3( dim ) );*/
	}

	void _OnExit ()
	{
		SubSystems()->Get< GraphicsEngine >()->Deinitialize();
		SubSystems()->Get< ComputeEngine >()->Deinitialize();
	}

	void _OnResized ()
	{
	}
};


MAIN_APPLICATION_ENTRY( TestApplication );
