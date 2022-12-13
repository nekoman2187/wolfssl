/*------------------------------------------------------------------------*/
/* FRK-RX62N: MMCv3/SDv1/SDv2 (SPI mode) Control Module                   */
/*------------------------------------------------------------------------*/
/*
/  Copyright (C) 2014, ChaN, all right reserved.
/                2016, modified by Hisashi Hata
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include <kernel.h>
#include <sil.h>
#include <driver/rx_gcc/mmc_rspi.h>
#include <driver/rx_gcc/mmc_gpio.h>

#define	WP			0 						/* Write protect switch (Protected:True, Enabled:False) */

#define SCLK_FAST	12000000UL	/* SCLK frequency (R/W) */
#define	SCLK_SLOW	400000UL	/* SCLK frequency (Init) */

static inline uint32_t LDDW( uint32_t data )
{
  __asm__("revl	%1, %0":"=r"(data):"r"(data));
  return data;
}

#ifdef RSPI_MMC_DTCA_TRANS
#include <driver/rx_gcc/DTCa.h>

/*
 * define dtca buffer
 */
uint32_t rspi_mmc_dtca_buffer[128]; //512byte

#endif

/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

/* MMC/SD command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */

//time out flag
#define DATA_TRANS_TIME 0x1
#define WAIT_TIME 0x2

//time out flag management function
inline void clear_timeout_timer(mmc_rspi_stat_t *mmc_stat, uint8_t flg_bit){
  mmc_stat->tout_flg &= ~flg_bit;
}

inline uint8_t is_timeout(mmc_rspi_stat_t *mmc_stat, uint8_t flg_bit){
  return mmc_stat->tout_flg & flg_bit;
}

void fast_clk_mode(rspi_dstat* rspi_stat){
    rspi_disable(rspi_stat);
    rspi_chg_bit_rate(rspi_stat, F_PCLKB/2/SCLK_FAST-1);
    rspi_enable(rspi_stat);
}

/*-----------------------------------------------------------------------*/
/* Control SPI module                                                    */
/*-----------------------------------------------------------------------*/
/* Only these five functions are platform dependent. Any other functions */
/* are portable to different system.                                     */

/*---------------------------------*/
/* Enable SPI and MMC/SDC controls */
/*---------------------------------*/
static
void power_on (mmc_rspi_stat_t* mmc_stat)
{

  rspi_param_t rspi_param;
  rspi_dstat* rspi_stat;

  rspi_stat = (rspi_dstat*)GET_DEV_STAT(mmc_stat->mmc_drv_id);
  
  /* Initialize RSPI module */
  rspi_param.spcr = (SPCR_SPE | SPCR_MSTR | SPCR_SPMS); //enable rspi, set master mode, s clock synchronized mode
  rspi_param.sslp = 0;
  rspi_param.sppcr = 0;
  rspi_param.spscr = 0;
  rspi_param.bit_rate = SCLK_SLOW;
  rspi_param.spdcr = SPDCR_SPLW; //access type is long word(32 bit)
  rspi_param.spcmd0 = SPCMD_SPB_8; //8bit transfer mode
  
  rspi_init(rspi_stat, &rspi_param);
}


/*---------------------*/
/*    Disable SPI      */
/*---------------------*/
static
void power_off (mmc_rspi_stat_t* mmc_stat)	/* Disable MMC/SDC interface */
{
  rspi_disable((rspi_dstat*)GET_DEV_STAT(mmc_stat->mmc_drv_id));
  //RSPI.SPCR.BYTE = 0;		/* Stop RSPI module */
}


/*---------------------*/
/* Send/Receive a byte */
/*---------------------*/
static
uint32_t xchg_spi (
                  mmc_rspi_stat_t *mmc_stat,
                  uint32_t dat	/* Data to send */
                  )
{
  rspi_dstat *rspi_stat;

  rspi_stat = (rspi_dstat*)GET_DEV_STAT(mmc_stat->mmc_drv_id);
  return rspi_xchg_rw(rspi_stat, dat);
}


#ifdef RSPI_MMC_DTCA_TRANS
/*-------------------------------------*/
/* Send multiple bytes by dtca write */
/*-------------------------------------*/
static
void xmit_spi_multi (
                     mmc_rspi_stat_t *mmc_stat,
                     const uint8_t *buff,	/* Pointer to the data */
                     uint32_t btx			/* Number of bytes to send (multiple of 4) */
                     )
{
  const uint32_t *lp = (const uint32_t*)buff;
  uint32_t i;
  rspi_dstat *rspi_stat;

  rspi_stat = (rspi_dstat*)GET_DEV_STAT(mmc_stat->mmc_drv_id);
  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_32);	/* Set 32-bit mode */

  for(i=0; i<(btx/4); i++){
    rspi_mmc_dtca_buffer[i] = LDDW(*(lp + i));
  }

  rspi_send_by_dtca(rspi_stat, rspi_mmc_dtca_buffer, btx);

  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_8);	/* Set 8-bit mode */
}

#else
/*-------------------------------------*/
/* Send multiple bytes by single write */
/*-------------------------------------*/
static
void xmit_spi_multi (
                     mmc_rspi_stat_t *mmc_stat,
                     const uint8_t *buff,	/* Pointer to the data */
                     uint32_t btx			/* Number of bytes to send (multiple of 4) */
                     )
{
  const uint32_t *lp = (const uint32_t*)buff;
  rspi_dstat *rspi_stat;

  rspi_stat = (rspi_dstat*)GET_DEV_STAT(mmc_stat->mmc_drv_id);
  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_32);	/* Set 32-bit mode */
  
  do {
    rspi_send_w(rspi_stat, LDDW(*lp++));	/* Send four data bytes */
    while (rspi_status(rspi_stat) & SPSR_IDLNF) ;	/* Wait for end of transfer */
    rspi_rcv_w(rspi_stat);					/* Discard four received bytes */
  } while (btx -= 4);					/* Repeat until all data sent */
  
  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_8);	/* Set 8-bit mode */
}

#endif
/*------------------------*/
/* Receive multiple bytes */
/*------------------------*/
#ifdef RSPI_MMC_DTCA_TRANS
static
void rcvr_spi_multi (
                     mmc_rspi_stat_t *mmc_stat,
                     uint8_t *buff,		/* Pointer to data buffer */
                     uint32_t btr		/* Number of bytes to receive (multiple of 4) */
                     )
{
  uint32_t *lp = (uint32_t*)buff;
  uint32_t i;
  rspi_dstat *rspi_stat;

  rspi_stat = (rspi_dstat*)GET_DEV_STAT(mmc_stat->mmc_drv_id);

  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_32);	/* Set 32-bit mode */

  rspi_recieve_by_dtca(rspi_stat, lp, btr);

  for(i=0; i<(btr/4); i++){
    lp[i] = LDDW(lp[i]);
  }

  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_8);	/* Set 8-bit mode */
}

#else
static
void rcvr_spi_multi (
                     mmc_rspi_stat_t *mmc_stat,
                     uint8_t *buff,		/* Pointer to data buffer */
                     uint32_t btr		/* Number of bytes to receive (multiple of 4) */
                     )
{
  uint32_t *lp = (uint32_t*)buff;
  rspi_dstat *rspi_stat;

  rspi_stat = (rspi_dstat*)GET_DEV_STAT(mmc_stat->mmc_drv_id);

  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_32);	/* Set 32-bit mode */
  
  do {
    rspi_send_w(rspi_stat, 0xFFFFFFFF);	/* Send four 0xFFs */
    while (rspi_status(rspi_stat) & SPSR_IDLNF);/* Wait for end of transfer */
    *lp++ = LDDW(rspi_rcv_w(rspi_stat));	/* Store four received bytes */
  } while (btr -= 4);					/* Repeat until all data received */
  
  rspi_chg_dwidth(rspi_stat, 0, SPCMD_SPB_8);	/* Set 8-bit mode */
}
#endif



