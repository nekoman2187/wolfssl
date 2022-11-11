/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2016 Hisashi Hata
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <kernel.h>
#include <shell_command.h>
#include <middleware/bootload/boot_elf.h>

int8_t cmd_boot(uint8_t argc, int8_t *argv[])
{
  shell_print("boot start.\r\n");
  shell_close_connection();
  tslp_tsk(1000);
  if(argc == 0)
    boot_elf("asp");
  else
    boot_elf(argv[0]);

  return ECLOSE;
}

shell_cmd_t usr_cmd[] = {
  {"boot", 1, cmd_boot, "boot file_name: boot elf_image from sd card. file_name is elf_image name.\r\n"},
  {NULL, 0, NULL}
};
