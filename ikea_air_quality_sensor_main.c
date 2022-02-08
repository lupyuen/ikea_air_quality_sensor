/****************************************************************************
 * apps/examples/ikea_air_quality_sensor/ikea_air_quality_sensor_main.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <fcntl.h>

static bool frame_is_valid(void);
static void process_frame(void);

//  Header for response frame
static const uint8_t PM1006_RESPONSE_HEADER[] = { 0x16, 0x11, 0x0B };

//  Current data in the response frame (20 bytes)
static uint8_t frame[20];

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * main
 ****************************************************************************/

//  Read and process the Sensor Data from IKEA Air Quality Sensor
int main(int argc, FAR char *argv[]) {

    //  Open the UART port
    int fd = open("/dev/ttyS1", O_RDONLY);
    if (fd < 0) { printf("Unable to open file /dev/ttyS1\n"); return 1; }

    //  Forever process bytes from the UART port
    for (;;) {
        //  Read a byte from the UART port
        char ch;
        read(fd, &ch, 1);
        printf("%02x  ", ch); ////

        //  Append to response frame after shifting the bytes.
        //  We always append bytes to the frame (instead of replacing bytes)
        //  because UART is unreliable and bytes may be dropped.
        for (int i = 0; i < sizeof(frame) - 1; i++) {
            frame[i] = frame[i + 1];
        }
        frame[sizeof(frame) - 1] = ch;

        //  If frame is complete and valid...
        if (frame_is_valid()) {
            //  Process the frame
            process_frame();
        }   
    }

    //  Never returns
    return 0;
}

//  Return true if we have received a complete and valid response frame
static bool frame_is_valid(void) {
    //  Check the header at frame[0..2]
    if (memcmp(frame, PM1006_RESPONSE_HEADER, sizeof(PM1006_RESPONSE_HEADER)) != 0) {
        //  Header not found
        return false;
    }

    //  Compute sum of all bytes in the frame
    uint8_t sum = 0;
    for (int i = 0; i < sizeof(frame); i++) {
        sum += frame[i];
    }

    //  All bytes must add to 0 (because of checksum at the last byte)
    if (sum != 0) {
        //  Invalid checksum
        printf("PM1006 checksum is wrong: %02x, expected zero\n", sum);
        return false;
    }

    //  We have received a complete and valid response frame
    return true;
}

//  Process the sensor data in the response frame
static void process_frame(void) {
    //  frame[3..4] is unused
    //  frame[5..6] is our PM2.5 reading
    //  In the datasheet, index 3..6 is called DF1-DF4
    //  http://www.jdscompany.co.kr/download.asp?gubun=07&filename=PM1006_LED_PARTICLE_SENSOR_MODULE_SPECIFICATIONS.pdf
    const int pm_2_5_concentration = frame[5] * 256 + frame[6];
    printf("Got PM2.5 Concentration: %d µg/m³\n", pm_2_5_concentration);

    //  TODO: Transmit the sensor data
}