/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
int wait_ready (	/* 1:Ready, 0:Timeout */
                mmc_rspi_stat_t *mmc_stat,
                uint32_t wt			/* Timeout [ms] */
                    )
{
  clear_timeout_timer(mmc_stat, WAIT_TIME);
  sta_alm(mmc_stat-> tout_task_id_1, wt);
  
  do {
    if (xchg_spi(mmc_stat, 0xFF) == 0xFF){
    	/* Card goes ready */
    	stp_alm(mmc_stat-> tout_task_id_1);
    	return 1;
    }
    /* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */
    //rot_rdq();
  } while (!is_timeout(mmc_stat, WAIT_TIME));    /* Wait until card goes ready or timeout */
  stp_alm(mmc_stat-> tout_task_id_1);
  
  return 0;	/* Timeout occured */
}



/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/

static
void deselect (mmc_rspi_stat_t *mmc_stat)
{
  deselect_gpio_cs(GET_DEV_STAT(mmc_stat->mmc_ins_id)); /* Set CS# high */
  xchg_spi(mmc_stat, 0xFF);	/* Dummy clock (force DO hi-z for multiple slave SPI) */
}



/*-----------------------------------------------------------------------*/
/* Select card and wait for ready                                        */
/*-----------------------------------------------------------------------*/

static
int select (mmc_rspi_stat_t* mmc_stat)	/* 1:OK, 0:Timeout */
{
    
  select_gpio_cs(GET_DEV_STAT(mmc_stat->mmc_ins_id)); //set cs# low
  xchg_spi(mmc_stat, 0xFF);	/* Dummy clock (force DO enabled) */
  
  if (wait_ready(mmc_stat, 1000)) return 1;	/* Wait for card ready */
  
  deselect(mmc_stat);
  return 0;	/* Failed to select the card due to timeout */
}



/*-----------------------------------------------------------------------*/
/* Receive a data packet from the MMC                                    */
/*-----------------------------------------------------------------------*/

