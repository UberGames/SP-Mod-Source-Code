#ifndef __OBJECTIVES_H__
#define __OBJECTIVES_H__

// mission Objectives


// DO NOT CHANGE MAX_MISSION_OBJ. IT AFFECTS THE SAVEGAME STRUCTURE

typedef enum //# Objective_e
{
	//=================================================
	//
	//=================================================
	OBJ_ELIMINATEHIROGEN = 0,		//# TUTORIAL

	OBJ_FOSTERLIVES,		//# CROSSLEVEL
	OBJ_ODELLLIVES,			//# CROSSLEVEL
	OBJ_CSATLOSLIVES,		//# CROSSLEVEL

	// VOY1
	OBJ_TURBOLIFTTOENGINEERING,		//# VOY1

	// BORG1
	OBJ_RESCUE_TEAMMATES,	//# BORG1
	OBJ_RECLAIM_IMOD,		//# BORG1

	//VOY2
	OBJ_TAKE_TURBO,			//# VOY2
	OBJ_CONTAIN_DN,			//# VOY2
	OBJ_JEFF_JUNCTION,		//# VOY2

	//VOY3
	OBJ_TO_ENG,				//# VOY3
	OBJ_AVOID_BREACH,		//# VOY3
	OBJ_SHUTDOWNRELAYS,		//# VOY3
	OBJ_DECOUPLEMATRIX,		//# VOY3
	OBJ_REPEL_CB8,			//# VOY3

	//VOY4
	OBJ_REPEL_CB7,			//# VOY4

	//VOY5
	OBJ_NEUTRALIZE15,		//# VOY5
	OBJ_RESUPPLY,			//# VOY5
	OBJ_BEAMOUT,			//# VOY5

	//STASIS1
	OBJ_LOCTERMINAL,		//# STASIS1
	OBJ_PROTTECH,			//# STASIS1
	OBJ_SECTION29,			//# STASIS1

	//STASIS2			
	OBJ_COMPCORE,			//# STASIS2
	
	//STASIS3
	OBJ_MAINCORE,			//# STASIS3

	//VOY6
	OBJ_HEALING,			//# VOY6
	OBJ_HAZOP,				//# VOY6
	
	//VOY7				
	OBJ_HAZBRIEFVOY7,		//# VOY7
	OBJ_EQUIPVOY7,			//# VOY7
	OBJ_SHUTTLEBAY,			//# VOY7
	OBJ_NEUTRALIZE20,		//# VOY7

	//VOY8
	OBJ_SHUTTLEBAYVOY8,		//# VOY8
	OBJ_DOCKCLAMPS,			//# VOY8
	OBJ_MAINDECK,			//# VOY8

	//SCAV2	
	OBJ_INFILTRATE,			//# SCAV2
	OBJ_REROUTE,			//# SCAV2

	//SCAV3
	OBJ_FINDODELL,			//# SCAV3
	OBJ_FINDODELLISO,		//# SCAV3

	//SCAV4
	OBJ_FINDTELSIA,			//# SCAV4

	//SCAV5
	OBJ_EXTRACTION,			//# SCAV5

	//SCAVBOSS
	OBJ_EXTRACTBOSS,		//# SCAVBOSS

	//VOY9
	OBJ_WAITTUVOK,			//# VOY9
	OBJ_ASTROMETRICSDECK8,	//# VOY9

	//BORG3
	OBJ_RECOVERISO,			//# BORG3
	OBJ_RESCUEFOSTER,		//# BORG3

	//BORG5
	OBJ_CLEANOUT8472,		//# BORG5

	//VOY13
	OBJ_TESTWEAPONS,		//# VOY13
	OBJ_MEETTELSIAMESSHALL,	//# VOY13
	OBJ_NEUTRALIZE25,		//# VOY13

	//VOY14
	OBJ_MESSDECK2,			//# VOY14

	//VOY15
	OBJ_GETHELMET,			//# VOY15
	OBJ_GETGOODS,			//# VOY15
	OBJ_BEAMOUTVOY15,		//# VOY15

	//DN1
	OBJ_RESTOREENV,			//# DN1
	OBJ_ESCORTTUVOK,		//# DN1

	//DN2
	OBJ_DEBRIS,				//# DN2

	//DN3
	OBJ_REALIGNBEAM,		//# DN3
	OBJ_LOADINGCHAMBER,		//# DN3

	//DN8
	OBJ_LOADROUND,			//# DN8

	//VOY16
	OBJ_REPELHARVESTERS,	//# VOY16

	//FORGE1
	OBJ_NAVIGATEHULL,		//# FORGE1

	//FORGE2	
	OBJ_SECGRID,			//# FORGE2
	OBJ_CENTRALSHAFT,		//# FORGE2

	//FORGE3
	OBJ_LOCMAINSHAFT,		//# FORGE3
	OBJ_MEETREENFORCEMENTS,	//# FORGE3

	//FORGE4		
	OBJ_DESTROYGENERATOR,	//# FORGE4

	//FORGE5
	OBJ_GETTOSHUTTLE,		//# FORGE5
	OBJ_STOPSEEDLAUNCH,		//# FORGE5

	//FORGEBOSS
	OBJ_FORGESEED,			//# FORGEBOSS

	OBJ_ISODESIUM1,		//# CROSSLEVEL
	OBJ_ISODESIUM2,		//# CROSSLEVEL
	OBJ_ISODESIUM3,		//# CROSSLEVEL
	OBJ_ISODESIUMALL,	//# CROSSLEVEL
	//# #eol
	MAX_OBJECTIVES,
} objectiveNumber_t;

