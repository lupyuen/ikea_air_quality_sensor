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
#include <wchar.h>
#include <syslog.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * main
 ****************************************************************************/

int main(int argc, FAR char *argv[])
{
  int fd;
  int cnt;
  char ch;

  /* Open the serial port */

  fd = open("/dev/ttyS1", O_RDONLY);
  if (fd < 0)
    {
      printf("Unable to open file /dev/ttyS1\n");
    }

  /* Run forever */

  for (; ; )
    {
      /* Read until we complete a line */

      cnt = 0;
      do
        {
          read(fd, &ch, 1);
          printf("%02x  ", ch); ////
        }
      while (ch != '\r' && ch != '\n');
    }

  return 0;
}
