#include "argp_handler.h"
#include "tuya_handler.h"

/**
 * parse_opt() - Parse given options
 *
 * Only accept '-s' '-i' '-p' options
 *
 * Return: Error code on failure, otherwise 0.
 */
error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct device_details *device_details = state->input;
	switch (key) {
	case 'D':
		device_details->daemon = 1;
		break;
	case 'i':
		device_details->device_id = arg;
		break;
	case 's':
		device_details->device_secret = arg;
		break;
	case 'p':
		device_details->product_id = arg;
		break;

	case ARGP_KEY_ARG:
		argp_failure(state, 1, 0, "required -i, -s and -p options. See --help for more information");
		return ARGP_ERR_UNKNOWN;
	case ARGP_KEY_END:
		if (device_details->device_id == NULL || device_details->device_secret == NULL ||
		    device_details->product_id == NULL) {
			argp_failure(state, 1, 0,
				     "required -i, -s and -p options. See --help for more information");
			return ARGP_ERR_UNKNOWN;
		}
	default:
		return ARGP_ERR_UNKNOWN;
	}

	return 0;
}