typedef enum //# Tour_Objective_e
{
	OBJ_SECURITYCODE,	//# CROSSLEVEL

	OBJ_ENGAGEWARP,			//# VIRTUAL VOYAGER
	OBJ_REDALERT,			//# VIRTUAL VOYAGER
	OBJ_SELFDESTRUCT,		//# VIRTUAL VOYAGER
	OBJ_TRANSPORTER,		//# VIRTUAL VOYAGER
	OBJ_DECK15,				//# VIRTUAL VOYAGER
	OBJ_ASTROMETRICS,		//# VIRTUAL VOYAGER
	OBJ_ACCESSCODES,			//# VIRTUAL VOYAGER
	OBJ_LAUNCHSHUTTLE,		//# VIRTUAL VOYAGER
	OBJ_SHUTDOWNWARP,		//# VIRTUAL VOYAGER
	OBJ_SECRETITEMS,		//# VIRTUAL VOYAGER
	OBJ_DOLL_MUNRO,			//# VIRTUAL VOYAGER
	OBJ_DOLL_FOSTER,		//# VIRTUAL VOYAGER
	OBJ_DOLL_TELSIA,		//# VIRTUAL VOYAGER
	OBJ_DOLL_ALEXANDRIA,	//# VIRTUAL VOYAGER
	OBJ_DOLL_BIESSMAN,		//# VIRTUAL VOYAGER
	OBJ_DOLL_CHELL,			//# VIRTUAL VOYAGER
	OBJ_DOLL_CHANG,			//# VIRTUAL VOYAGER
	OBJ_DOLL_JUROT,			//# VIRTUAL VOYAGER
	OBJ_DOLL_BORG_FOSTER,	//# VIRTUAL VOYAGER

	OBJ_COLLECTEDACTIONFIGURES,	//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_HARVESTER_LEG,		//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_EF_POSTER,			//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_SEVEN_PLATE,		//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_FIREFLIES,			//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_ARC_WELDER,			//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_GRENADE_LAUNCHER,	//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_BIESSMAN_MORGUE,	//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_BORG_SLAYER,		//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_RAVEN_PLAQUE,		//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_HERETIC_II_BOX,		//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_SOF_BOX,			//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)

	OBJ_PHOTONBURST,		//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_TETRYONDISRUPTOR,	//# VIRTUAL VOYAGER (CROSSLEVEL TACTICAL)
	OBJ_GETPADD,			//# VIRTUAL VOYAGER (HOLODECK MISSION)
	OBJ_SAVEGOODHEART,		//# VIRTUAL VOYAGER (HOLODECK MISSION)
	OBJ_BS_LOCATEWEAPON,	//# VIRTUAL VOYAGER (BORG SLAYER)
	OBJ_BS_SAVESEVEN,		//# VIRTUAL VOYAGER (BORG SLAYER)
	OBJ_TOURSUCCESS,		//#	VIRTUAL VOYAGER SUCCESSFULLY COMPLETED TOUR MODE.

	//# #eol
	MAX_TOUR_OBJECTIVES,
} tourobjectiveNumber_t;

