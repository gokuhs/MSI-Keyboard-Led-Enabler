
/** Area constants */
#define AREA_LEFT							0x01
#define AREA_MIDDLE							0x02
#define AREA_RIGHT							0x03

/** Color constants */
#define COLOR_BLACK							0x00
#define COLOR_RED							0x01
#define COLOR_ORANGE							0x02
#define COLOR_YELLOW							0x03
#define COLOR_GREEN							0x04
#define COLOR_TINYGREEN							0x10
#define COLOR_SKY							0x05
#define COLOR_BLUE							0x06
#define COLOR_DARKBLUE							0x02
#define COLOR_TINYBLUE							0X01
#define COLOR_PINK							0x03
#define COLOR_TINYPINK							0x1D
#define COLOR_LIGHTPINK							0x06
#define COLOR_PURPLE							0x07
#define COLOR_LIGHTPURPLE						0x31
#define COLOR_WHITE							0x08
#define COlOR_GREY							0x10
#define UCHAR_MAX							0xFF

/** Level constants. High is more intense light */
#define LEVEL_1								0x00
#define LEVEL_2								0x01
#define LEVEL_3								0x02
#define LEVEL_4								0x03

/** Lights modes */
#define MODE_NORMAL							0x01
#define MODE_GAMING							0x02
#define MODE_BREATHING						0x03
#define MODE_WAVE							0x04
#define MODE_DUAL_COLOR						0x05

/** Allowed params */
const char* PARAM_HELP =					"--help";
const char* PARAM_HELP_SHORT=				"-h";
const char* PARAM_VERS =					"--version";
const char* PARAM_VERS_SHORT=				"-v";
const char* PARAM_MODE =					"-mode";
const char* PARAM_COLOR1 =					"-color1";
const char* PARAM_COLOR2 =					"-color2";
const char* PARAM_COLOR3 =					"-color3";
const char* PARAM_LEVEL	=					"-level";
const char* CLOSE_DAEMON	=				"-exitdaemon";

/** Allowed modes values */
const char* VALUE_MODE_NORMAL = 			"normal";
const char* VALUE_MODE_GAMING = 			"gaming";
const char* VALUE_MODE_BREATHING = 			"breathing";
const char* VALUE_MODE_WAVE = 				"wave";
const char* VALUE_MODE_DUALCOLOR =			"dualcolor";

/** Allowed colors values */
const char* VALUE_COLOR_BLACK =				"black";
const char* VALUE_COLOR_RED	=			"red";
const char* VALUE_COLOR_ORANGE =			"orange";
const char* VALUE_COLOR_YELLOW =			"yellow";
const char* VALUE_COLOR_GREEN =				"green";
const char* VALUE_COLOR_SKY =				"sky";
const char* VALUE_COLOR_BLUE =				"blue";
const char* VALUE_COLOR_PURPLE =			"purple";
const char* VALUE_COLOR_WHITE =				"white";

// enum for array param values positions
enum values {
	kMode,
	kColor1,
	kColor2,
	kColor3,
	kLevel,
	kSize
};



char usage[] =
"MSI Led Enabler:\n"
"Usage [NORMAL MODE]:\n"
"msiledenabler -mode normal -color1 <valid_color> [-color2 <valid_color>] [-color3 <valid_color>]\n"
"		       -level <valid_intensity_level>\n"
"Usage [GAMING MODE]:\n"
"msiledenabler -mode gaming -color1 <valid_color> -level <valid_intensity_level>\n\n"
"Valid intensity levels: [0,1,2,3]\n"
"Valid Colors: [black|red|orange|yellow|green|sky|blue|purple|white]\n"
"Example usage: ./msiledenabler -mode normal -color1 blue -color2 green -color3 yellow -level 0\n\n";

char version[] =
"MSI Led Enabler v1.0\n"
"Author: Jesús Sánchez - Twitter: @gokuhss\n"
"Basend on  Christian Panadero code - @ bakingcode.com - Twitter: @PaNaVTEC\n";

static void skeleton_daemon();
void sendActivateArea(hid_device *handle, unsigned char area, unsigned char color, unsigned char level);
void commit(hid_device *handle, unsigned char mode);
unsigned char parseColor(char* color);
void testMode();
int  daemonMode();