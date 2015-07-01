#ifndef _HREMOTE_H_
#define _HREMOTE_H_

#pragma once

#include "..\Include\HWin.h"

#include <string>
#include <vector>
#include <unordered_map>

#pragma warning( disable : 4227 )

namespace Dumper
{

	namespace Remote
	{

		class CProcess;
		class CModule;

		class SignatureType
		{
		public:
			enum
			{
				NORMAL = 0x0,		// normal
				READIT = 0x1,		// rpm at pattern
				SUBTRACT = 0x2,		// subtract img base
			};
		};

		typedef std::vector< unsigned char >							vecByte;
		typedef std::unordered_map< std::string, CModule* >				mapModule;

		class CMemory
		{
		public:

			CMemory( const uintptr_t& base, const size_t& size );
			~CMemory( void );


		public:

			template< typename _Ty >
			_Ty Get( const uintptr_t& off ) {
				if( off < _bytes.size( ) ) {
					return *( _Ty* ) &_bytes.at( off );
				}
				return _Ty( );
			}

			inline const uintptr_t& const Get( void ) { return _base; }


		protected:

			uintptr_t						_base;					// base
			vecByte							_bytes;					// bytes
		};

		class CModule
		{
		public:

			CModule( const std::string& name, const std::string& path, const uintptr_t& imgsize, const intptr_t& imgbase );
			~CModule( void );


		public:

			uintptr_t operator+ ( uintptr_t offset ) const				{ return _imgbase + offset; }
			uintptr_t operator- ( uintptr_t offset ) const				{ return _imgbase - offset; }


		public:

			inline const std::string& const GetName( void )				{ return _name; }
			inline const std::string& const GetPath( void )				{ return _path; }
			inline const uintptr_t& const	GetImgSize( void )			{ return _imgsize; }
			inline const uintptr_t& const	GetImgBase( void )			{ return _imgbase; }
			inline const vecByte& const		GetDumpedBytes( void )		{ return _bytes; }


		protected:

			std::string						_name;						// module name
			std::string						_path;						// module path

			uintptr_t						_imgsize = 0;				// image size
			uintptr_t						_imgbase = 0;				// image base

			vecByte							_bytes;						// dumped byte of the module
		};

		class CProcess
		{
		public:

			CProcess( void );
			~CProcess( void );


		public:

			bool							Attach( const std::string& procname, const std::string& winname = std::string( ), const std::string& winclname = std::string( ), DWORD accessrights = PROCESS_ALL_ACCESS, DWORD maxwtime = 0 );
			void							Detach( void );


		public:

			bool							ReadMemory( const uintptr_t& address, void* pBuffer, size_t size );
			bool							WriteMemory( uintptr_t& address, const void* pBuffer, size_t size );


		public:

			bool							CompareBytes( unsigned char* pBytes, const unsigned char* pPattern, const char* pMask );
			uintptr_t						FindPattern( CModule* pModule, const unsigned char* pPattern, const char* pMask, int type, uintptr_t pattern_offset, uintptr_t address_offset );


		private:

			bool							GetProcessID( void );
			bool							GetProcessHandle( void );
			bool							GetProcessModules( void );


		public:

			inline const mapModule& const	GetModules( void ) { return _modules; }
			inline CModule*					GetModuleByName( const std::string& name )
			{

				auto& res = _modules.find( name );
				if( res != _modules.end( ) )
					return res->second;
				return nullptr;
			}


		protected:

			std::string						_procname;					// process name
			std::string						_winname;					// window name
			std::string						_winclname;					// window class

			DWORD							_accessrights	= 0;		// openprocess rights
			bool							_haswindow		= false;	// has the process a window
			DWORD							_procid			= 0;		// process id
			HANDLE							_hproc			= 0;		// process handle

			mapModule						_modules;					// unordered_map holds modules
		};

		inline CProcess* Singleton( void )
		{

			static CProcess* __pProcess = new CProcess( );
			return __pProcess;
		}
	}
}

#ifndef pProcess
#define pProcess Dumper::Remote::Singleton( )
#endif /* pProcess */

#pragma warning( default : 4227 )

#endif /* _HREMOTE_H_ */