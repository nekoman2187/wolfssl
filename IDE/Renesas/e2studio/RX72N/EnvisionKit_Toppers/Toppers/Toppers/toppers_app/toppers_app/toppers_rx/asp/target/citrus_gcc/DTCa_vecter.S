/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

.section DTCA_VECTOR_SEC, "aw", @nobits
.glb _dtca_vect
#define DTCA_MACRO_ONLY
#include <driver/rx_gcc/DTCa.h>

_dtca_vect:
#ifdef USE_DTCA_0
	.space		0400H
    
    .glb _dtca_desc_table
_dtca_desc_table:
    .space      DTCA_DESC_SIZE*NUM_DTCA_DESC
    
	.glb _dtca_vector_end
#else
	.space		4H
#endif
	.glb _dtca_vector_end
_dtca_vector_end:
