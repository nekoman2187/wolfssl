/* Copyright (c) 2013, Philipp Tölke
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#include <src/ff.h>
#include <string.h>
#include "vfs.h"

/* dirent that will be given to callers;
 * note: both APIs assume that only one dirent ever exists
 */
vfs_dirent_t dir_ent;

FIL guard_for_the_whole_fs;

int32_t vfs_read (void* buffer, int32_t dummy, int32_t len, vfs_file_t* file) {
  uint32_t bytesread;
  FRESULT r = f_read(file, buffer, len, &bytesread);

  if (r != FR_OK) return 0;
  return bytesread;
}

vfs_dirent_t* vfs_readdir(vfs_dir_t* dir) {
  FILINFO fi;
  FRESULT r = f_readdir(dir, &fi);
  if (r != FR_OK) return NULL;
  if (fi.fname[0] == 0) return NULL;
  memcpy(dir_ent.name, fi.fname, strlen(fi.fname)+1);
  return &dir_ent;
}

int32_t vfs_stat(vfs_t* vfs, const int8_t* filename, vfs_stat_t* st) {
  FILINFO f;
  if (FR_OK != f_stat(filename, &f)) {
    return 1;
  }
  st->st_size = f.fsize;
  st->st_mode = f.fattrib;
  st->st_mtime.date = f.fdate;
  st->st_mtime.time = f.ftime;
  return 0;
}

void vfs_close(vfs_t* vfs) {
  if ((vfs != &guard_for_the_whole_fs) || (vfs == NULL)) {
    /* Close a file */
    f_close(vfs);
  }
}

int32_t vfs_write (void* buffer, int32_t dummy, int32_t len, vfs_file_t* file) {
  uint32_t byteswritten;
  FRESULT r = f_write(file, buffer, len, &byteswritten);
  if (r != FR_OK) return 0;
  return byteswritten;
}

vfs_t* vfs_openfs() {
  return &guard_for_the_whole_fs;
}

vfs_file_t* vfs_open(vfs_t* vfs, const int8_t* filename, const int8_t* mode) {
  vfs_file_t *f = vfs;
  BYTE flags = 0;
  while (*mode != '\0') {
    if (*mode == 'r') flags |= FA_READ;
    if (*mode == 'w') flags |= FA_WRITE | FA_CREATE_ALWAYS;
    mode++;
  }
  
  FRESULT r = f_open(f, filename, flags);
  if (FR_OK != r) {
    return NULL;
  }
  return f;
}

#ifdef FTPD_ENABLE_FF_DIR
int8_t* vfs_getcwd(vfs_t* vfs, void* path, int32_t len) {
  FRESULT r = f_getcwd(path, len);
  if (r != FR_OK) {
    return NULL;
  }
  return path;
}

vfs_dir_t* vfs_opendir(vfs_t* vfs, const int8_t* path) {
  vfs_dir_t* dir = vfs;
  FRESULT r = f_opendir(dir, path);
  if (FR_OK != r) {
    return NULL;
  }
  return dir;
}

void vfs_closedir(vfs_dir_t* dir) {
  return;
}

struct tm dummy;

struct tm* gmtime(vfs_time_t* c_t) {
  return &dummy;
}
#endif
