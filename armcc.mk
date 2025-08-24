#######
# ARMCC toolchains makefile
#######

BUILD_DIR = build
TARGET = $(BUILD_DIR)/prog.axf

# C sources
C_SOURCES =  \
bsp/stm32f429igt6/board.c            \
bsp/stm32f429igt6/main.c             \
bsp/stm32f429igt6/stm32f4xx_it.c      \
bsp/stm32f429igt6/start/system_stm32f4xx.c \
bsp/stm32f429igt6/drivers/bsp_led.c        \
bsp/stm32f429igt6/drivers/bsp_usart.c        \
bsp/stm32f429igt6/libraries/src/misc.c                          \
bsp/stm32f429igt6/libraries/src/stm32f4xx_adc.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_can.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_cec.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_crc.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_cryp.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_cryp_aes.c            \
bsp/stm32f429igt6/libraries/src/stm32f4xx_cryp_des.c            \
bsp/stm32f429igt6/libraries/src/stm32f4xx_cryp_tdes.c           \
bsp/stm32f429igt6/libraries/src/stm32f4xx_dac.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_dbgmcu.c              \
bsp/stm32f429igt6/libraries/src/stm32f4xx_dcmi.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_dma.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_dma2d.c               \
bsp/stm32f429igt6/libraries/src/stm32f4xx_exti.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_flash.c               \
bsp/stm32f429igt6/libraries/src/stm32f4xx_flash_ramfunc.c       \
bsp/stm32f429igt6/libraries/src/stm32f4xx_fmc.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_fmpi2c.c              \
bsp/stm32f429igt6/libraries/src/stm32f4xx_gpio.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_hash.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_hash_md5.c            \
bsp/stm32f429igt6/libraries/src/stm32f4xx_hash_sha1.c           \
bsp/stm32f429igt6/libraries/src/stm32f4xx_i2c.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_iwdg.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_ltdc.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_pwr.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_qspi.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_rcc.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_rng.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_rtc.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_sai.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_sdio.c                \
bsp/stm32f429igt6/libraries/src/stm32f4xx_spdifrx.c             \
bsp/stm32f429igt6/libraries/src/stm32f4xx_spi.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_syscfg.c              \
bsp/stm32f429igt6/libraries/src/stm32f4xx_tim.c                 \
bsp/stm32f429igt6/libraries/src/stm32f4xx_usart.c               \
bsp/stm32f429igt6/libraries/src/stm32f4xx_wwdg.c                \
libcpu/arm/cortex-m4/cpuport.c    \
src/clock.c         \
src/components.c    \
src/device.c        \
src/idle.c          \
src/ipc.c           \
src/irq.c           \
src/kservice.c      \
src/mem.c           \
src/memheap.c       \
src/mempool.c       \
src/object.c        \
src/scheduler.c     \
src/signal.c        \
src/thread.c        \
src/timer.c         \

# ASM sources
ASM_SOURCES =  \
bsp/stm32f429igt6/start/startup_stm32f429_439xx.s \
libcpu/arm/cortex-m4/context_rvds.S \


# C includes
C_INCLUDES = \
-Ibsp/stm32f429igt6 \
-Ibsp/stm32f429igt6/start \
-Ibsp/stm32f429igt6/libraries/inc \
-Ibsp/stm32f429igt6/drivers \
-Icomponents/finsh \
-Iinclude \

#######################################
# binaries
#######################################
PREFIX = C:/GLQ/.pkg/keil5/keil5_MDK/ARM/ARMCC/bin/
CC = $(PREFIX)armcc
AS = $(PREFIX)armasm
LINK = $(PREFIX)armlink
AR = $(PREFIX)armar
 
# interwork: 允许ARM/Thumb指令混合调用	兼容旧版ARM代码和Thumb高效指令
# split_sections: 函数级代码分节（每函数独立section）	关键优化：链接器可移除未调用函数，显著减少Flash占用（适合库文件多的项目）
CFLAGS = --c99 --gnu -c --cpu Cortex-M4.fp.sp -D__MICROLIB -g -O1 --apcs=interwork --split_sections -DSTM32F429xx -DSTM32F429_439xx -DUSE_STDPERIPH_DRIVER

# --pd: 汇编预处理定义（等同于C的-D）
# xref: 生成交叉引用表, 生成符号交叉引用表，用于追踪汇编代码中所有符号，是实现代码可靠性和空间优化的基石工具
ASFLAGS = --cpu Cortex-M4.fp.sp -g --apcs=interwork --pd "__MICROLIB SETA 1" --pd "STM32F429xx SETA 1" --xref 

# strict: 启用严格模式（警告视为错误）
# scatter: 指定分散加载文件
LDFLAGS = --cpu Cortex-M4.fp.sp --library_type=microlib --strict --scatter "link.sct" 

# default action: build all
all: $(TARGET)

#######################################
# build the application
#######################################
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
OBJECTS := $(OBJECTS:.S=.o)
vpath %.s $(sort $(dir $(ASM_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(C_INCLUDES) $< -o $@

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(CC) $(CFLAGS) ${C_INCLUDES} $< -o $@

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(LINK) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR):
	mkdir $@		

download:
	@openocd.exe -f cmsis-dap.cfg -f stm32f4x.cfg -c "program $(TARGET) verify reset exit"

clean:
	rm -rf $(BUILD_DIR)