static
int rcvr_datablock (	/* 1:OK, 0:Error */
                    mmc_rspi_stat_t *mmc_stat,
                    uint8_t *buff,			/* Data buffer */
                    uint32_t btr			/* Data block length (byte) */
                        )
{
  uint8_t token;

  clear_timeout_timer(mmc_stat, DATA_TRANS_TIME);
  sta_alm(mmc_stat-> tout_task_id_0, 1000);
  do {							/* Wait for DataStart token in timeout of 200ms */
    token = xchg_spi(mmc_stat, 0xFF);
    /* This loop will take a time. Insert rot_rdq() here for multitask envilonment. */
  } while ((token == 0xFF) && (!is_timeout(mmc_stat, DATA_TRANS_TIME)));
  stp_alm(mmc_stat-> tout_task_id_0);

  if (token != 0xFE) return 0;	/* Function fails if invalid DataStart token or timeout */
  rcvr_spi_multi(mmc_stat, buff, btr);		/* Store trailing data to the buffer */
  xchg_spi(mmc_stat, 0xFF); xchg_spi(mmc_stat, 0xFF);	/* Discard CRC */
    
  return 1;						/* Function succeeded */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to the MMC                                         */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
static
int xmit_datablock (	/* 1:OK, 0:Failed */
                    void *v_stat,
                    const uint8_t *buff,	/* Ponter to 512 byte data to be sent */
                    uint8_t token			/* Token */
)
{
	uint8_t resp;
    mmc_rspi_stat_t *mmc_stat;

	mmc_stat = (mmc_rspi_stat_t*)v_stat;

	if (!wait_ready(mmc_stat, 1000)) return 0;		/* Wait for card ready */

	xchg_spi(mmc_stat, token);					/* Send token */
	if (token != 0xFD) {				/* Send data if token is other than StopTran */
      xmit_spi_multi(mmc_stat, buff, 512);		/* Data */
      xchg_spi(mmc_stat, 0xFF); xchg_spi(mmc_stat, 0xFF);	/* Dummy CRC */
      
      resp = xchg_spi(mmc_stat, 0xFF);			/* Receive data resp */
      if ((resp & 0x1F) != 0x05){		/* Function fails if the data packet was not accepted */
        return 0;
      }
	}

	return 1;
}
#endif /* _USE_WRITE */



/*-----------------------------------------------------------------------*/
/* Send a command packet to the MMC                                      */
/*-----------------------------------------------------------------------*/

static
uint8_t send_cmd (		/* Return value: R1 resp (bit7==1:Failed to send) */
                  mmc_rspi_stat_t *mmc_stat,
                  uint8_t cmd,		/* Command index */
                  uint32_t arg		/* Argument */
                        )
{
	uint8_t n, res;

	if (cmd & 0x80) {	/* Send a CMD55 prior to ACMD<n> */
		cmd &= 0x7F;
		res = send_cmd(mmc_stat, CMD55, 0);
		if (res > 1) return res;
	}

	/* Select the card and wait for ready except to stop multiple block read */
	if (cmd != CMD12) {
		deselect(mmc_stat);
		if (!select(mmc_stat)) return 0xFF;
	}

	/* Send command packet */
	xchg_spi(mmc_stat, 0x40 | cmd);			/* Start + command index */
	xchg_spi(mmc_stat, (uint8_t)(arg >> 24));	/* Argument[31..24] */
	xchg_spi(mmc_stat, (uint8_t)(arg >> 16));	/* Argument[23..16] */
	xchg_spi(mmc_stat, (uint8_t)(arg >> 8));		/* Argument[15..8] */
	xchg_spi(mmc_stat, (uint8_t)arg);			/* Argument[7..0] */
	n = 0x01;						/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;		/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;		/* Valid CRC for CMD8(0x1AA) */
	xchg_spi(mmc_stat, n);

	/* Receive command resp */
	if (cmd == CMD12) xchg_spi(mmc_stat, 0xFF);	/* Diacard stuff byte on CMD12 */
	n = 10;							/* Wait for response (10 bytes max) */
	do
      res = xchg_spi(mmc_stat, 0xFF);
	while ((res & 0x80) && --n);

	return res;						/* Return received response */
}



/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize disk drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS rspi_disk_initialize (
	void *v_stat		/* mmc_rspi status */
)
{
	uint8_t n, cmd, ty, ocr[4];
    mmc_rspi_stat_t *mmc_stat;
    mmc_stat = (mmc_rspi_stat_t *)v_stat;
    rspi_get_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));

    if (check_ins_sw(GET_DEV_STAT(DEV_MMC_GPIO0)))    /* Card is in socket */
      mmc_stat->Stat = STA_NOINIT;
    else        /* Socket empty */
      mmc_stat->Stat = (STA_NODISK | STA_NOINIT);

    mmc_stat->CardType = 0; 
    mmc_stat->tout_flg = 0; //clear condition of time out.
    
	power_on(mmc_stat);							/* Initialize RSPI */
	for (n = 10; n; n--) xchg_spi(mmc_stat, 0xFF);/* Send 80 dummy clocks */
    
	ty = 0;
	if (send_cmd(mmc_stat, CMD0, 0) == 1) {			/* Put the card SPI/Idle state */
      clear_timeout_timer(mmc_stat, DATA_TRANS_TIME);
      sta_alm(mmc_stat-> tout_task_id_0, 10000); /* Initialization timeout = 1 sec */
      if (send_cmd(mmc_stat, CMD8, 0x1AA) == 1) {	/* SDv2? */
        for (n = 0; n < 4; n++) ocr[n] = xchg_spi(mmc_stat, 0xFF);	/* Get 32 bit return value of R7 resp */
        if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* Is the card supports vcc of 2.7-3.6V? */
          while (!is_timeout(mmc_stat, DATA_TRANS_TIME) && send_cmd(mmc_stat, ACMD41, 1UL << 30)) ;	/* Wait for end of initialization with ACMD41(HCS) */
          if (!is_timeout(mmc_stat, DATA_TRANS_TIME) && send_cmd(mmc_stat, CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
            for (n = 0; n < 4; n++) ocr[n] = xchg_spi(mmc_stat, 0xFF);
            ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* Card id SDv2 */
          }
        }
      } else {	/* Not SDv2 card */
        if (send_cmd(mmc_stat, ACMD41, 0) <= 1) 	{	/* SDv1 or MMC? */
          ty = CT_SD1; cmd = ACMD41;	/* SDv1 (ACMD41(0)) */
        } else {
          ty = CT_MMC; cmd = CMD1;	/* MMCv3 (CMD1(0)) */
        }
        while (!is_timeout(mmc_stat, DATA_TRANS_TIME) && send_cmd(mmc_stat, cmd, 0)) ;		/* Wait for end of initialization */
        if (is_timeout(mmc_stat, DATA_TRANS_TIME) || send_cmd(mmc_stat, CMD16, 512) != 0)	/* Set block length: 512 */
          ty = 0;
      }
      stp_alm(mmc_stat-> tout_task_id_0);
	}
	mmc_stat->CardType = ty;	/* Card type */
	deselect(mmc_stat);
    
	if (ty) {			/* OK */
      fast_clk_mode(GET_DEV_STAT(mmc_stat->mmc_drv_id));			/* Set fast clock */
      mmc_stat->Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT flag */
	} else {			/* Failed */
      power_off(mmc_stat);
      mmc_stat->Stat = STA_NOINIT;
	}
    
    rspi_relese_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));
	return mmc_stat->Stat;
}



