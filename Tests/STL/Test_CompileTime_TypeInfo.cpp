// Copyright � 2014-2016  Zhirnov Andrey. All rights reserved.

#include "STL/ux_stl.h"

using namespace GX_STL;
using namespace GX_STL::GXTypes;
using namespace GX_STL::CompileTime;


extern void Test_CompileTime_TypeInfo ()
{
	// IsSameTypes //
	STATIC_ASSERT( (IsSameTypes< int, int >) );
	STATIC_ASSERT( (IsSameTypes< int *, int * >) );
	STATIC_ASSERT( (not IsSameTypes< const int, int >) );
	STATIC_ASSERT( (not IsSameTypes< int *, const int * >) );
	STATIC_ASSERT( (IsSameTypes< int const *, const int * >) );
	
	STATIC_ASSERT( (IsSameTypesWithoutQualifiers< int, int >) );
	STATIC_ASSERT( (IsSameTypesWithoutQualifiers< const int, int >) );
	//STATIC_ASSERT( (IsSameTypesWithoutQualifiers< int *, const int * >::value) );
	//STATIC_ASSERT( (IsSameTypesWithoutQualifiers< int *, int const * const >::value) );


	// NearInt //
	STATIC_ASSERT( (IsSameTypes< NearUInt::FromBits<7>,  ubyte >) );
	STATIC_ASSERT( (IsSameTypes< NearUInt::FromBits<15>, ushort >) );
	STATIC_ASSERT( (IsSameTypes< NearUInt::FromBits<17>, uint >) );
	STATIC_ASSERT( (IsSameTypes< NearUInt::FromBits<32>, uint >) );
	STATIC_ASSERT( (IsSameTypes< NearUInt::FromBits<64>, ulong >) );
	STATIC_ASSERT( (IsSameTypes< NearUInt::FromBits<80>, ulong >) );


	// constexpr
	STATIC_ASSERT( MinValue<uint>() == 0 );


	MustBeFloat<float>();
	MustBeInteger<int>();
	MustBeUnsignedInteger<uint>();
	
	//MustBeFloat<int>();
	//MustBeInteger<float>();
	//MustBeUnsignedInteger<int>();
}