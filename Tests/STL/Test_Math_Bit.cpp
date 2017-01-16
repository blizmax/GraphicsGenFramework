// Copyright � 2017  Zhirnov Andrey. All rights reserved.

#include "STL/ux_stl.h"

using namespace GX_STL;
using namespace GX_STL::GXTypes;
using namespace GX_STL::GXMath;


extern void Test_Math_Bit ()
{
	uint	a0 = ToMask<uint>( 0 );		ASSERT( a0 == 0 );
	uint	a1 = ToMask<uint>( 1 );		ASSERT( a1 == 0x00000001 );		ASSERT( ((1 << ( 1-1)) & a1) != 0 );
	uint	a2 = ToMask<uint>( 16 );	ASSERT( a2 == 0x0000FFFF );		ASSERT( ((1 << (16-1)) & a2) != 0 );
	uint	a3 = ToMask<uint>( 31 );	ASSERT( a3 == 0x7FFFFFFF );		ASSERT( ((1 << (31-1)) & a3) != 0 );
	uint	a4 = ToMask<uint>( 32 );	ASSERT( a4 == 0xFFFFFFFF );		ASSERT( ((1 << (32-1)) & a4) != 0 );

	ASSERT(( a0 == CompileTime::ToMask<uint, 0> ));
	ASSERT(( a1 == CompileTime::ToMask<uint, 1> ));
	ASSERT(( a2 == CompileTime::ToMask<uint, 16> ));
	ASSERT(( a3 == CompileTime::ToMask<uint, 31> ));
	ASSERT(( a4 == CompileTime::ToMask<uint, 32> ));
	
	uint	b0 = ToMask<uint>( 0, 1 );		ASSERT( b0 == 0x00000001 );	ASSERT( ((1 <<  0) & b0) != 0 );
	uint	b1 = ToMask<uint>( 1, 3 );		ASSERT( b1 == 0x00000006 );	ASSERT( ((1 <<  1) & b1) != 0 );	ASSERT( ((1 <<  2) & b1) != 0 );
	uint	b2 = ToMask<uint>( 16, 18 );	ASSERT( b2 == 0x00030000 );	ASSERT( ((1 << 16) & b2) != 0 );	ASSERT( ((1 << 17) & b2) != 0 );
	uint	b3 = ToMask<uint>( 30, 31 );	ASSERT( b3 == 0x40000000 );	ASSERT( ((1 << 30) & b3) != 0 );	ASSERT( ((1 << 30) & b3) != 0 );
	uint	b4 = ToMask<uint>( 32, 34 );	ASSERT( b4 == 0 );
	
	ASSERT(( b0 == CompileTime::ToMask2<uint, 0, 1> ));
	ASSERT(( b1 == CompileTime::ToMask2<uint, 1, 3> ));
	ASSERT(( b2 == CompileTime::ToMask2<uint, 16, 18> ));
	ASSERT(( b3 == CompileTime::ToMask2<uint, 30, 31> ));
	ASSERT(( b4 == CompileTime::ToMask2<uint, 32, 34> ));

	uint	c0 = SafeLeftBitShift( 1u,  1 );			ASSERT( c0 == 0x00000002 );
	uint	c1 = SafeLeftBitShift( 1u, 16 );			ASSERT( c1 == 0x00010000 );
	uint	c2 = SafeLeftBitShift( 1u, 31 );			ASSERT( c2 == 0x80000000 );

	uint	c3 = SafeRightBitShift( 1u << 12,  11 );	ASSERT( c3 == 0x00000002 );
	uint	c4 = SafeRightBitShift( 1u << 12,  12 );	ASSERT( c4 == 0x00000001 );
	uint	c5 = SafeRightBitShift( 1u << 12,  13 );	ASSERT( c5 == 0 );

	uint	d0 = BitRotateLeft( 1u, 1 );			ASSERT( d0 == 0x00000002 );
	uint	d1 = BitRotateLeft( 1u << 31, 1 );		ASSERT( d1 == 0x00000001 );

	uint	d2 = BitRotateRight( 1u, 1 );			ASSERT( d2 == 0x80000000 );
	uint	d3 = BitRotateRight( 1u << 31, 1 );		ASSERT( d3 == 0x40000000 );

	uint	e0 = BitScanReverse( 0x101u );			ASSERT( e0 == 8 );
	uint	e1 = BitScanReverse( 0x202u );			ASSERT( e1 == 9 );
	uint	e2 = BitScanReverse( 0x80001000u );		ASSERT( e2 == 31 );
	uint	e3 = BitScanReverse( 0x80001002u );		ASSERT( e3 == 31 );
	uint	e4 = BitScanReverse( 0x0u );			ASSERT( e4 == -1 );

	uint	f0 = BitScanForward( 0x101u );			ASSERT( f0 == 0 );
	uint	f1 = BitScanForward( 0x202u );			ASSERT( f1 == 1 );
	uint	f2 = BitScanForward( 0x80001000u );		ASSERT( f2 == 12 );
	uint	f3 = BitScanForward( 0x80001002u );		ASSERT( f3 == 1 );
	uint	f4 = BitScanForward( 0x0u );			ASSERT( f4 == -1 );
	uint	f5 = BitScanForward( ushort(0x04) );	ASSERT( f5 == 2 );


	Bitfield<10>	g;
	g.SetAll( true );	uint	g0 = g;				ASSERT( g0 == ToMask<uint>( 10 ) );
	g.SetAll( false );	uint	g1 = g;				ASSERT( g1 == 0 );
	g.Set( 2 );			uint	g2 = g.MinIndex();	ASSERT( g2 == 2 );
	g.Set( 1 );			uint	g3 = g.MinIndex();	ASSERT( g3 == 1 );
	g.Set( 3 );			uint	g4 = g.MaxIndex();	ASSERT( g4 == 3 );
	g.Set( 4 );			uint	g5 = g.MaxIndex();	ASSERT( g5 == 4 );

	g.SetAll( false );	g.SetInterval( 0, 1 );		ASSERT( g.Get(0) and g.Get(1) and not g.Get(2) );
	g.SetAll( false );	g.SetInterval( 3, 5 );		ASSERT( g.HasInterval( 3, 5 ) and not g.HasInterval( 2, 6 ) );
	
	Bitfield<10>	h0, h1;
	h0.Set( 0 ).Set( 1 ).Set( 2 );
	h1.SetInterval( 0, 2 );
	ASSERT( h0 == h1 );
}