typedef enum //# Tactical_e
{
	//=================================================
	//
	//=================================================
	TACT_HIROGENARE=0,			//#
	TACT_JEFFERIES,				//#
	TACT_TURBOLIFT, 	  		//#
	TACT_DESTROY_BORG_NODES,	//#
	TACT_BORG_WILL_ADAPT,		//#
	TACT_IMOD_DESIGNED,			//#
	TACT_CORE_EJECT,			//#
	TACT_COVER,					//#
	TACT_HOLODECK5,				//#
	TACT_HOLODECKIS,			//#
	TACT_FIREFLIES,				//#
	TACT_ALIENTRANSPORT,		//#
	TACT_FORCESHIELDS,			//#
	TACT_ALIENENERGYPODS,		//#
	TACT_MAGDOCKCLAMPS,			//#
	TACT_ISODESIUM,				//#
	TACT_CROUCH,				//#
	TACT_SHADOWS,				//#
	TACT_LEANING,				//#
	TACT_ENVHAZ,				//#
	TACT_ALERTNOSTEALTH,		//#
	TACT_AVOIDCONF,				//#
	TACT_AVOIDCONFPANELS,		//#
	TACT_REALBORG,				//#
	TACT_8472DEF,				//#
	TACT_8472TACT,				//#
	TACT_DNNOTEMPTY,			//#
	TACT_GUNSHIPDEF,			//#
	TACT_ENERGYCHARGE,			//#
	TACT_ROBOTDEFENSE,			//#
	TACT_DISABLEDHARV,			//#
	TACT_NAVHULL,				//#
	TACT_DAMPENINGGEN,			//#

	TACT_EASTEREGG1,			//#
	TACT_EASTEREGG2,			//#
	TACT_EASTEREGG3,			//#
	TACT_EASTEREGG4,			//#
	TACT_EASTEREGG5,			//#
	TACT_EASTEREGG6,			//#
	TACT_EASTEREGG7,			//#
	TACT_EASTEREGG8,			//#
	TACT_EASTEREGG9,			//#
	TACT_EASTEREGG10,			//#
	TACT_EASTEREGG11,			//#
	TACT_EASTEREGG12,			//#
	TACT_EASTEREGG13,			//#
	TACT_EASTEREGG14,			//#
	TACT_HOWMANY_DOLLS,			//#

	//# #eol
	MAX_TACTICAL,
} tacticalNumber_t;

typedef enum //# StatusText_e
{
	//=================================================
	//
	//=================================================
	STAT_INSUBORDINATION = 0,		//# Starfleet will not tolerate such insubordination
	STAT_YOUCAUSEDDEATHOFTEAMMATE,	//# You caused the death of a teammate.
	STAT_DIDNTPROTECTTECH,			//# You failed to protect Chell, your technician.
	STAT_DIDNTPROTECT7OF9,			//# You failed to protect 7 of 9
	STAT_NOTSTEALTHYENOUGH,			//# You weren't quite stealthy enough
	STAT_STEALTHTACTICSNECESSARY,	//# Starfleet will not tolerate such insubordination
	STAT_WATCHYOURSTEP,				//# Watch your step
	STAT_JUDGEMENTMUCHDESIRED,		//# Your judgement leaves much to be desired

	//# #eol
	MAX_STATUSTEXT,
} statusText_t;

extern qboolean	missionInfo_Updated;

#define SET_TACTICAL_OFF	0
#define SET_TACTICAL_ON		1

#define SET_OBJ_HIDE			0
#define SET_OBJ_SHOW			1
#define SET_OBJ_PENDING			2
#define SET_OBJ_SUCCEEDED		3
#define SET_OBJ_FAILED			4
#define SET_OBJ_SUCCEEDEDTOUR	5


#define OBJECTIVE_HIDE 0
#define OBJECTIVE_SHOW 1

#define OBJECTIVE_STAT_PENDING		0
#define OBJECTIVE_STAT_SUCCEEDED	1
#define OBJECTIVE_STAT_FAILED		2

#define MAX_TACTICAL_TXT 512

extern char *mission_objective_text[MAX_OBJECTIVES];
extern char *tour_objective_text[MAX_TOUR_OBJECTIVES];

extern qboolean tactical_info[MAX_TACTICAL_TXT];
extern char *tactical_text[MAX_TACTICAL_TXT];

extern int statusTextIndex;

void OBJ_SaveObjectiveData(void);
void OBJ_LoadObjectiveData(void);
extern void OBJ_SetPendingObjectives(gentity_t *ent);

#ifndef G_OBJECTIVES_CPP

extern stringID_table_t objectiveTable [];
extern stringID_table_t tourObjectiveTable [];
extern stringID_table_t tacticalTable [];
extern stringID_table_t statusTextTable [];

