#include "tuya_cacert.h"
#include <syslog.h>
#include <tuya_error_code.h>
#include "tuya_handler.h"
#include "json_handler.h"
#include "file_handler.h"
#include "message_handler.h"

/**
 * on_connected() - Tuya's event callback.
 * @arg1: The handle to device management
 * @arg2: User's data
 *
 * On connection, logs the event.
 *
 */
void on_connected(tuya_mqtt_context_t *context, void *user_data)
{
	syslog(LOG_INFO, "[INFO] CONNECTED");
}

/**
 * on_disconnect() - Tuya's event callback.
 * @arg1: The handle to device management
 * @arg2: User's data
 *
 * On disconnection, logs the event.
 *
 */
void on_disconnect(tuya_mqtt_context_t *context, void *user_data)
{
	syslog(LOG_INFO, "[INFO] DISCONNECTED");
}

/**
 * on_messages() - Tuya's event callback.
 * @arg1: The handle to device management
 * @arg2: User's data
 * @arg3: Received message
 *
 * On receiving message, checks if message type is correct, checks if received data is valid and switches LED.
 *
 */
void on_messages(tuya_mqtt_context_t *context, void *user_data, const tuyalink_message_t *msg)
{
	log_message(GOT_MESSAGE, msg->data_string);
	tuyalink_thing_type_t message_type = msg->type;

	switch (message_type) {
	case THING_TYPE_PROPERTY_SET:
		if (msg->data_string != NULL) {
			int rt = parse_property_json(msg->data_string);
			if (rt == 1 || rt == 0) {
				int toggle_rt = toggle_led(rt);
				if (toggle_rt < 0) {
					log_message(toggle_rt, "");
				} else
					log_message(MODIFIED_BRIGHTNESS_FILE, "");
			}
		}
		break;
	default:
		break;
	}
}

/**
 * handle_connection() - Handle the process of connecting to tuya's API.
 * @arg1: The handle to device management
 * @arg2: Given devices' configuration
 *
 * Return: Error code on failure, otherwise 0.
 *
 */
int handle_connection(tuya_mqtt_context_t *client, struct device_details *device_details)
{
	int rt = 0;
	rt     = tuya_mqtt_init(client,
				&(const tuya_mqtt_config_t){ .host	    = "m2.tuyacn.com",
							     .port	    = 8883,
							     .cacert	    = (unsigned char *)tuya_cacert_pem,
							     .cacert_len    = sizeof(tuya_cacert_pem),
							     .device_id	    = device_details->device_id,
							     .device_secret = device_details->device_secret,
							     .keepalive	    = 60,
							     .timeout_ms    = 2000,
							     .on_connected  = on_connected,
							     .on_disconnect = on_disconnect,
							     .on_messages   = on_messages });

	if (rt != OPRT_OK) {
		log_message(ERROR_TUYA_INIT, "");
		return rt;
	}

	rt = tuya_mqtt_connect(client);

	if (rt != OPRT_OK) {
		log_message(ERROR_TUYA_CONNECTION, "");
		return rt;
	}
	return rt;
}