/*-----------------------------------------------------------------------*/
/* Get disk status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS rspi_disk_status (
	void* v_stat		/* mmc_rspi status */
)
{
    mmc_rspi_stat_t *mmc_stat;
    mmc_stat = (mmc_rspi_stat_t *)v_stat;

	return mmc_stat->Stat;	/* Return disk status */
}

/*-----------------------------------------------------------------------*/
/* Read sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT rspi_disk_read (
	void* v_stat,		/* Status of mmc rspi */
	uint8_t *buff,		/* Pointer to the data buffer to store read data */
	uint32_t sector,	/* Start sector number (LBA) */
	uint32_t count		/* Number of sectors to read (1..128) */
)
{
    mmc_rspi_stat_t *mmc_stat;

    mmc_stat = (mmc_rspi_stat_t *)v_stat;
    
	if (!count) return RES_PARERR;		/* Check parameter */
	if (mmc_stat->Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */
    
    rspi_get_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));
    
	if (!(mmc_stat->CardType & CT_BLOCK)) sector *= 512;	/* LBA ot BA conversion (byte addressing cards) */
    
	if (count == 1) {	/* Single sector read */
      if ((send_cmd(mmc_stat, CMD17, sector) == 0)	/* READ_SINGLE_BLOCK */
          && rcvr_datablock(mmc_stat, buff, 512))
        count = 0;
	}
	else {				/* Multiple sector read */
      if (send_cmd(mmc_stat, CMD18, sector) == 0) {	/* READ_MULTIPLE_BLOCK */
        do {
          if (!rcvr_datablock(mmc_stat, buff, 512)) break;
          buff += 512;
        } while (--count);
        send_cmd(mmc_stat, CMD12, 0);				/* STOP_TRANSMISSION */
      }
	}
	deselect(mmc_stat);
    rspi_relese_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));
	return count ? RES_ERROR : RES_OK;	/* Return result */
}



