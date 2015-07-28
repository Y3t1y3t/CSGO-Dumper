#include "HRemote.h"

namespace Dumper
{
    namespace Remote
    {
        CMemory::CMemory( const uintptr_t& base, const size_t& size ) :
            _base( base )
        {
            _bytes = vecByte( size );
            if( !_base || !pProcess->ReadMemory( _base, static_cast< void* >( &_bytes.at( 0 ) ), size ) ) {
                _bytes = vecByte( 0 );
            }
        }

        CMemory::~CMemory( void )
        {
            if( !_bytes.empty( ) ) {
                _bytes.clear( );
            }
        }

        CModule::CModule( const std::string& name, const std::string& path, const uintptr_t& imgsize, const intptr_t& imgbase ) :
            _name( name ),
            _path( path ),
            _imgsize( imgsize ),
            _imgbase( imgbase )
        {
            _bytes = vecByte( imgsize );
            pProcess->ReadMemory( _imgbase, &_bytes[ 0 ], _imgsize );
        }

        CModule::~CModule( void )
        {
            if( !_bytes.empty( ) ) {
                _bytes.clear( );
            }
        }

        CProcess::CProcess( void )
        {
        }

        CProcess::~CProcess( void )
        {
        }

        bool CProcess::Attach( const std::string& procname, const std::string& winname /* = std::string( ) */, const std::string& winclname /* = std::string( ) */, DWORD accessrights /* = PROCESS_ALL_ACCESS */, DWORD maxwtime /* = 0 */ )
        {
            Detach( );

            _procname = procname;
            _winname = winname;
            _winclname = winclname;

            _accessrights = accessrights;
            _haswindow = bool( !_winname.empty( ) || !_winclname.empty( ) );

            auto curtime = GetTickCount( );
            do {
                if( !GetProcessID( ) )
                    continue;

                if( !GetProcessHandle( ) )
                    continue;

                if( GetProcessModules( ) )
                    return true;
            } while( ( maxwtime != 0 ? ( GetTickCount( ) - curtime ) <= maxwtime : true ) );

            return false;
        }

        void CProcess::Detach( void )
        {
            if( !_modules.empty( ) ) {
                for( auto& m : _modules ) {
                    delete m.second;
                }
                _modules.clear( );
            }

            _procname.clear( );
            _winname.clear( );
            _winclname.clear( );

            _procid = 0;
            _hproc = nullptr;
        }

        bool CProcess::ReadMemory( const uintptr_t& address, void* pBuffer, size_t size )
        {
            return bool( ReadProcessMemory( _hproc, LPCVOID( address ), pBuffer, size, nullptr ) == TRUE );
        }

        bool CProcess::WriteMemory( uintptr_t& address, const void* pBuffer, size_t size )
        {
            return bool( WriteProcessMemory( _hproc, LPVOID( address ), pBuffer, size, nullptr ) == TRUE );
        }

        bool CProcess::CompareBytes( unsigned char* pBytes, const unsigned char* pPattern, const char* pMask )
        {
            for( auto i = 0; *pMask; ++pMask, ++pPattern, ++i ) {
                if( *pMask != '?' && pBytes[ i ] != *pPattern ) {
                    return false;
                }
            }
            return true;
        }

        uintptr_t CProcess::FindPattern( CModule* pModule, const unsigned char* pPattern, const char* pMask, int type, uintptr_t pattern_offset, uintptr_t address_offset )
        {
            if( !pModule ) {
                return 0;
            }

            auto pDump = const_cast< unsigned char* >( &pModule->GetDumpedBytes( ).at( 0 ) );
            auto off = pModule->GetImgSize( ) - strlen( pMask );

            for( uintptr_t i = 0; i < off; ++i ) {

                if( CompareBytes( pDump + i, pPattern, pMask ) ) {

                    i += pModule->GetImgBase( ) + pattern_offset;

                    if( type & SignatureType::READIT ) {
                        ReadMemory( i, &i, sizeof( uintptr_t ) );
                    }

                    if( type & SignatureType::SUBTRACT ) {
                        i -= pModule->GetImgBase( );
                    }

                    return i + address_offset;
                }
            }
            return 0;
        }

        bool CProcess::GetProcessID( void )
        {
            if( _haswindow ) {
                auto hWin = FindWindowA( _winclname.empty( ) ? NULL : _winclname.c_str( ), _winname.empty( ) ? NULL : _winname.c_str( ) );
                if( hWin ) {
                    GetWindowThreadProcessId( hWin, &_procid );
                }
            }
            else {
                auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
                if( !hSnapshot ) {
                    return false;
                }

                PROCESSENTRY32 pe32 = { sizeof( PROCESSENTRY32 ) };
                if( Process32First( hSnapshot, &pe32 ) == TRUE ) {
                    do {
                        if( pe32.szExeFile == _procname )
                            _procid = pe32.th32ProcessID;
                    } while( Process32Next( hSnapshot, &pe32 ) == TRUE && _procid == 0 );
                }

                CloseHandle( hSnapshot );
            }
            return bool( _procid != 0 );
        }

        bool CProcess::GetProcessHandle( void )
        {
            if( _procid == 0 ) {
                return false;
            }
            return bool( ( _hproc = OpenProcess( _accessrights, FALSE, _procid ) ) != nullptr );
        }

        bool CProcess::GetProcessModules( void )
        {
            if( _hproc == nullptr ) {
                return false;
            }

            auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, _procid );
            if( !hSnapshot ) {
                return false;
            }

            MODULEENTRY32 me32 = { sizeof( MODULEENTRY32 ) };
            if( Module32First( hSnapshot, &me32 ) == TRUE ) {
                do {
                    char path[ MAX_PATH ] = { 0 };
                    GetModuleFileNameExA( _hproc, me32.hModule, path, MAX_PATH );

                    _modules[ me32.szModule ] = new CModule( me32.szModule, path, uintptr_t( me32.modBaseSize ), uintptr_t( me32.hModule ) );
                } while( Module32Next( hSnapshot, &me32 ) == TRUE );
            }

            CloseHandle( hSnapshot );

            if( _modules.find( "client.dll" ) == _modules.end( ) ) { // sanity - check :C
                if( !_modules.empty( ) ) {
                    for( auto& m : _modules ) {
                        delete m.second;
                    }
                    _modules.clear( );
                }
            }
            return bool( !_modules.empty( ) );
        }
    }
}
