/**
 * MSI Led enabler for MSI GT60 / 70 can works with other MSIs with the same keyboard.
 * The purpose of this app is to enable the keyboard light leds when using unix based systems.
 * 
 * Christian Panadero Martinez - 2012 - Bakingcode.com - @PaNaVTEC on twitter
 */

#include <stdio.h>
#include <wchar.h>
#include "hidapi.h"
#include "msg.h"
#include "msiledenabler.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>



static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("MSI_KB_LED", LOG_PID, LOG_DAEMON);
}



// Headers needed for sleeping.
#ifdef _WIN32
	#include <windows.h>
#else
	//#include <unistd.h>
#endif



/**
 * Sends to the handler the area / color and level selected. NOTE you need to commit for this applies
 */
void sendActivateArea(hid_device *handle, unsigned char area, unsigned char color, unsigned char level) {

	// Will send a 8 bytes array
	unsigned char data[8];
	memset(&data, 0x00, 8);
	data[0] = 0x01; // Fixed report value.
	data[1] = 0x02; // Fixed report value?

	data[2] = 0x42; // 42 = set color inputs / 41 = confirm
	data[3] = area; // 1 = left / 2 = middle / 3 = right
	data[4] = color; // see color constantsç
	data[5] = level; // see level constants
	data[6] = 0x00; // empty 
	data[7] = 0xec; // EOR

	if (hid_send_feature_report(handle, data, 9) < 0) {
		printf("Unable to send a feature report.\n");
	}

}

/**
 * Commits the lights with the modes
 */
void commit(hid_device *handle, unsigned char mode) {

	//CONFIRMATION. This needs to be sent for confirmate all the led operations
	unsigned char data[8];
	data[0] = 0x01;
	data[1] = 0x02;

	data[2] = 0x41; // commit byte
	data[3] = mode; // current mode
	data[4] = 0x00;  
	data[5] = 0x00; 
	data[6] = 0x00;
	data[7] = 0xec;

	if (hid_send_feature_report(handle, data, 9) < 0) {
		printf("Unable to send a feature report.\n");
	}

}

unsigned char parseColor(char* color) {

	if (strcmp(color, VALUE_COLOR_BLACK) == 0) {
		return COLOR_BLACK;
	} else if (strcmp(color, VALUE_COLOR_RED) == 0) {
		return COLOR_RED;
	} else if (strcmp(color, VALUE_COLOR_ORANGE) == 0) {
		return COLOR_ORANGE;
	} else if (strcmp(color, VALUE_COLOR_YELLOW) == 0) {
		return COLOR_YELLOW;
	} else if (strcmp(color, VALUE_COLOR_ORANGE) == 0) {
		return COLOR_ORANGE;
	} else if (strcmp(color, VALUE_COLOR_GREEN) == 0) {
		return COLOR_GREEN;
	} else if (strcmp(color, VALUE_COLOR_SKY) == 0) {
		return COLOR_SKY;
	} else if (strcmp(color, VALUE_COLOR_BLUE) == 0) {
		return COLOR_BLUE;
	} else if (strcmp(color, VALUE_COLOR_PURPLE) == 0) {
		return COLOR_PURPLE;
	} else if (strcmp(color, VALUE_COLOR_WHITE) == 0) {
		return COLOR_WHITE;
	}

	return UCHAR_MAX;
}

void testMode()
{
  char mensaje[6];
  for (int aux = 0x00; aux < 0xFF; aux += 0x01)
  {
    mensaje[0] = aux;
    mensaje[1] = aux + 0x01;
    mensaje[2] = aux + 0x02;
    mensaje[3] = MODE_NORMAL;
    mensaje[4] = 0x01;
    mensaje[5] = '\0';
    sendMesage(mensaje);
    
    printf("Test MODE: %x\n",aux);
    sleep (2);						
  }
}