#else

stringID_table_t objectiveTable [] =
{
	//=================================================
	//
	//=================================================

	ENUM2STRING(OBJ_ELIMINATEHIROGEN),//# TUTORIAL
	//# 

	ENUM2STRING(OBJ_FOSTERLIVES),			//# CROSSLEVEL
	ENUM2STRING(OBJ_ODELLLIVES),			//# CROSSLEVEL
	ENUM2STRING(OBJ_CSATLOSLIVES),			//# CROSSLEVEL

	ENUM2STRING(OBJ_TURBOLIFTTOENGINEERING),//# VOY1

	// BORG1
	ENUM2STRING(OBJ_RESCUE_TEAMMATES),		//# BORG1
	ENUM2STRING(OBJ_RECLAIM_IMOD),			//# BORG1

	//VOY2
	ENUM2STRING(OBJ_TAKE_TURBO),			//# VOY2
	ENUM2STRING(OBJ_CONTAIN_DN),			//# VOY2
	ENUM2STRING(OBJ_JEFF_JUNCTION),			//# VOY2

	//VOY3
	ENUM2STRING(OBJ_TO_ENG),				//# VOY3
	ENUM2STRING(OBJ_AVOID_BREACH),			//# VOY3
	ENUM2STRING(OBJ_SHUTDOWNRELAYS),		//# VOY3
	ENUM2STRING(OBJ_DECOUPLEMATRIX),		//# VOY3
	ENUM2STRING(OBJ_REPEL_CB8),				//# VOY3

	//VOY4
	ENUM2STRING(OBJ_REPEL_CB7),				//# VOY4

	//VOY5
	ENUM2STRING(OBJ_NEUTRALIZE15),			//# VOY5
	ENUM2STRING(OBJ_RESUPPLY),				//# VOY5
	ENUM2STRING(OBJ_BEAMOUT),				//# VOY5

	//STASIS1
	ENUM2STRING(OBJ_LOCTERMINAL),			//# STASIS1
	ENUM2STRING(OBJ_PROTTECH),				//# STASIS1
	ENUM2STRING(OBJ_SECTION29),				//# STASIS1

	//STASIS2			
	ENUM2STRING(OBJ_COMPCORE),				//# STASIS2
	
	//STASIS3
	ENUM2STRING(OBJ_MAINCORE),				//# STASIS3

	//VOY6
	ENUM2STRING(OBJ_HEALING),				//# VOY6
	ENUM2STRING(OBJ_HAZOP),					//# VOY6
	
	//VOY7				
	ENUM2STRING(OBJ_HAZBRIEFVOY7),			//# VOY7
	ENUM2STRING(OBJ_EQUIPVOY7),				//# VOY7
	ENUM2STRING(OBJ_SHUTTLEBAY),			//# VOY7
	ENUM2STRING(OBJ_NEUTRALIZE20),			//# VOY7

	//VOY8
	ENUM2STRING(OBJ_SHUTTLEBAYVOY8),		//# VOY8
	ENUM2STRING(OBJ_DOCKCLAMPS),			//# VOY8
	ENUM2STRING(OBJ_MAINDECK),				//# VOY8

	//SCAV2	
	ENUM2STRING(OBJ_INFILTRATE),				//# SCAV2
	ENUM2STRING(OBJ_REROUTE),				//# SCAV2

	//SCAV3
	ENUM2STRING(OBJ_FINDODELL),				//# SCAV3
	ENUM2STRING(OBJ_FINDODELLISO),			//# SCAV3

	//SCAV4
	ENUM2STRING(OBJ_FINDTELSIA),				//# SCAV4

	//SCAV5
	ENUM2STRING(OBJ_EXTRACTION),			//# SCAV5

	//SCAVBOSS
	ENUM2STRING(OBJ_EXTRACTBOSS),			//# SCAVBOSS


	//VOY9
	ENUM2STRING(OBJ_WAITTUVOK),				//# VOY9
	ENUM2STRING(OBJ_ASTROMETRICSDECK8),		//# VOY9


	//BORG3
	ENUM2STRING(OBJ_RECOVERISO),		//# BORG3
	ENUM2STRING(OBJ_RESCUEFOSTER),		//# BORG3

	//BORG5
	ENUM2STRING(OBJ_CLEANOUT8472),		//# BORG5

	//VOY13
	ENUM2STRING(OBJ_TESTWEAPONS),			//# VOY13
	ENUM2STRING(OBJ_MEETTELSIAMESSHALL),	//# VOY13
	ENUM2STRING(OBJ_NEUTRALIZE25),			//# VOY13

	//VOY14
	ENUM2STRING(OBJ_MESSDECK2),			//# VOY14

	//VOY15
	ENUM2STRING(OBJ_GETHELMET),			//# VOY15
	ENUM2STRING(OBJ_GETGOODS),			//# VOY15
	ENUM2STRING(OBJ_BEAMOUTVOY15),		//# VOY15

	//DN1
	ENUM2STRING(OBJ_RESTOREENV),			//# DN1
	ENUM2STRING(OBJ_ESCORTTUVOK),		//# DN1

	//DN2
	ENUM2STRING(OBJ_DEBRIS),				//# DN2

	//DN3
	ENUM2STRING(OBJ_REALIGNBEAM),		//# DN3
	ENUM2STRING(OBJ_LOADINGCHAMBER),		//# DN3

	//DN8
	ENUM2STRING(OBJ_LOADROUND),			//# DN8

	//VOY16
	ENUM2STRING(OBJ_REPELHARVESTERS),	//# VOY16

	//FORGE1
	ENUM2STRING(OBJ_NAVIGATEHULL),		//# FORGE1

	//FORGE2	
	ENUM2STRING(OBJ_SECGRID),			//# FORGE2
	ENUM2STRING(OBJ_CENTRALSHAFT),		//# FORGE2

	//FORGE3
	ENUM2STRING(OBJ_LOCMAINSHAFT),			//# FORGE3
	ENUM2STRING(OBJ_MEETREENFORCEMENTS),	//# FORGE3

	//FORGE4		
	ENUM2STRING(OBJ_DESTROYGENERATOR),		//# FORGE4

	//FORGE5
	ENUM2STRING(OBJ_GETTOSHUTTLE),		//# FORGE5
	ENUM2STRING(OBJ_STOPSEEDLAUNCH),	//# FORGE5

	//
	ENUM2STRING(OBJ_FORGESEED),			//# FORGEBOSS

	ENUM2STRING(OBJ_ISODESIUM1),			//# CROSSLEVEL
	ENUM2STRING(OBJ_ISODESIUM2),			//# CROSSLEVEL
	ENUM2STRING(OBJ_ISODESIUM3),			//# CROSSLEVEL
	ENUM2STRING(OBJ_ISODESIUMALL),			//# CROSSLEVEL

	//stringID_table_t Must end with a null entry
	"", NULL
};


