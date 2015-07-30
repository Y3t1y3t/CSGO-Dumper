#include "HOffsetManager.h"
#include <sstream>

namespace Dumper
{
    namespace OffsetManager
    {
        COffsetManager::COffsetManager( void )
        {
        }

        COffsetManager::~COffsetManager( void )
        {
        }

        void COffsetManager::Dump( void )
        {
            std::stringstream ss;
            ss << "- - - - - - Tool by Y3t1y3t ( uc ) - - - - - - " << std::endl;
            ss << "| -> http://www.unknowncheats.me/forum/counterstrike-global-offensive/100856-cs-go-offset-dumper-small-one.html" << std::endl;
            ss << "| -> " << Utilis::GetTime( );
            ss << "- -" << std::endl << std::endl;

            auto pClient = pProcess->GetModuleByName( "client.dll" );
            if( !pClient ) {
                return;
            }

            auto pEngine = pProcess->GetModuleByName( "engine.dll" );
            if( !pEngine ) {
                return;
            }

            Dump( "DT_WeaponCSBase", "m_fAccuracyPenalty", 0x0, ss );
            Dump( "DT_BaseAnimating", "m_nForceBone", 0x0, ss );
            Dump( "DT_BaseCombatWeapon", "m_iState", 0x0, ss );
            Dump( "DT_BaseCombatWeapon", "m_iClip1", 0x0, ss );
            Dump( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack", 0x0, ss );
            Log( "DT_BaseCombatWeapon", "m_bCanReload", pNetVarManager->GetNetVar( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" ) + 0x5D, ss );
            Dump( "DT_BaseCombatWeapon", "m_iPrimaryAmmoType", 0x0, ss );
            Log( "DT_BaseCombatWeapon", "m_iWeaponID", pNetVarManager->GetNetVar( "DT_WeaponCSBase", "m_fAccuracyPenalty" ) + 0x20, ss );
            Dump( "DT_BaseEntity", "m_bSpotted", 0x0, ss );
            Dump( "DT_BaseEntity", "m_bSpottedByMask", 0x0, ss );
            Dump( "DT_BaseEntity", "m_hOwnerEntity", 0x0, ss );
            Dump( "DT_BaseEntity", "m_vecOrigin", 0x0, ss );
            Dump( "DT_BaseEntity", "m_iTeamNum", 0x0, ss );
            Dump( "DT_CSPlayer", "m_flFlashMaxAlpha", 0x0, ss );
            Dump( "DT_CSPlayer", "m_flFlashDuration", 0x0, ss );
            Log( "DT_CSPlayer", "m_iGlowIndex", pNetVarManager->GetNetVar( "DT_CSPlayer", "m_flFlashDuration" ) + 0x18, ss );
            Dump( "DT_CSPlayer", "m_angEyeAngles", 0x0, ss );
            Dump( "DT_CSPlayer", "m_iAccount", 0x0, ss );
            Dump( "DT_CSPlayer", "m_ArmorValue", 0x0, ss );
            Dump( "DT_CSPlayer", "m_bGunGameImmunity", 0x0, ss );
            Dump( "DT_CSPlayer", "m_iShotsFired", 0x0, ss );
            Dump( "DT_BasePlayer", "m_lifeState", 0x0, ss );
            Dump( "DT_BasePlayer", "m_fFlags", 0x0, ss );
            Dump( "DT_BasePlayer", "m_iHealth", 0x0, ss );
            Dump( "DT_BasePlayer", "m_hLastWeapon", 0x0, ss );
            Dump( "DT_BasePlayer", "m_hMyWeapons", 0x0, ss );
            Dump( "DT_BasePlayer", "m_hActiveWeapon", 0x0, ss );
            Dump( "DT_BasePlayer", "m_Local", 0x0, ss );
            Dump( "DT_BasePlayer", "m_vecViewOffset[0]", 0x0, ss );
            Dump( "DT_BasePlayer", "m_nTickBase", 0x0, ss );
            Dump( "DT_BasePlayer", "m_vecVelocity[0]", 0x0, ss );
            Dump( "DT_BasePlayer", "m_szLastPlaceName", 0x0, ss );
            Log( "DT_Local", "m_vecPunch", pNetVarManager->GetNetVar( "DT_BasePlayer", "m_Local" ) + 0x70, ss );
            Log( "DT_Local", "m_iCrossHairID", pNetVarManager->GetNetVar( "DT_CSPlayer", "m_bHasDefuser" ) + 0x50, ss );
            Log( "BaseEntity", "m_dwModel", 0x6C, ss );
            Log( "BaseEntity", "m_dwIndex", 0x64, ss );
            Log( "BaseEntity", "m_dwBoneMatrix", pNetVarManager->GetNetVar( "DT_BaseAnimating", "m_nForceBone" ) + 0x1C, ss );
            Log( "BaseEntity", "m_bMoveType", 0x258, ss );
            Log( "BaseEntity", "m_bDormant", 0xE9, ss );

            Dump( "ClientState", "m_dwClientState", pEngine, reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05\x00\x00\x00\x00" ), "x????xxxx????xxxxx????", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );
            Dump( "ClientState", "m_dwLocalPlayerIndex", pEngine, reinterpret_cast< unsigned char* >( "\x8B\x80\x00\x00\x00\x00\x40\xC3" ), "xx????xx", Remote::SignatureType::READIT, 0x2, 0x0, ss );
            Dump( "ClientState", "m_dwInGame", pEngine, reinterpret_cast< unsigned char* >( "\x83\xB9\x00\x00\x00\x00\x06\x0F\x94\xC0\xC3" ), "xx?xxxxxxxx", Remote::SignatureType::READIT, 0x2, 0x0, ss );
            Dump( "ClientState", "m_dwMaxPlayer", pEngine, reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\x8B\x80\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\x55\x8B\xEC\x8B\x45\x08" ), "x????xx????xxxxxxxxxxx", Remote::SignatureType::READIT, 0x7, 0x0, ss );
            Dump( "ClientState", "m_dwMapDirectory", pEngine, reinterpret_cast< unsigned char* >( "\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x80\x3D" ), "x????x???????xx", Remote::SignatureType::READIT, 0x1, 0x0, ss );
            Dump( "ClientState", "m_dwMapname", pEngine, reinterpret_cast< unsigned char* >( "\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00" ), "x????xxxxxxxxx????", Remote::SignatureType::READIT, 0x1, 0x0, ss );
            Dump( "ClientState", "m_dwPlayerInfo", pEngine, reinterpret_cast< unsigned char* >( "\x8B\x88\x00\x00\x00\x00\x8B\x01\x8B\x40\x00\xFF\xD0\x8B\xF8" ), "xx????xxxx?xxxx", Remote::SignatureType::READIT, 0x2, 0x0, ss );
            Dump( "ClientState", "m_dwViewAngles", pEngine, reinterpret_cast< unsigned char* >( "\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05\x00\x00\x00\x00" ), "xxxx????xxxxx????", Remote::SignatureType::READIT, 0x4, 0x0, ss );

            Dump( "EngineRender", "m_dwViewMatrix", pClient, reinterpret_cast< unsigned char* >( "\x81\xC6\x00\x00\x00\x00\x88\x45\x92\x0F\xB6\xC0" ), "xx????xxxxxx", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x33C, 0xB0, ss );
            Dump( "EngineRender", "m_dwEnginePosition", pEngine, reinterpret_cast< unsigned char* >( "\xF3\x0F\x11\x15\x00\x00\x00\x00\xF3\x0F\x11\x0D\x00\x00\x00\x00\xF3\x0F\x11\x05\x00\x00\x00\x00\xF3\x0F\x11\x3D\x00\x00\x00\x00" ), "xxxx????xxxx????xxxx????xxxx????", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x4, 0x0, ss );

            Dump( "RadarBase", "m_dwRadarBase", pClient, reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\x8B\x0C\xB0\x8B\x01\xFF\x50\x00\x46\x3B\x35\x00\x00\x00\x00\x7C\xEA\x8B\x0D\x00\x00\x00\x00" ), "x????xxxxxxx?xxx????xxxx????", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );
            Dump( "RadarBase", "m_dwRadarBasePointer", 0x50, ss );

            Dump( "LocalPlayer", "m_dwLocalPlayer", pClient, reinterpret_cast< unsigned char* >( "\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3\x6A\x00" ), "x????xx????????x????xxxx", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x10, ss );

            Dump( "EntityList", "m_dwEntityList", pClient, reinterpret_cast< unsigned char* >( "\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8" ), "x????xxxxx????xx", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );

            Dump( "WeaponTable", "m_dwWeaponTable", pClient, reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\x0F\xB7\xC9\x03\xC9\x8B\x44\x00\x0C\xC3" ), "x????xxxxxxx?xx", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );
            Dump( "WeaponTable", "m_dwWeaponTableIndex", pClient, reinterpret_cast< unsigned char* >( "\x66\x8B\x8E\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x05\x00\x00\x00\x00\x50" ), "xxx??xxx????x????x", Remote::SignatureType::READIT, 0x3, 0x0, ss );

            Dump( "Extra", "m_dwInput", pClient, reinterpret_cast< unsigned char* >( "\xB9\x00\x00\x00\x00\xFF\x75\x08\xE8\x00\x00\x00\x00\x8B\x06" ), "x????xxxx????xx", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );
            Dump( "Extra", "m_dwGlobalVars", pEngine, reinterpret_cast< unsigned char* >( "\x8B\x0D\x00\x00\x00\x00\x83\xC4\x04\x8B\x01\x68\x00\x00\x00\x00\xFF\x35\x00\x00\x00\x00" ), "xx????xxxxxx????xx????", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x12, 0x0, ss );
            Dump( "Extra", "m_dwGlowObject", pClient, reinterpret_cast< unsigned char* >( "\x8B\x0D\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x6B\xD6\x00" ), "xx????x????xx?", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x2, 0x0, ss );

            Dump( "Extra", "m_dwForceJump", pClient, reinterpret_cast< unsigned char* >( "\x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x08" ), "xx????xx????xxxxxxxx", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x2, 0x0, ss );

            Dump( "Extra", "m_dwForceAttack", pClient, reinterpret_cast< unsigned char* >( "\x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x04" ), "xx????xx????xxxxxxxx", Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x2, 0x0, ss );

            std::ofstream( "OffsetManager.txt" ) << ss.str( );
        }

        void COffsetManager::Dump( const std::string& tablename, const std::string& varname, uintptr_t offset, std::stringstream& ss )
        {
            Log( tablename, varname, pNetVarManager->GetNetVar( tablename, varname ) + offset, ss );
        }

        void COffsetManager::Dump( const std::string& tablename, const std::string& varname, Remote::CModule* pModule, const unsigned char* pPattern, const char* pMask, int type, uintptr_t pattern_offset, uintptr_t address_offset, std::stringstream& ss )
        {
            Log( tablename, varname, pProcess->FindPattern( pModule, pPattern, pMask, type, pattern_offset, address_offset ), ss );
        }

        void COffsetManager::Log( const std::string& tablename, const std::string& varname, uintptr_t offset, std::stringstream& ss )
        {
            ss << std::setw( 47 )
                << std::setfill( '_' )
                << std::left
                << ( tablename + " -> " + varname + ": " )
                << std::right
                << std::hex
                << " 0x"
                << std::setw( 8 )
                << std::setfill( '0' )
                << std::uppercase
                << offset << std::endl;
        }
    }
}
