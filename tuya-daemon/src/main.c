#include <assert.h>
#include <stdlib.h>
#include <cJSON.h>
#include "tuya_log.h"
#include "tuya_error_code.h"
#include "system_interface.h"
#include "argp_handler.h"
#include "mqtt_client_interface.h"
#include "tuya_handler.h"
#include <signal.h>
#include <syslog.h>
#include <unistd.h>
#include "file_handler.h"
#include "message_handler.h"
#include <libubox/blobmsg_json.h>
#include <libubus.h>
#include <stdio.h>
#include "ubus_handler.h"
#include "daemon.h"

void signal_handler(int signum);
int running = 1;
int main(int argc, char **argv)
{
	tuya_mqtt_context_t client_instance;
	tuya_mqtt_context_t *client = &client_instance;
	struct device_details device_details;
	device_details.device_id     = NULL;
	device_details.device_secret = NULL;
	device_details.product_id    = NULL;
	device_details.daemon    = NULL;
	struct argp_option options[] = { { "device-id", 'i', "DEVICE-ID", 0, "Device ID" },
					 { "device-secret", 's', "DEVICE-SECRET", 0, "Device Secret" },
					 { "product-id", 'p', "PRODUCT-ID", 0, "Product ID" },
					 { "daemon", 'D', 0, OPTION_ARG_OPTIONAL,
					   "Option to run program as daemon" },
					 { 0 } };
	struct argp argp	     = { options, parse_opt, 0, 0 };
	char payload[100];
	int rt;
	int daemon_rt;
	struct ubus_context *ctx;
	uint32_t id;
	struct MemData memory;

	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, signal_handler);

	argp_parse(&argp, argc, argv, 0, 0, &device_details);
	if (device_details.daemon == 1) {
		daemon_rt = daemon_init();
		if (daemon_rt) {
			log_message(ERROR_DAEMON_START, "");
			closelog();
			exit(EXIT_FAILURE);
		}
	}
	openlog("daemon-tuya", LOG_PID, LOG_USER);

	rt = handle_connection(client, &device_details);

	if (rt != 0) {
		goto cleanup;
	}

	ctx = ubus_connect(NULL);
	if (!ctx) {
		log_message(ERROR_UBUS_CONNECTION, "");
		goto cleanup;
	}
	ubus_lookup_id(ctx, "system", &id);

	while (running) {
		ubus_invoke(ctx, id, "info", NULL, board_cb, &memory, 1000);
		snprintf(payload, sizeof(payload), "{\"free_memory\": %d}", memory.free);
		tuyalink_thing_property_report(client, device_details.device_id, payload);
		log_message(SENDING_MEMORY, payload);
		tuya_mqtt_loop(client);
	}

cleanup:
	log_message(CLEANUP, "");
	tuya_mqtt_disconnect(client);
	tuya_mqtt_deinit(client);
	ubus_free(ctx);
	closelog();
	exit(EXIT_SUCCESS);
}

/**
 * signal_handler() - Handler for processing signals.
 * @arg1: An integer that specifies signal's number
 *
 * On called signal changes global variable to not running.
 *
 */
void signal_handler(int signum)
{
	running = 0;
}