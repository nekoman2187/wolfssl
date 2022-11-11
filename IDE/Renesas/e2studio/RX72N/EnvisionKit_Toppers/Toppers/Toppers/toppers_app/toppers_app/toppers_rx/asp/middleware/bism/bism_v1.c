/*---------------------------------------------------------------------------------------------

   Memory map

   1byte header mode
         +-----------------------+
         | user data             |
         +-----------------------+
         | time 4 or 8 byte      |
         +-----------------------+
         | event code 2-4 byte   |
         +-----------------------+
         | event class  1-2 byte |
$000001  +-----------------------+
         | header 1 byte         |
$000000  +-----------------------+

----------------------------------------------------------------------------------------------

BISM Log format

  header format
  header[0]
  bit 7 header mode -> 1: 2 byte header mode, 0: 1 byte header mode

  //1 byte header mode
      bit 6   Timer mode -> 1: 64 bit timer mode 0: 32 bit timer mode
	  bit 5   event class length -> 0: 1byte, 1: 2byte
	  bit 4   event length -> 0: 2byte, 1: 4byte
	  bit 3   user data mode -> 1: word step and 8byte offset mode 0: byte step mode
	  bit 2:0 user data length :
	              when bit 3 is 1;
				     user data length is (bit[2:0] * 2 + 8) bite
				  when bit 3 is 0:
				     user data length is (bit[2:0]) byte

  //2 byte heade mode
      TBD

----------------------------------------------------------------------------------------------
*/


//set event function
//result
//  return value:
//    ERROR_CLASS_FORMAT   : event class(arg 2) is illegal format
//    ERROR_END_OF_ELEMENT : end of element is not detect
//
//argument
//  arg 1: event object
//  arg 2: event class - type uint32_t
//           bit[7:0] : event class header
//           bit[15:8] : event class value 0
//           bit[23:16]   : event class value 1 (option)
//
//  arg 3-6 : event element(list of uint16_t)
//            bit[7:0] : event element header
//            bit[15:8] : event element value
//
// Formet of header
//   evnet class header
//          bit[7] : event class flag. always 1.
//          bit[6] : event class length. 1: 2byte, 0: 1byte.
//          bit[5:3] : maximum number of event element
//
//   event element header
//          bit[7] : event class flag. always 0.
//          bit[6] : end of element flag. set 1 when the element is last.
//          bit[5:4] : reserved

#include <stdarg.h>
#include <kernel.h>
#include <kernel_cfg.h>
#include <middleware/bism/bism_io.h>
#include <middleware/bism/bism_format.h>
#include <middleware/bism/bism.h>
#include <driver/rx_gcc/EPTPC.h>


//event class header defefine
#define IS_EVENT_CLASS 0x80
#define IS_2BYTE_CLASS 0x40
#define MAX_NUM_ELMASK 0x38

#define MAX_NUM_SHIFT  3
#define HEADER_BIT_SIZE 8

//event element header define
#define IS_LAST_ELEMENT 0x40

#define BISM_SET_OK 1
#define ERROR_CLASS_FORMAT -1
#define ERROR_END_OF_ELEMENT -2
#define ERROR_NOT_INITED -3

PTPCLK ptp_time;

#define BISM_IDLE 0
#define BISM_LOGGING 1

uint8_t bism_state = BISM_IDLE;

void bism_init(uint8_t* log_file){
  bism_io_init(log_file);
  bism_state = BISM_LOGGING;
}

void bism_close(){
  bism_state = BISM_IDLE;
  bism_io_close();
}

int8_t bism_set_event(bism_log *blog, uint32_t bevent_cls, ...){
  va_list list;
  uint8_t i, max_element, len_element, len_log, det_last, log_header;
  uint8_t* log_p;
  uint16_t element;

  if(bism_state == BISM_IDLE)
    return ERROR_NOT_INITED;
  
  va_start(list, bevent_cls);

  log_header = T1_TIMER_LEN_MASK; //Timer len is 64bit.
  if((bevent_cls & IS_EVENT_CLASS) == 0)
    return ERROR_CLASS_FORMAT;

  len_log = 1;
  max_element = (bevent_cls  & MAX_NUM_ELMASK) >> MAX_NUM_SHIFT;
  //set event class
  log_p = blog->dat + 1;//skip log header
  *((uint16_t*)(log_p)) = 0;

  if(bevent_cls & IS_2BYTE_CLASS){
    len_log += 2;
    *((uint16_t*)log_p) = (uint16_t)(bevent_cls >> HEADER_BIT_SIZE);
    log_header |= T1_EVENT_CLASS_FLG; //class len is 2byte
  }else{
    len_log++;
    *(log_p) = (uint8_t)(bevent_cls >> HEADER_BIT_SIZE);
  }
  blog->len = len_log;
  //set event element
  log_p = blog->dat + len_log;
  det_last = len_log = 0;
  *((uint32_t*)log_p) = 0;

  //  va_start(list, bevent);
  for(i=0; i<max_element; i++){
    element = va_arg(list, int);
    *log_p = (uint8_t)(element >> HEADER_BIT_SIZE);

    len_log++, log_p++;
    if(element & IS_LAST_ELEMENT){
      det_last = 1;
      break;
    }
  }
  va_end(list);

  if(det_last == 0)
    return ERROR_END_OF_ELEMENT;


  if(len_log > 2 ){
    log_header |= T1_EVENT_LEN_FLG;
    blog->len += 4;
  }else
    blog->len += 2;

  log_p = blog->dat + blog->len;
  if(bism_get_time(&ptp_time)==E_OK){
    *((uint32_t*)log_p) = ptp_time.sec_l;
    *((uint32_t*)(log_p+4)) = ptp_time.nano_sec;
    blog->len += 8;
  }
  *blog->dat = log_header;
  return BISM_SET_OK;

}


void bism_write(bism_log *blog){
  uint32_t w_len, w_count;
  if(bism_state == BISM_IDLE)
    return 0;
  
  wai_sem(BISM_WRITE_FUNC_SEM);
  w_len = 0;
  w_count = blog->len;

  while(w_len != w_count)
    w_len += bism_buff_write(blog->dat+w_len, w_count-w_len);
  sig_sem(BISM_WRITE_FUNC_SEM);
}

void bism_push(){
  if(bism_state == BISM_IDLE)
    return 0;
  bism_push_block();
}
