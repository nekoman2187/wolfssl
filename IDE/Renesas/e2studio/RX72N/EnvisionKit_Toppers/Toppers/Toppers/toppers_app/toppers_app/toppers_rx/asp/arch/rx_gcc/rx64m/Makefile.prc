#
#		Makefile のchip依存部（rx用）
#

# 
#  チップ依存部ディレクトリ名の定義 
# 
ARCH_SYS_DIR = $(SRCDIR)/arch/rx_$(TOOL)/$(PRC)

#
# include Makefile of arch_common
#
include $(SRCDIR)/arch/rx_$(TOOL)/rx_common/Makefile.prc_common

#
#  コンパイルオプション
#
INCLUDES := $(INCLUDES) -I$(ARCH_SYS_DIR)
CDEFS := $(CDEFS)
COPTS := $(COPTS)

#
#  カーネルに関する定義
#
KERNEL_DIR := $(KERNEL_DIR) $(ARCH_SYS_DIR) 
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS)
KERNEL_COBJS := $(KERNEL_COBJS) rx64m_config.o rx64m_support.o

#
#  システムサービスに関する定義
#
SYSSVC_DIR := $(SYSSVC_DIR)
SYSSVC_COBJS := $(SYSSVC_COBJS)

#
#  トレースログに関する設定
#
ifeq ($(ENABLE_TRACE),true)
	COPTS := $(COPTS) -DTOPPERS_ENABLE_TRACE
	KERNEL_DIR := $(KERNEL_DIR) $(SRCDIR)/arch/logtrace
	KERNEL_COBJS := $(KERNEL_COBJS) trace_config.o trace_dump.o
endif

#
#  依存関係の定義
# 
kernel_cfg.timestamp: $(ARCH_SYS_DIR)/rx64m.tf $(ARCH_SYS_DIR)/prc.tf
#kernel_cfg.timestamp: $(ARCH_COM_DIR)/prc.tf


# 
#  オフセットファイル生成のための定義 
# 
OFFSET_TF = $(TARGETDIR)/target_offset.tf


#
#  ツール依存部ディレクトリ名の定義 
#
TOOLDIR = $(SRCDIR)/arch/$(TOOL)

#
#  コンパイルオプション
#
COPTS := $(COPTS)
INCLUDES := $(INCLUDES) -I$(TOOLDIR)
LDFLAGS := -nostdlib $(LDFLAGS) 
CDEFS := $(CDEFS)
LIBS := $(LIBS)  -lgcc