/*-----------------------------------------------------------------------*/
/* Write sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT rspi_disk_write (
	void* v_stat,		/* Status of mmc rspi */
	const uint8_t *buff,	/* Ponter to the data to write */
	uint32_t sector,		/* Start sector number (LBA) */
	uint32_t count			/* Number of sectors to write (1..128) */
)
{
    mmc_rspi_stat_t *mmc_stat;
    
    mmc_stat = (mmc_rspi_stat_t *)v_stat;
	if (!count) return RES_PARERR;		/* Check parameter */
	if (mmc_stat->Stat & STA_NOINIT) return RES_NOTRDY;	/* Check drive status */

    if (WP) return RES_WRPRT;                           /* Check write protect (check is disable)*/
//	if (mmc_stat->Stat & STA_PROTECT) return RES_WRPRT;	/* Check write protect */

    rspi_get_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));

	if (!(mmc_stat->CardType & CT_BLOCK)) sector *= 512;	/* LBA ==> BA conversion (byte addressing cards) */
    
	if (count == 1) {	/* Single sector write */
      if ((send_cmd(mmc_stat, CMD24, sector) == 0)	/* WRITE_BLOCK */
          && xmit_datablock(mmc_stat, buff, 0xFE))
        count = 0;
	}
	else {				/* Multiple sector write */
      if (mmc_stat->CardType & CT_SDC) send_cmd(mmc_stat, ACMD23, count);
      if (send_cmd(mmc_stat, CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
			do {
              if (!xmit_datablock(mmc_stat, buff, 0xFC)) break;
              buff += 512;
			} while (--count);
			if (!xmit_datablock(mmc_stat, 0, 0xFD))	/* STOP_TRAN token */
              count = 1;
      }
	}
	deselect(mmc_stat);
    
    rspi_relese_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));
	return count ? RES_ERROR : RES_OK;	/* Return result */
}
#endif /* _USE_WRITE */



