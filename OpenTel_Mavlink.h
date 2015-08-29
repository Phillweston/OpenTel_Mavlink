
#ifndef __OPENTEL_MAVLINK_H
#define __OPENTEL_MAVLINK_H


#include "./minimal/minimal/minimal.h"
#include "define.h"

void mavlink_send_message(mavlink_channel_t chan, enum ap_message id, uint16_t packet_drops);
void update(void);

#endif /*__OPENTEL_MAVLINK_H*/   


