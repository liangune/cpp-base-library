#-------------------------------------------------------------------
#-------------------------------Source------------------------------
ifeq ($(BUILD_SHARED_LIBS), ON)
	TARGET := libzlog.so
	BUILD_LIB_TYPE := dynamic
else 
	TARGET := libzlog.a
	BUILD_LIB_TYPE := static
endif
SRCDIRS = ./src 

SRCS = $(foreach n, $(SRCDIRS), $(wildcard $(n)/*.c)) $(foreach n, $(SRCDIRS), $(wildcard $(n)/*.cpp))
OBJS = $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SRCS)))

COMPONENT = ../../../Depend

#-------------------------------------------------------------------
#-------------------------------Flags-------------------------------
CFLAGS  = -g -ggdb -O2 -Wall -fPIC -fno-strict-aliasing -pipe
#DEFINES = 
ARCHIVES = 
LIBS    = -lpthread -lm
INCDIRS = -I./src
LIBDIRS = -L/usr/lib64 -L/usr/local/lib64
OUTDIR ?= $(COMPONENT)/lib/linux/x64/$(BUILD_LIB_TYPE)/zlog
OUTDIR_INCLUDE ?= $(COMPONENT)/include/zlog/$(notdir $(CURDIR))
LIBDIR ?= .
CXX_STANDARD = -std=c++11 
C_STANDARD   = -std=c99 -pedantic

#-------------------------------------------------------------------
#-------------------------------Compile-----------------------------
MK_OUTDIR  := $(shell if [ ! -d $(OUTDIR) ]; then mkdir -p $(OUTDIR); fi )
MK_OUTDIR_INCLUDE  := $(shell if [ ! -d $(OUTDIR_INCLUDE) ]; then mkdir -p $(OUTDIR_INCLUDE); fi )
LOG_FILE   := $(OUTDIR)/make.log
TO_WRITE_LOG := >> $(LOG_FILE) 2>&1
DO_SHOW_LOG  :=    cat $(LOG_FILE) | GREP_COLOR='01;31' egrep --color=always ':[ ]*(error|undefined|错误|未定义|(No such)|(multiple definition))'
DO_SHOW_LOG  += || cat $(LOG_FILE) | GREP_COLOR='01;33' egrep --color=always '(warning|警告|(Build Success))'

ALL: pre_handle $(LIBDIR)/$(TARGET)
.PHONY: ALL

$(basename $(TARGET)): $(OBJS) $(ARCHIVES)
	$(CXX) -o $(OUTDIR)/$(notdir $@) $^ $(ARCHIVES) $(LIBS) $(LIBDIRS) $(TO_WRITE_LOG)

$(LIBDIR)/$(basename $(TARGET)).a: $(OBJS)
	@rm -rf $@ $(OUTDIR)/$@
	ar -rcs $(OUTDIR)/$@ $^
	@rm -rfv $(OBJS)
	@cp -a src/zlog.h $(OUTDIR_INCLUDE)

$(LIBDIR)/$(basename $(TARGET)).so: $(OBJS) $(ARCHIVES)
	@rm -rf $@ $(OUTDIR)/$@
	@#$(CXX) -shared -o $@ $(OUTDIR)/*.o $(ARCHIVES) $(LIBS) $(LIBDIRS)
	$(CXX) -shared -o $@ $^ $(LIBS) $(LIBDIRS)

%.o: %.cpp
	@#echo "$< -> $(OUTDIR)/$(notdir $@)"
	@#$(CXX) $(CFLAGS) $(CXX_STANDARD) $(INCDIRS) -o $(OUTDIR)/$(notdir $@) -c $< $(TO_WRITE_LOG)
	@$(CXX) $(CFLAGS) $(CXX_STANDARD) $(INCDIRS) $(DEFINES)  -o $@ -c $< $(TO_WRITE_LOG)

%.o: %.c
	@#echo "$< -> $(OUTDIR)/$(notdir $@)"
	@#$(CC) $(CFLAGS) $(C_STANDARD) $(INCDIRS) -o $(OUTDIR)/$(notdir $@) -c $< $(TO_WRITE_LOG)
	@$(CC) $(CFLAGS) $(C_STANDARD) $(INCDIRS) $(DEFINES) -o $@ -c $< $(TO_WRITE_LOG)

INSTALL ?= cp -a
DYLIB_VERSION = 1.2.12
DYLIB_NAME=$(TARGET).$(DYLIB_VERSION)
install: 
	$(INSTALL) src/zlog.h $(OUTDIR_INCLUDE)
	#$(INSTALL) $(TARGET) $(OUTDIR)/$(DYLIB_NAME)
	#cd $(OUTDIR) && ln -sf $(DYLIB_NAME) $(TARGET)
	$(INSTALL) $(TARGET) $(OUTDIR)/$(TARGET)

clean:
	@rm -rfv $(TARGET)
	@rm -rfv $(OBJS)
	@rm -rfv $(OUTDIR)/*.o
	@rm -rfv $(LOG_FILE)
.PHONY: clean
pre_handle:
	@rm -f $(LOG_FILE)
.PHONY: pre_handle
err:
	@if [ -f $(LOG_FILE) ]; then \
		$(DO_SHOW_LOG); \
	fi
.PHONY:err