/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT rspi_disk_ioctl (
	void* v_stat,		/* Status of mmc rspi */
	uint8_t ctrl,		/* Control command code */
	void *buff		/* Pointer to the conrtol data */
)
{
	DRESULT res;
	uint8_t n, csd[16], *ptr = buff;
	uint32_t *dp, st, ed, csz;
    mmc_rspi_stat_t *mmc_stat;

    mmc_stat = (mmc_rspi_stat_t *)v_stat;
	if (mmc_stat->Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

    rspi_get_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));
    
	res = RES_ERROR;

	switch (ctrl) {
	case CTRL_SYNC :		/* Wait for end of internal write process of the drive */
      if (select(mmc_stat)) res = RES_OK;
      break;
      
	case GET_SECTOR_COUNT :	/* Get drive capacity in unit of sector (uint32_t) */
      if ((send_cmd(mmc_stat, CMD9, 0) == 0) && rcvr_datablock(mmc_stat, csd, 16)) {
        if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
          csz = csd[9] + ((uint16_t)csd[8] << 8) + ((uint32_t)(csd[7] & 63) << 16) + 1;
          *(uint32_t*)buff = csz << 10;
        } else {					/* SDC ver 1.XX or MMC ver 3 */
          n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
          csz = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
          *(uint32_t*)buff = csz << (n - 9);
        }
        res = RES_OK;
      }
      break;
      
	case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (uint32_t) */
      if (mmc_stat->CardType & CT_SD2) {	/* SDC ver 2.00 */
        if (send_cmd(mmc_stat, ACMD13, 0) == 0) {	/* Read SD status */
          xchg_spi(mmc_stat, 0xFF);	/* Discard 2nd byte of R2 resp. */
          if (rcvr_datablock(mmc_stat, csd, 16)) {					/* Read partial block */
            for (n = 64 - 16; n; n--) xchg_spi(mmc_stat, 0xFF);	/* Purge trailing data */
            *(uint32_t*)buff = 16UL << (csd[10] >> 4);
            res = RES_OK;
          }
        }
      } else {					/* SDC ver 1.XX or MMC */
        if ((send_cmd(mmc_stat, CMD9, 0) == 0) && rcvr_datablock(mmc_stat, csd, 16)) {	/* Read CSD */
          if (mmc_stat->CardType & CT_SD1) {	/* SDC ver 1.XX */
            *(uint32_t*)buff = (((csd[10] & 63) << 1) + ((uint16_t)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
          } else {					/* MMC */
            *(uint32_t*)buff = ((uint16_t)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
          }
          res = RES_OK;
        }
      }
      break;
      
	case CTRL_TRIM :	/* Erase a block of sectors (used when _USE_TRIM == 1) */
      if (!(mmc_stat->CardType & CT_SDC)) break;				/* Check if the card is SDC */
      if (rspi_disk_ioctl((void*)mmc_stat, MMC_GET_CSD, csd)) break;	/* Get CSD */
		if (!(csd[0] >> 6) && !(csd[10] & 0x40)) break;	/* Check if sector erase can be applied to the card */
		dp = buff; st = dp[0]; ed = dp[1];				/* Load sector block */
		if (!(mmc_stat->CardType & CT_BLOCK)) {
          st *= 512; ed *= 512;
		}
		if (send_cmd(mmc_stat, CMD32, st) == 0 && send_cmd(mmc_stat, CMD33, ed) == 0 && send_cmd(mmc_stat, CMD38, 0) == 0 && wait_ready(mmc_stat, 30000))	/* Erase sector block */
          res = RES_OK;
		break;
        
        /* Following command are not used by FatFs module */
        
	case MMC_GET_TYPE :		/* Get MMC/SDC type (uint8_t) */
      *ptr = mmc_stat->CardType;
      res = RES_OK;
      break;
      
	case MMC_GET_CSD :		/* Read CSD (16 bytes) */
      if (send_cmd(mmc_stat, CMD9, 0) == 0		/* READ_CSD */
          && rcvr_datablock(mmc_stat, ptr, 16))
        res = RES_OK;
      break;
      
	case MMC_GET_CID :		/* Read CID (16 bytes) */
      if (send_cmd(mmc_stat, CMD10, 0) == 0		/* READ_CID */
          && rcvr_datablock(mmc_stat, ptr, 16))
			res = RES_OK;
      break;
      
	case MMC_GET_OCR :		/* Read OCR (4 bytes) */
      if (send_cmd(mmc_stat, CMD58, 0) == 0) {	/* READ_OCR */
        for (n = 4; n; n--) *ptr++ = xchg_spi(mmc_stat, 0xFF);
        res = RES_OK;
      }
      break;
      
	case MMC_GET_SDSTAT :	/* Read SD status (64 bytes) */
      if (send_cmd(mmc_stat, ACMD13, 0) == 0) {	/* SD_STATUS */
        xchg_spi(mmc_stat, 0xFF);
        if (rcvr_datablock(mmc_stat, ptr, 64))
          res = RES_OK;
      }
      break;
      
	default:
      res = RES_PARERR;
	}
    
	deselect(mmc_stat);
    
    rspi_relese_right(GET_DEV_STAT(mmc_stat->mmc_drv_id));
	return res;
}
#endif /* _USE_IOCTL */


/*-----------------------------------------------------------------------*/
/* Device timer function                                                 */
/*-----------------------------------------------------------------------*/

/* This function must be called from RTOS alarm handler
*/
void mmc_rspi_tout0_handler(intptr_t exinf){
  mmc_rspi_stat_t* mmc_stat;
  mmc_stat = (mmc_rspi_stat_t *)GET_DEV_STAT((dnode_id) exinf);

  mmc_stat->tout_flg |= DATA_TRANS_TIME;
}

void mmc_rspi_tout1_handler(intptr_t exinf){
  mmc_rspi_stat_t* mmc_stat;
  mmc_stat = (mmc_rspi_stat_t *)GET_DEV_STAT((dnode_id) exinf);

  mmc_stat->tout_flg |= WAIT_TIME;
}

/*
 * fatfs API get_fattime
 */

uint32_t rspi_get_fattime(){
  return 0;
}


// register call back api of mmc_rspi api
const mmc_func_t mmc_rspi_func = {
  rspi_disk_initialize,
  rspi_disk_status,
  rspi_disk_read,
#ifdef _USE_WRITE
  rspi_disk_write,
#else
  NULL,
#endif
#ifdef _USE_IOCTL
  rspi_disk_ioctl,
#else
  NULL
#endif
};