stringID_table_t tourObjectiveTable [] =
{

	ENUM2STRING(OBJ_SECURITYCODE),			//# CROSSLEVEL

	ENUM2STRING(OBJ_ENGAGEWARP),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_REDALERT),				//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_SELFDESTRUCT),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_TRANSPORTER),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DECK15),				//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_ASTROMETRICS),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_ACCESSCODES),				//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_LAUNCHSHUTTLE),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_SHUTDOWNWARP),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_SECRETITEMS),			//# VIRTUAL VOYAGER

	ENUM2STRING(OBJ_DOLL_MUNRO),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_FOSTER),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_TELSIA),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_ALEXANDRIA),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_BIESSMAN),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_CHELL),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_CHANG),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_JUROT),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_DOLL_BORG_FOSTER),		//# VIRTUAL VOYAGER

	ENUM2STRING(OBJ_COLLECTEDACTIONFIGURES),	//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_HARVESTER_LEG),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_EF_POSTER),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_SEVEN_PLATE),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_FIREFLIES),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_ARC_WELDER),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_GRENADE_LAUNCHER),	//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_BIESSMAN_MORGUE),	//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_BORG_SLAYER),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_RAVEN_PLAQUE),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_HERETIC_II_BOX),	//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_SOF_BOX),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_PHOTONBURST),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_TETRYONDISRUPTOR),	//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_GETPADD),			//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_SAVEGOODHEART),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_BS_LOCATEWEAPON),	//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_BS_SAVESEVEN),		//# VIRTUAL VOYAGER
	ENUM2STRING(OBJ_TOURSUCCESS),		//# VIRTUAL VOYAGER

	//stringID_table_t Must end with a null entry
	"", NULL
};


