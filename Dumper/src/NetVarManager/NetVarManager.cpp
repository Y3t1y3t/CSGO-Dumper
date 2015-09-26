#include "HNetVarManager.h"

#include "../Utilis/HUtilis.h"
#include <iomanip>
#include <sstream>

namespace Dumper
{
    namespace NetVarManager
    {
        RecvTable::RecvTable( const uintptr_t& base ) :
            CMemory( base, 0x10 )
        {
        }

        RecvTable::~RecvTable( void )
        {
        }

        RecvProp::RecvProp( const uintptr_t& base, int run ) :
            CMemory( base, 0x3C ),
            _run( run )
        {
        }

        RecvProp::~RecvProp( void )
        {
        }

        ClientClass::ClientClass( const uintptr_t& base ) :
            CMemory( base, 0x28 )
        {
        }

        ClientClass::~ClientClass( void )
        {
        }

        CNetVarManager::CNetVarManager( void )
        {
        }

        CNetVarManager::~CNetVarManager( void )
        {
        }

        bool CNetVarManager::Load( void )
        {
            auto firstclass = pProcess->FindPattern( pProcess->GetModuleByName( "client.dll" ), reinterpret_cast< unsigned char* >( "DT_TEWorldDecal" ), "xxxxxxxxxxxxxx", 0, 0, 0 );
            firstclass = pProcess->FindPattern( pProcess->GetModuleByName( "client.dll" ), reinterpret_cast< unsigned char* >( &firstclass ), "xxxx", Remote::SignatureType::READIT, 0x2B, 0 );

            if( !firstclass )
                return false;

            for( auto Class = ClientClass( firstclass ); Class.Get(); Class = ClientClass( Class.GetNextClass() ) ) {

                auto table = RecvTable( Class.GetTable() );
                if( !table.Get() )
                    continue;

                ScanTable( table, 0, table.GetName().c_str() );
            }
            return true;
        }

        void CNetVarManager::Dump( void ) const
        {
            std::stringstream ss;
            ss << "- - - - - - Tool by Y3t1y3t ( uc ) - - - - - - " << std::endl;
            ss << "| -> http://www.unknowncheats.me/forum/counterstrike-global-offensive/100856-cs-go-offset-dumper-small-one.html" << std::endl;
            ss << "| -> " << Utilis::GetTime();
            ss << "- -" << std::endl << std::endl;

            for( auto& table : _tables ) {
                ss << table.first << std::endl;
                for( auto& prop : table.second ) {
                    ss << std::setw( 53 )
                        << std::setfill( '_' )
                        << std::left
                        << ( std::string( prop.second->GetRun(), '  ' ) + "|__" + prop.first ).c_str()
                        << std::right
                        << std::hex
                        << " -> 0x"
                        << std::setw( 4 )
                        << std::setfill( '0' )
                        << std::uppercase
                        << prop.second->GetOffset() << std::endl;
                }
            }

            std::ofstream( "NetVarManager.txt" ) << ss.str();
        }

        void CNetVarManager::Release( void )
        {
            for( auto& table : _tables ) {
                for( auto& prop : table.second ) {
                    delete prop.second;
                }
                table.second.clear();
            }
            _tables.clear();
        }

        int CNetVarManager::GetNetVar( const std::string& tablename, const std::string& varname )
        {
            auto table = _tables.find( tablename );
            if( table != _tables.end() ) {
                for( auto& prop : table->second ) {
                    if( prop.first == varname ) {
                        return prop.second->GetOffset();
                    }
                }
            }
            return 0;
        }

        void CNetVarManager::ScanTable( RecvTable& table, int run, const char* name )
        {
            for( auto i = 0; i < table.GetMaxProp(); ++i ) {
                auto pProp = new RecvProp( table.GetPropById( i ), run );
                if( isdigit( pProp->GetName()[ 0 ] ) )
                    continue;

                _tables[ name ].push_back( std::pair<std::string, RecvProp*>( pProp->GetName().c_str(), pProp ) );

                auto child = pProp->GetTable();
                if( !child )
                    continue;

                auto recvTable = RecvTable( child );
                ScanTable( recvTable, ++run, name );
            }
        }
    }
}
