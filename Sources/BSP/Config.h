#ifndef _CONFIG_H_
#define _CONFIG_H_

#define _FOSC_2_		32000000L

typedef enum {
	CeWarning			= 1,
	CeSuccess			= 0,
	CeNotInitialized	= -1,
	CeBadParameter		= -2,
	CeNotConfigured 	= -3,
	CeDrvError			= -4
} TeRetVal;

#endif //_CONFIG_H_