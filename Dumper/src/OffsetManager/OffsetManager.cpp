#include "HOffsetManager.h"

#include <sstream>
#include <iomanip>

#include "../Utilis/HUtilis.h"
#include "../NetVarManager/HNetVarManager.h"

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

        void COffsetManager::Dump( void ) const
        {
            auto pClient = pProcess->GetModuleByName( "client.dll" );
            auto pEngine = pProcess->GetModuleByName( "engine.dll" );

            if( !pClient || !pEngine ) {
                return;
            }

            std::stringstream ss;
            ss << "- - - - - - Tool by Y3t1y3t ( uc ) - - - - - - " << std::endl;
            ss << "| -> http://www.unknowncheats.me/forum/counterstrike-global-offensive/100856-cs-go-offset-dumper-small-one.html" << std::endl;
            ss << "| -> " << Utilis::GetTime();
            ss << "- -" << std::endl << std::endl;

            DumpNetVar( "DT_WeaponCSBase", "m_fAccuracyPenalty", 0x0, ss );

            DumpNetVar( "DT_BaseAnimating", "m_nForceBone", 0x0, ss );

            DumpNetVar( "DT_BaseCombatWeapon", "m_iState", 0x0, ss );
            DumpNetVar( "DT_BaseCombatWeapon", "m_iClip1", 0x0, ss );
            DumpNetVar( "DT_BaseCombatWeapon", "m_flNextPrimaryAttack", 0x0, ss );

            DumpPatternOffset( "DT_BaseCombatWeapon", "m_bCanReload", pClient,
                               reinterpret_cast< unsigned char* >( "\x80\xB9\x00\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\xA1" ),
                               "xx?????xx????x",
                               Remote::SignatureType::READIT, 0x2, 0x0, ss );

            DumpNetVar( "DT_BaseCombatWeapon", "m_iPrimaryAmmoType", 0x0, ss );

            LogToStringStream( "DT_BaseCombatWeapon", "m_iWeaponID",
                               pNetVarManager->GetNetVar( "DT_WeaponCSBase", "m_fAccuracyPenalty" ) + 0x24, ss );

            DumpNetVar( "DT_WeaponCSBaseGun", "m_zoomLevel", 0x0, ss );

            DumpNetVar( "DT_BaseEntity", "m_bSpotted", 0x0, ss );
            DumpNetVar( "DT_BaseEntity", "m_bSpottedByMask", 0x0, ss );
            DumpNetVar( "DT_BaseEntity", "m_hOwnerEntity", 0x0, ss );
            DumpNetVar( "DT_BaseEntity", "m_vecOrigin", 0x0, ss );
            DumpNetVar( "DT_BaseEntity", "m_iTeamNum", 0x0, ss );

            DumpNetVar( "DT_CSPlayer", "m_flFlashMaxAlpha", 0x0, ss );
            DumpNetVar( "DT_CSPlayer", "m_flFlashDuration", 0x0, ss );

            LogToStringStream( "DT_CSPlayer", "m_iGlowIndex",
                               pNetVarManager->GetNetVar( "DT_CSPlayer", "m_flFlashDuration" ) + 0x18, ss );

            DumpNetVar( "DT_CSPlayer", "m_angEyeAngles", 0x0, ss );
            DumpNetVar( "DT_CSPlayer", "m_iAccount", 0x0, ss );
            DumpNetVar( "DT_CSPlayer", "m_ArmorValue", 0x0, ss );
            DumpNetVar( "DT_CSPlayer", "m_bGunGameImmunity", 0x0, ss );
            DumpNetVar( "DT_CSPlayer", "m_iShotsFired", 0x0, ss );

            DumpPatternOffset( "DT_CSPlayerResource", "CSPlayerResource", pClient,
                               reinterpret_cast< unsigned char* >( "\x8B\x3D\x00\x00\x00\x00\x85\xFF\x0F\x84\x00\x00\x00\x00\x81\xC7" ),
                               "xx????xxxx????xx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x2, 0x0, ss );

            DumpNetVar( "DT_CSPlayerResource", "m_iCompetitiveRanking", 0x0, ss );
            DumpNetVar( "DT_CSPlayerResource", "m_iCompetitiveWins", 0x0, ss );
            DumpNetVar( "DT_CSPlayerResource", "m_iKills", 0x0, ss );
            DumpNetVar( "DT_CSPlayerResource", "m_iAssists", 0x0, ss );
            DumpNetVar( "DT_CSPlayerResource", "m_iDeaths", 0x0, ss );
            DumpNetVar( "DT_CSPlayerResource", "m_iPing", 0x0, ss );
            DumpNetVar( "DT_CSPlayerResource", "m_iScore", 0x0, ss );
            DumpNetVar( "DT_CSPlayerResource", "m_szClan", 0x0, ss );

            DumpNetVar( "DT_BasePlayer", "m_lifeState", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_fFlags", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_iHealth", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_hLastWeapon", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_hMyWeapons", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_hActiveWeapon", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_Local", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_vecViewOffset[0]", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_nTickBase", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_vecVelocity[0]", 0x0, ss );
            DumpNetVar( "DT_BasePlayer", "m_szLastPlaceName", 0x0, ss );

            LogToStringStream( "DT_Local", "m_vecPunch", pNetVarManager->GetNetVar( "DT_BasePlayer", "m_Local" ) + 0x70, ss );
            LogToStringStream( "DT_Local", "m_iCrossHairID", pNetVarManager->GetNetVar( "DT_CSPlayer", "m_bHasDefuser" ) + 0x50, ss );

            LogToStringStream( "BaseEntity", "m_dwModel", 0x6C, ss );
            LogToStringStream( "BaseEntity", "m_dwIndex", 0x64, ss );
            LogToStringStream( "BaseEntity", "m_dwBoneMatrix", pNetVarManager->GetNetVar( "DT_BaseAnimating", "m_nForceBone" ) + 0x1C, ss );
            LogToStringStream( "BaseEntity", "m_bMoveType", 0x258, ss );
            LogToStringStream( "BaseEntity", "m_bDormant", 0xE9, ss );

            DumpPatternOffset( "ClientState", "m_dwClientState", pEngine,
                               reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05\x00\x00\x00\x00" ),
                               "x????xxxx????xxxxx????",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );

            DumpPatternOffset( "ClientState", "m_dwLocalPlayerIndex", pEngine,
                               reinterpret_cast< unsigned char* >( "\x8B\x80\x00\x00\x00\x00\x40\xC3" ),
                               "xx????xx",
                               Remote::SignatureType::READIT, 0x2, 0x0, ss );

            DumpPatternOffset( "ClientState", "m_dwInGame", pEngine,
                               reinterpret_cast< unsigned char* >( "\x83\xB9\x00\x00\x00\x00\x06\x0F\x94\xC0\xC3" ),
                               "xx?xxxxxxxx",
                               Remote::SignatureType::READIT, 0x2, 0x0, ss );

            DumpPatternOffset( "ClientState", "m_dwMaxPlayer", pEngine,
                               reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\x8B\x80\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\x55\x8B\xEC\x8B\x45\x08" ),
                               "x????xx????xxxxxxxxxxx",
                               Remote::SignatureType::READIT, 0x7, 0x0, ss );

            DumpPatternOffset( "ClientState", "m_dwMapDirectory", pEngine,
                               reinterpret_cast< unsigned char* >( "\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x80\x3D" ),
                               "x????x???????xx",
                               Remote::SignatureType::READIT, 0x1, 0x0, ss );

            DumpPatternOffset( "ClientState", "m_dwMapname", pEngine,
                               reinterpret_cast< unsigned char* >( "\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00" ),
                               "x????xxxxxxxxx????",
                               Remote::SignatureType::READIT, 0x1, 0x0, ss );

            DumpPatternOffset( "ClientState", "m_dwPlayerInfo", pEngine,
                               reinterpret_cast< unsigned char* >( "\x8B\x88\x00\x00\x00\x00\x8B\x01\x8B\x40\x00\xFF\xD0\x8B\xF8" ),
                               "xx????xxxx?xxxx",
                               Remote::SignatureType::READIT, 0x2, 0x0, ss );

            DumpPatternOffset( "ClientState", "m_dwViewAngles", pEngine,
                               reinterpret_cast< unsigned char* >( "\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05\x00\x00\x00\x00" ),
                               "xxxx????xxxxx????",
                               Remote::SignatureType::READIT, 0x4, 0x0, ss );

            DumpPatternOffset( "EngineRender", "m_dwViewMatrix", pClient,
                               reinterpret_cast< unsigned char* >( "\x81\xC6\x00\x00\x00\x00\x88\x45\x92\x0F\xB6\xC0" ),
                               "xx????xxxxxx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x33C, 0xB0, ss );

            DumpPatternOffset( "EngineRender", "m_dwEnginePosition", pEngine,
                               reinterpret_cast< unsigned char* >( "\xF3\x0F\x11\x15\x00\x00\x00\x00\xF3\x0F\x11\x0D\x00\x00\x00\x00\xF3\x0F\x11\x05\x00\x00\x00\x00\xF3\x0F\x11\x3D\x00\x00\x00\x00" ),
                               "xxxx????xxxx????xxxx????xxxx????",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x4, 0x0, ss );

            DumpPatternOffset( "RadarBase", "m_dwRadarBase", pClient,
                               reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\x8B\x0C\xB0\x8B\x01\xFF\x50\x00\x46\x3B\x35\x00\x00\x00\x00\x7C\xEA\x8B\x0D\x00\x00\x00\x00" ),
                               "x????xxxxxxx?xxx????xxxx????",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );

            DumpNetVar( "RadarBase", "m_dwRadarBasePointer", 0x50, ss );

            DumpPatternOffset( "LocalPlayer", "m_dwLocalPlayer", pClient,
                               reinterpret_cast< unsigned char* >( "\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3\x6A\x00" ),
                               "x????xx????????x????xxxx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x10, ss );

            DumpPatternOffset( "EntityList", "m_dwEntityList", pClient,
                               reinterpret_cast< unsigned char* >( "\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8" ),
                               "x????xxxxx????xx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );

            DumpPatternOffset( "WeaponTable", "m_dwWeaponTable", pClient,
                               reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\x0F\xB7\xC9\x03\xC9\x8B\x44\x00\x0C\xC3" ),
                               "x????xxxxxxx?xx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );

            DumpPatternOffset( "WeaponTable", "m_dwWeaponTableIndex", pClient,
                               reinterpret_cast< unsigned char* >( "\x66\x8B\x8E\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x05\x00\x00\x00\x00\x50" ),
                               "xxx??xxx????x????x",
                               Remote::SignatureType::READIT, 0x3, 0x0, ss );

            DumpPatternOffset( "Extra", "m_dwInput", pClient,
                               reinterpret_cast< unsigned char* >( "\xB9\x00\x00\x00\x00\xFF\x75\x08\xE8\x00\x00\x00\x00\x8B\x06" ),
                               "x????xxxx????xx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x1, 0x0, ss );

            DumpPatternOffset( "Extra", "m_dwGlobalVars", pEngine,
                               reinterpret_cast< unsigned char* >( "\x8B\x0D\x00\x00\x00\x00\x83\xC4\x04\x8B\x01\x68\x00\x00\x00\x00\xFF\x35\x00\x00\x00\x00" ),
                               "xx????xxxxxx????xx????",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x12, 0x0, ss );

            DumpPatternOffset( "Extra", "m_dwGlowObject", pClient,
                               reinterpret_cast< unsigned char* >( "\xA1\x00\x00\x00\x00\xA8\x01\x75\x00\x0F\x57\xC0\xC7\x05" ),
                               "x????xxx?xxxxx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x58, 0x0, ss );

            DumpPatternOffset( "Extra", "m_dwForceJump", pClient,
                               reinterpret_cast< unsigned char* >( "\x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x08" ),
                               "xx????xx????xxxxxxxx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x2, 0x0, ss );

            DumpPatternOffset( "Extra", "m_dwForceAttack", pClient
                               , reinterpret_cast< unsigned char* >( "\x89\x15\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\xF6\xC2\x03\x74\x03\x83\xCE\x04" ),
                               "xx????xx????xxxxxxxx",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x2, 0x0, ss );

            DumpPatternOffset( "Extra", "m_dwSensitivity", pClient
                               , reinterpret_cast< unsigned char* >( "\xF3\x0F\x10\x05\x00\x00\x00\x00\xEB\x17\x8B\x01\x8B\x40\x30\xFF\xD0\xF3\x0F\x10\x0D\x00\x00\x00\x00" ),
                               "xxxx????xxxxxxxxxxxxx????",
                               Remote::SignatureType::READIT | Remote::SignatureType::SUBTRACT, 0x4, 0x0, ss );

            std::ofstream( "OffsetManager.txt" ) << ss.str();
        }

        void COffsetManager::DumpNetVar( const std::string& tablename, const std::string& varname, uintptr_t offset, std::stringstream& ss ) const
        {
            LogToStringStream( tablename, varname, pNetVarManager->GetNetVar( tablename, varname ) + offset, ss );
        }

        void COffsetManager::DumpPatternOffset( const std::string& tablename, const std::string& varname, Remote::CModule* pModule, const unsigned char* pPattern, const char* pMask, int type, uintptr_t pattern_offset, uintptr_t address_offset, std::stringstream& ss ) const
        {
            LogToStringStream( tablename, varname, pProcess->FindPattern( pModule, pPattern, pMask, type, pattern_offset, address_offset ), ss );
        }

        void COffsetManager::LogToStringStream( const std::string& tablename, const std::string& varname, uintptr_t offset, std::stringstream& ss ) const
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
