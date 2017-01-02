#ifndef CONSTANTS_H
#define CONSTANTS_H


#define numOfCelstialObjects 9
 


#define EARTH_TEXTURE "media\\earthmap.tga"
#define EARTH_NIGHT_TEXTURE "media\\earthlights2.tga"
#define EARTH_LIGHTS_TEXTURE "media\\earthlights.tga"
#define	EARTH_DISTANCE_FROM_SUN 23.5f
#define	EARTH_ROTATION_SPEED 20.0f
#define	EARTH_REVALTUION_SPEED 160
#define EARTH_SCALE 3



#define SUN_TEXTURE "media\\sunmap.tga"
#define SUN_DISTANCE_FROM_SUN 0.0f
#define SUN_ROTATION_SPEED 10
#define SUN_REVALTUION_SPEED 0.0f
#define SUN_SCALE 32

#define MERCURY_TEXTURE "media\\mercurymap.tga"
#define	MERCURY_DISTANCE_FROM_SUN 34
#define	MERCURY_ROTATION_SPEED (EARTH_ROTATION_SPEED*5.865f)
#define	MERCURY_REVALTUION_SPEED EARTH_REVALTUION_SPEED*0.24f
#define MERCURY_SCALE EARTH_SCALE*0.382

#define VENUS_TEXTURE "media\\venusmap.tga"
#define	VENUS_DISTANCE_FROM_SUN 18.32
#define	VENUS_ROTATION_SPEED EARTH_ROTATION_SPEED*(2.43)
#define	VENUS_REVALTUION_SPEED EARTH_REVALTUION_SPEED*0.62f
#define VENUS_SCALE EARTH_SCALE*0.849



#define MARS_TEXTURE "media\\marsmap.tga"
#define	MARS_DISTANCE_FROM_SUN 55//EARTH_DISTANCE_FROM_SUN*1.52
#define	MARS_ROTATION_SPEED EARTH_ROTATION_SPEED* 0.551
#define	MARS_REVALTUION_SPEED EARTH_REVALTUION_SPEED* 0.0286
#define MARS_SCALE EARTH_SCALE*0.532

#define JUPITER_TEXTURE "media\\jupitermap.tga"
#define	JUPITER_DISTANCE_FROM_SUN 7.3//5.20
#define	JUPITER_ROTATION_SPEED EARTH_ROTATION_SPEED*0.43
#define	JUPITER_REVALTUION_SPEED EARTH_REVALTUION_SPEED*0.288
#define JUPITER_SCALE EARTH_SCALE*5.5//11.209

#define SATRUN_TEXTURE "media\\saturnmap.tga"
#define	SATRUN_DISTANCE_FROM_SUN 12.9
#define	SATRUN_ROTATION_SPEED EARTH_ROTATION_SPEED*0.38
#define	SATRUN_REVALTUION_SPEED EARTH_REVALTUION_SPEED*0.288
#define SATRUN_SCALE EARTH_SCALE*4.2

#define URANUS_TEXTURE "media\\uranusmap.tga"
#define	URANUS_DISTANCE_FROM_SUN 22
#define	URANUS_ROTATION_SPEED EARTH_ROTATION_SPEED*0.34
#define	URANUS_REVALTUION_SPEED EARTH_REVALTUION_SPEED*0.288
#define URANUS_SCALE EARTH_SCALE*2.9

#define NEPTUNE_TEXTURE "media\\neptunemap.tga"
#define	NEPTUNE_DISTANCE_FROM_SUN 29//*30.06
#define	NEPTUNE_ROTATION_SPEED EARTH_ROTATION_SPEED*0.32
#define	NEPTUNE_REVALTUION_SPEED EARTH_REVALTUION_SPEED*0.288
#define NEPTUNE_SCALE EARTH_SCALE*2.5

#define PLUTO_TEXTURE "media\\plutomap.tga"
#define	PLUTO_DISTANCE_FROM_SUN 40//*0.39
#define	PLUTO_ROTATION_SPEED 30
#define	PLUTO_REVALTUION_SPEED 35
#define PLUTO_SCALE EARTH_SCALE//*0.949
#endif


