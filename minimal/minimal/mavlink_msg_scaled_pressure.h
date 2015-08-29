// MESSAGE SCALED_PRESSURE PACKING

#ifndef _MAVLINK_MSG_SCALED_PRESSURE_H_
#define _MAVLINK_MSG_SCALED_PRESSURE_H_

#include "../mavlink_helpers.h" 

#define MAVLINK_MSG_ID_SCALED_PRESSURE 29

typedef struct __mavlink_scaled_pressure_t
{
 uint32_t time_boot_ms; /*< Timestamp (milliseconds since system boot)*/
 float press_abs; /*< Absolute pressure (hectopascal)*/
 float press_diff; /*< Differential pressure 1 (hectopascal)*/
 int16_t temperature; /*< Temperature measurement (0.01 degrees celsius)*/
} mavlink_scaled_pressure_t;

#define MAVLINK_MSG_ID_SCALED_PRESSURE_LEN 14
#define MAVLINK_MSG_ID_29_LEN 14

#define MAVLINK_MSG_ID_SCALED_PRESSURE_CRC 115
#define MAVLINK_MSG_ID_29_CRC 115



#define MAVLINK_MESSAGE_INFO_SCALED_PRESSURE { \
	"SCALED_PRESSURE", \
	4, \
	{  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_scaled_pressure_t, time_boot_ms) }, \
         { "press_abs", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_scaled_pressure_t, press_abs) }, \
         { "press_diff", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_scaled_pressure_t, press_diff) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_scaled_pressure_t, temperature) }, \
         } \
}


/**
 * @brief Pack a scaled_pressure message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms Timestamp (milliseconds since system boot)
 * @param press_abs Absolute pressure (hectopascal)
 * @param press_diff Differential pressure 1 (hectopascal)
 * @param temperature Temperature measurement (0.01 degrees celsius)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
uint16_t mavlink_msg_scaled_pressure_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint32_t time_boot_ms, float press_abs, float press_diff, int16_t temperature);
uint16_t mavlink_msg_scaled_pressure_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint32_t time_boot_ms,float press_abs,float press_diff,int16_t temperature);
uint16_t mavlink_msg_scaled_pressure_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scaled_pressure_t* scaled_pressure);
uint16_t mavlink_msg_scaled_pressure_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scaled_pressure_t* scaled_pressure);

#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

void mavlink_msg_scaled_pressure_send(mavlink_channel_t chan, uint32_t time_boot_ms, float press_abs, float press_diff, int16_t temperature);

#if MAVLINK_MSG_ID_SCALED_PRESSURE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
void mavlink_msg_scaled_pressure_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, float press_abs, float press_diff, int16_t temperature);
#endif

#endif

// MESSAGE SCALED_PRESSURE UNPACKING


/**
 * @brief Get field time_boot_ms from scaled_pressure message
 *
 * @return Timestamp (milliseconds since system boot)
 */
uint32_t mavlink_msg_scaled_pressure_get_time_boot_ms(const mavlink_message_t* msg);
float mavlink_msg_scaled_pressure_get_press_abs(const mavlink_message_t* msg);
float mavlink_msg_scaled_pressure_get_press_diff(const mavlink_message_t* msg);
int16_t mavlink_msg_scaled_pressure_get_temperature(const mavlink_message_t* msg);
void mavlink_msg_scaled_pressure_decode(const mavlink_message_t* msg, mavlink_scaled_pressure_t* scaled_pressure);

#endif /*_xx_h_*/