stringID_table_t tacticalTable [] =
{
	//=================================================
	//
	//=================================================
	ENUM2STRING(TACT_HIROGENARE),			//#
	ENUM2STRING(TACT_JEFFERIES),			//#
	ENUM2STRING(TACT_TURBOLIFT), 	  		//#
	ENUM2STRING(TACT_DESTROY_BORG_NODES),	//#
	ENUM2STRING(TACT_BORG_WILL_ADAPT),		//#
	ENUM2STRING(TACT_IMOD_DESIGNED),		//#
	ENUM2STRING(TACT_CORE_EJECT),			//#
	ENUM2STRING(TACT_COVER),				//#
	ENUM2STRING(TACT_HOLODECK5),			//#
	ENUM2STRING(TACT_HOLODECKIS),			//#
	ENUM2STRING(TACT_FIREFLIES),			//#
	ENUM2STRING(TACT_ALIENTRANSPORT),		//#
	ENUM2STRING(TACT_FORCESHIELDS),			//#
	ENUM2STRING(TACT_ALIENENERGYPODS),		//#
	ENUM2STRING(TACT_MAGDOCKCLAMPS),		//#
	ENUM2STRING(TACT_ISODESIUM),			//#
	ENUM2STRING(TACT_CROUCH),				//#
	ENUM2STRING(TACT_SHADOWS),				//#
	ENUM2STRING(TACT_LEANING),				//#
	ENUM2STRING(TACT_ENVHAZ),				//#
	ENUM2STRING(TACT_ALERTNOSTEALTH),		//#
	ENUM2STRING(TACT_AVOIDCONF),			//#
	ENUM2STRING(TACT_AVOIDCONFPANELS),		//#
	ENUM2STRING(TACT_REALBORG),				//#
	ENUM2STRING(TACT_8472DEF),				//#
	ENUM2STRING(TACT_8472TACT),				//#
	ENUM2STRING(TACT_DNNOTEMPTY),			//#
	ENUM2STRING(TACT_GUNSHIPDEF),			//#
	ENUM2STRING(TACT_ENERGYCHARGE),			//#
	ENUM2STRING(TACT_ROBOTDEFENSE),			//#
	ENUM2STRING(TACT_DISABLEDHARV),			//#
	ENUM2STRING(TACT_NAVHULL),				//#
	ENUM2STRING(TACT_DAMPENINGGEN),			//#

	ENUM2STRING(TACT_EASTEREGG1),			//#
	ENUM2STRING(TACT_EASTEREGG2),			//#
	ENUM2STRING(TACT_EASTEREGG3),			//#
	ENUM2STRING(TACT_EASTEREGG4),			//#
	ENUM2STRING(TACT_EASTEREGG5),			//#
	ENUM2STRING(TACT_EASTEREGG6),			//#
	ENUM2STRING(TACT_EASTEREGG7),			//#
	ENUM2STRING(TACT_EASTEREGG8),			//#
	ENUM2STRING(TACT_EASTEREGG9),			//#
	ENUM2STRING(TACT_EASTEREGG10),			//#
	ENUM2STRING(TACT_EASTEREGG11),			//#
	ENUM2STRING(TACT_EASTEREGG12),			//#
	ENUM2STRING(TACT_EASTEREGG13),			//#
	ENUM2STRING(TACT_EASTEREGG14),			//#
	ENUM2STRING(TACT_HOWMANY_DOLLS),		//#

	//stringID_table_t Must end with a null entry
	"", NULL
};

stringID_table_t statusTextTable [] =
{
	//=================================================
	//
	//=================================================
	ENUM2STRING(STAT_INSUBORDINATION),				//# Starfleet will not tolerate such insubordination
	ENUM2STRING(STAT_YOUCAUSEDDEATHOFTEAMMATE),		//# You caused the death of a teammate.
	ENUM2STRING(STAT_DIDNTPROTECTTECH),				//# You failed to protect Chell, your technician.
	ENUM2STRING(STAT_DIDNTPROTECT7OF9),				//# You failed to protect 7 of 9
	ENUM2STRING(STAT_NOTSTEALTHYENOUGH),			//# You weren't quite stealthy enough
	ENUM2STRING(STAT_STEALTHTACTICSNECESSARY),		//# Starfleet will not tolerate such insubordination
	ENUM2STRING(STAT_WATCHYOURSTEP),				//# Watch your step
	ENUM2STRING(STAT_JUDGEMENTMUCHDESIRED),			//# Your judgement leaves much to be desired
	//stringID_table_t Must end with a null entry
	"", NULL
};

#endif// #ifndef G_OBJECTIVES_CPP


#endif// #ifndef __OBJECTIVES_H__

