/*
 * Copyright 2016 Hisashi Hata.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the authors nor the names of the contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * ftpd_arg_dec.c - This file is part of the FTP daemon for tinet
 *
 */

#include "ftpd_arg_dec.h"
   
#define DEC_OK 3
#define DEC_EMP 1
#define DEC_ERROR -1

static int32_t skip_space(int8_t** arg_adr){
  const int8_t end_alp[3] = {'\n', '\r', '\0'};
  const int8_t endc_num = 3;
  int8_t *arg_str, i;

  arg_str = *arg_adr;
  while((*arg_str == ' ') || (*arg_str == ',')) arg_str++;
  for(i=0;i<endc_num;i++){
    if(*arg_str == end_alp[i]){
      *arg_adr = arg_str;
      return DEC_EMP;
    }
  }
  *arg_adr = arg_str;    
  return 0;
}

static int32_t ftpd_dec_num(int8_t** arg_adr, uint32_t *dec_val){
  uint32_t ret;
  uint32_t dec;
  int8_t *arg_str;
  
  dec = 0;
  arg_str = *arg_adr;

  if(skip_space(&arg_str) == DEC_EMP){
    *arg_adr = arg_str;
    return DEC_EMP;
  }

  ret = DEC_ERROR;
  while((*arg_str >= '0') && (*arg_str <= '9')){
    ret = DEC_OK;
    dec = dec*10+(*arg_str-'0');
    arg_str++;
  }
  *dec_val = dec;
  *arg_adr = arg_str;
  
  return ret;
}

int32_t ftpd_num_arg_dec(const int8_t* arg_str, uint32_t* dec_result, uint8_t num_arg){
  int8_t **arg_adr;
  int8_t i;
  
  arg_adr = &arg_str;
  for(i=0;i<num_arg;i++){
    if(ftpd_dec_num(arg_adr, dec_result)!=DEC_OK)
      return DEC_ERROR;
    dec_result++;
  }
  return DEC_OK;
}
