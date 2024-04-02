#include "message_handler.h"
#include <stdio.h>
#include <syslog.h>

/**
 * log_message() - Log a message.
 * @arg1: Integer which provides a number that maps to specific message
 *
 * Logs a message to a file, according to provided message code.
 *
 */
void log_message(int message_code, char *additional_msg)
{
	switch (message_code) {
	case ERROR_FILE_OPEN:
		syslog(LOG_ERR, "[ERROR] FILE COULDN'T BE OPENED");
		break;
	case ERROR_FILE_CLOSE:
		syslog(LOG_ERR, "[ERROR] FILE COULDN'T BE CLOSED");
		break;
	case SENDING_MEMORY:
		syslog(LOG_INFO, "[INFO] SENDING DATA TO TUYA %s", additional_msg);
		break;
	case ERROR_TUYA_INIT:
		syslog(LOG_ERR, "[ERROR] TUYA INIT FAILURE");
		break;
	case ERROR_TUYA_CONNECTION:
		syslog(LOG_ERR, "[ERROR] TUYA CONNECTION FAILURE");
		break;
	case ERROR_UBUS_CONNECTION:
		syslog(LOG_ERR, "[ERROR] UBUS CONNECTION FAILURE");
		break;
	case GOT_MESSAGE:
		syslog(LOG_INFO, "[INFO] GOT MESSAGE %s", additional_msg);
		break;
	case MODIFIED_BRIGHTNESS_FILE:
		syslog(LOG_INFO, "[INFO] BRIGHTNESS FILE WAS MODIFIED");
		break;
	case ERROR_JSON_PARSING:
		syslog(LOG_INFO, "[ERROR] INCOMING JSON PAYLOAD COULDN'T BE PARSED %s", additional_msg);
		break;
	case ERROR_DAEMON_START:
		syslog(LOG_INFO, "[ERROR] DAEMON COULDN'T BE STARTED");
		break;
	case TUYA_CONNECTED:
		syslog(LOG_INFO, "[INFO] CONNECTED");
		break;
	case TUYA_DISCONNECTED:
		syslog(LOG_INFO, "[INFO] DISCONNECTED");
		break;
	case EXITING:
		syslog(LOG_INFO, "[INFO] Exiting");
		break;
	case NO_MEMORY_RECEIVED:
		syslog(LOG_INFO, "[INFO] NO MEMORY DATA RECEIVED");
		break;
	case CLEANUP:
		syslog(LOG_INFO, "[INFO] CLEANING UP");
		break;
	default:
		break;
	}
}