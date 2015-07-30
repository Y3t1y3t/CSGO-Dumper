#ifndef _HNETVARMANAGER_H_
#define _HNETVARMANAGER_H_

#include "..\Include\HWin.h"

#include "..\Remote\HRemote.h"
#include "..\Utilis\HUtilis.h"

#include <map>
#include <unordered_map>

#include <sstream>
#include <fstream>

#pragma warning( disable : 4227 )
#pragma warning( disable : 4172 )

namespace Dumper
{
    namespace NetVarManager
    {
        class RecvTable : public Remote::CMemory
        {
        public:

            explicit                                RecvTable( const uintptr_t& base );
                                                    ~RecvTable( void );


        public:

            inline std::string&                     GetName( std::string& name = std::string( ) )
            {
                name.resize( 32 );
                pProcess->ReadMemory( Get<DWORD>( 0xC ), &name.at( 0 ), 32 );
                return name;
            }

            inline uintptr_t                        GetPropById( int id ) { return Get<uintptr_t>( 0x0 ) + id * 0x3C; }
            inline int                              GetMaxProp( void ) { return Get<int>( 0x4 ); }
        };

        class RecvProp : public Remote::CMemory
        {
        public:

                                                    RecvProp( const uintptr_t& base, int run );
                                                    ~RecvProp( void );


        public:

            inline std::string&                     GetName( std::string& name = std::string( ) )
            {
                name.resize( 64 );
                pProcess->ReadMemory( Get<DWORD>( 0x0 ), &name.at( 0 ), 64 );
                return name;
            }

            inline int                              GetOffset( void ) { return Get<int>( 0x2C ); }
            inline uintptr_t                        GetTable( void ) { return Get<uintptr_t>( 0x28 ); }
            inline const int& const                 GetRun( void ) { return _run; }


        protected:

            int                                     _run;                       // deepness
        };

        class ClientClass : public Remote::CMemory
        {
        public:

            explicit                                ClientClass( const uintptr_t& base );
            ~ClientClass( void );


        public:

            inline std::string&                     GetName( std::string& name = std::string( ) )
            {
                name.resize( 64 );
                pProcess->ReadMemory( Get<DWORD>( 0x8 ), &name.at( 0 ), 64 );
                return name;
            }

            inline uintptr_t                        GetTable( void ) { return Get<uintptr_t>( 0xC ); }
            inline uintptr_t                        GetNextClass( void ) { return Get<uintptr_t>( 0x10 ); }
            inline int                              GetId( void ) { return Get<int>( 0x14 ); }
        };

        typedef std::pair < std::string, RecvProp* >         stringProp;
        typedef std::vector< stringProp >                    vecProp;
        typedef std::unordered_map< std::string, vecProp >   mapTable;

        class CNetVarManager
        {
        public:

                                                    CNetVarManager( void );
                                                    ~CNetVarManager( void );


        public:

            bool                                    Load( void );
            void                                    Dump( void );
            void                                    Release( void );


        public:

            int                                     GetNetVar( const std::string& tablename, const std::string& varname );


        private:

            void                                    ScanTable( RecvTable& table, int run, const char* name );


        protected:

            mapTable                                _tables;                    // recvtables dumped
        };

        inline CNetVarManager* Singleton( void )
        {
            static auto __pNetVarManager = new CNetVarManager( );
            return __pNetVarManager;
        }
    }
}

#ifndef pNetVarManager
#define pNetVarManager Dumper::NetVarManager::Singleton( )
#endif

#pragma warning( default : 4172 )
#pragma warning( default : 4227 )

#endif /* _HNETVARMANAGER_H_ */