//Default Mode, wait to client
int  daemonMode()
{
    skeleton_daemon(); //Fork
    
    hid_device *handle;
    
    char mensaje[6];
  
    handle = hid_open(0x1770, 0xff00, NULL);
    if (!handle) {
      syslog (LOG_NOTICE, "Unable to open MSI Led device.");
      return EXIT_FAILURE;
    }
    syslog (LOG_NOTICE, "MSI Keyboard Led started.");
    
    //Establezco unos colores por defecto
    sendActivateArea(handle, AREA_LEFT, COLOR_RED, LEVEL_1);
    sendActivateArea(handle, AREA_MIDDLE, COLOR_GREEN, LEVEL_1);
    sendActivateArea(handle, AREA_RIGHT, COLOR_BLUE, LEVEL_1);

    commit(handle, MODE_NORMAL);
    
    while (1)
    {
      //printf("Read Mensaje\n");
      ReadMesage(mensaje);
      if(mensaje[0] != '\0')
      {
	if (mensaje[4] != 0x00)
	  mensaje[4] = (mensaje[4] - 0x01);
	switch (mensaje[0])
	{
	  case MODE_NORMAL:
	  {
	    sendActivateArea(handle, AREA_LEFT, mensaje[1], mensaje[4]);
	    sendActivateArea(handle, AREA_MIDDLE, mensaje[2], mensaje[4]);
	    sendActivateArea(handle, AREA_RIGHT, mensaje[3], mensaje[4]);
	    commit(handle, MODE_NORMAL);
	    break;
	  }
	  case MODE_WAVE:
	  {
	    //Wave Color = 3 colors
	    sendActivateArea(handle, AREA_LEFT, mensaje[1], mensaje[4]);
	    sendActivateArea(handle, AREA_MIDDLE, mensaje[2], mensaje[4]);
	    sendActivateArea(handle, AREA_RIGHT, mensaje[3], mensaje[4]);
	    commit(handle, MODE_WAVE);
	    break;
	  }
	  case MODE_GAMING:
	  {
	    sendActivateArea(handle, AREA_LEFT, mensaje[1], mensaje[4]);
	    commit(handle, MODE_GAMING);
	    break;
	  }
	  case MODE_DUAL_COLOR:
	  {
	    sendActivateArea(handle, AREA_LEFT, mensaje[1], mensaje[4]);
	    sendActivateArea(handle, AREA_MIDDLE, mensaje[2], mensaje[4]);
	    commit(handle, MODE_DUAL_COLOR);
	    break;
	  }
	  case MODE_BREATHING:
	  {
	    sendActivateArea(handle, AREA_LEFT, mensaje[1], mensaje[4]);
	    sendActivateArea(handle, AREA_MIDDLE, mensaje[2], mensaje[4]);
	    sendActivateArea(handle, AREA_RIGHT, mensaje[3], mensaje[4]);
	    commit(handle, MODE_BREATHING);
	    break;
	  }
	  
	  default:
	  {
	    syslog (LOG_NOTICE, "MSI Keyboard Led modde not valid.");
	  }
	}
      }
      else
      {
	if(mensaje[0] != 0xff)
	{
	  break;
	}
      }
      sleep (1);
    }

    syslog (LOG_NOTICE, "MSI Keyboard Led terminated.");
    closelog();

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
	
	unsigned char arguments[kSize];
	char mensaje[6];

#ifdef WIN32
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#endif

	memset(&arguments, UCHAR_MAX, kSize);

	if (argc == 2 && (strcmp(argv[1], PARAM_HELP_SHORT) == 0 || strcmp(argv[1], PARAM_HELP) == 0)) {
		printf("%s", usage);
		return 1;
	} else if (argc == 2 && (strcmp(argv[1], PARAM_VERS_SHORT) == 0 || strcmp(argv[1], PARAM_VERS) == 0)) {

		printf("%s", version);
		return 1;
	} else if (argc < 3) {
		//printf("DAEMON MODE.\n");
		return daemonMode();
		//return 1;
	} else {

		// Get arguments for program
		for (int x = 1; x < argc; x++) {

			// The params needs to start with "-"
			if (argv[x][0] == '-') {

				if (strcmp(argv[x], PARAM_MODE) == 0) {

					if (strcmp(argv[x + 1], VALUE_MODE_NORMAL) == 0) {

						arguments[kMode] = MODE_NORMAL;

					} else if (strcmp(argv[x + 1], VALUE_MODE_GAMING) == 0) {

						arguments[kMode] = MODE_GAMING;

					} else if (strcmp(argv[x + 1], VALUE_MODE_BREATHING) == 0) {

						arguments[kMode] = MODE_BREATHING;

					} else if (strcmp(argv[x + 1], VALUE_MODE_DUALCOLOR) == 0) {

						arguments[kMode] = MODE_DUAL_COLOR;

					} else if (strcmp(argv[x + 1], VALUE_MODE_WAVE) == 0) {

						arguments[kMode] = MODE_WAVE;

					} 

				} else if (strcmp(argv[x], PARAM_LEVEL) == 0) {

					arguments[kLevel] = (unsigned char)argv[x + 1][0];
				
				} else if (strcmp(argv[x], PARAM_COLOR1) == 0) {

					arguments[kColor1] = parseColor(argv[x + 1]);
				
				} else if (strcmp(argv[x], PARAM_COLOR2) == 0) {

					arguments[kColor2] = parseColor(argv[x + 1]);
				
				} else if (strcmp(argv[x], PARAM_COLOR3) == 0) {

					arguments[kColor3] = parseColor(argv[x + 1]);
				
				}

			}

		}
	}

	// Check required params
	if (arguments[kMode] == UCHAR_MAX) {
		printf("No mode specified. (-mode). Use --help for more information\n\n");
		return 1;
	}

	if (arguments[kColor1] == UCHAR_MAX && arguments[kMode] != MODE_WAVE && arguments[kMode] != MODE_BREATHING) {
		printf("No color specified. (-color1). Use --help for more information\n\n");
		return 1;
	}	

	if (arguments[kLevel] == UCHAR_MAX) {
		printf("No intensity level specified. (-level). Use --help for more information\n\n");
		return 1;
	}	

	// Check Modes
	if (arguments[kMode] == MODE_NORMAL) {

		//Gaming mode = full keyboard illumination 
		if (arguments[kColor3] == UCHAR_MAX && arguments[kColor2] == UCHAR_MAX) {
		  mensaje[0] = arguments[kColor1];
		  mensaje[1] = arguments[kColor1];
		  mensaje[2] = arguments[kColor1];
		  mensaje[3] = MODE_NORMAL;
		  mensaje[4] = arguments[kLevel] + 0x01;
		  mensaje[5] = '\0';

		} else {
		  mensaje[0] = arguments[kColor1];
		  mensaje[1] = arguments[kColor2];
		  mensaje[2] = arguments[kColor3];
		  mensaje[3] = MODE_NORMAL;
		  mensaje[4] = arguments[kLevel] + 0x01;
		  mensaje[5] = '\0';
		}
		sendMesage(mensaje);

	} else if (arguments[kMode] == MODE_GAMING) {

		//Gaming mode = only left area on 1 color with a intensity level
		mensaje[0] = arguments[kColor1];
		mensaje[1] = 0x01;
		mensaje[2] = 0x01;
		mensaje[3] = MODE_GAMING;
		mensaje[4] = arguments[kLevel] + 0x01;
		mensaje[5] = '\0';
		sendMesage(mensaje);

	} else if (arguments[kMode] == MODE_DUAL_COLOR) {

		//Dual color = two colors
		mensaje[0] = arguments[kColor1];
		mensaje[1] = arguments[kColor2];
		mensaje[2] = 0x01;
		mensaje[3] = MODE_DUAL_COLOR;
		mensaje[4] = arguments[kLevel] + 0x01;
		mensaje[5] = '\0';
		sendMesage(mensaje);

	} else if (arguments[kMode] == MODE_WAVE) {

		//Wave Color = 3 colors
		mensaje[0] = arguments[kColor1];
		mensaje[1] = arguments[kColor2];
		mensaje[2] = arguments[kColor3];
		mensaje[3] = MODE_WAVE;
		mensaje[4] = arguments[kLevel] + 0x01;
		mensaje[5] = '\0';
		sendMesage(mensaje);

	} else if (arguments[kMode] == MODE_BREATHING) {

		//??
		//Wave Color = 3 colors
		mensaje[0] = arguments[kColor1];
		mensaje[1] = arguments[kColor2];
		mensaje[2] = arguments[kColor3];
		mensaje[3] = MODE_BREATHING;
		mensaje[4] = arguments[kLevel] + 0x01;
		mensaje[5] = '\0';
		sendMesage(mensaje);

	}

	return 0;
}