/* Copyright (c) 2013, Philipp T�lke
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

#ifndef INCLUDE_VFS_H
#define INCLUDE_VFS_H

#include <kernel.h>
#include <middleware/include/ff.h>

#define vfs_load_plugin(x)

typedef struct {
	int16_t date;
	int16_t time;
} vfs_time_t;
typedef DIR vfs_dir_t;
typedef FIL vfs_file_t;
typedef struct {
	int32_t st_size;
	int8_t st_mode;
	vfs_time_t st_mtime;
} vfs_stat_t;
typedef struct {
	int8_t name[13];
} vfs_dirent_t;
typedef FIL vfs_t;

struct tm {
  int32_t tm_year;
  int32_t tm_mon;
  int32_t tm_mday;
  int32_t tm_hour;
  int32_t tm_min;
};

#define time(x)
#define vfs_eof f_eof
#define VFS_ISDIR(st_mode) ((st_mode) & AM_DIR)
#define VFS_ISREG(st_mode) !((st_mode) & AM_DIR)
#define vfs_rename(vfs, from, to) f_rename(from, to)
#define VFS_IRWXU 0
#define VFS_IRWXG 0
#define VFS_IRWXO 0
#define vfs_mkdir(vfs, name, mode) f_mkdir(name)
#define vfs_rmdir(vfs, name) f_unlink(name)
#define vfs_remove(vfs, name) f_unlink(name)
#define vfs_chdir(vfs, dir) f_chdir(dir)
int8_t* vfs_getcwd(vfs_t* vfs, void*, int32_t dummy);
int32_t vfs_read (void* buffer, int32_t dummy, int32_t len, vfs_file_t* file);
int32_t vfs_write (void* buffer, int32_t dummy, int32_t len, vfs_file_t* file);
vfs_dirent_t* vfs_readdir(vfs_dir_t* dir);
vfs_file_t* vfs_open(vfs_t* vfs, const int8_t* filename, const int8_t* mode);
vfs_t* vfs_openfs();
void vfs_close(vfs_t* vfs);
int32_t vfs_stat(vfs_t* vfs, const int8_t* filename, vfs_stat_t* st);
void vfs_closedir(vfs_dir_t* dir);
vfs_dir_t* vfs_opendir(vfs_t* vfs, const int8_t* path);
struct tm* gmtime(vfs_time_t *c_t);

#endif /* INCLUDE_VFS_H */
