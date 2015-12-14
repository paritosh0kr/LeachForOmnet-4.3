#
# OMNeT++/OMNEST Makefile for leach
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = leach$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Ih \
    -Ilist \
    -Imessage \
    -Ined \
    -Iresults \
    -Isrc

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/src/bs.o \
    $O/src/node.o \
    $O/src/nodebase.o \
    $O/message/ClusterHeadMessage_m.o \
    $O/message/ClusterMessage_m.o \
    $O/message/Data2BSMessage_m.o \
    $O/message/DataToCHMessage_m.o \
    $O/message/Status2BSMessage_m.o \
    $O/message/TDMAMessage_m.o

# Message files
MSGFILES = \
    message/ClusterHeadMessage.msg \
    message/ClusterMessage.msg \
    message/Data2BSMessage.msg \
    message/DataToCHMessage.msg \
    message/Status2BSMessage.msg \
    message/TDMAMessage.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f leach leach.exe libleach.so libleach.a libleach.dll libleach.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f h/*_m.cc h/*_m.h
	$(Q)-rm -f list/*_m.cc list/*_m.h
	$(Q)-rm -f message/*_m.cc message/*_m.h
	$(Q)-rm -f ned/*_m.cc ned/*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc h/*.cc list/*.cc message/*.cc ned/*.cc results/*.cc src/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/message/ClusterHeadMessage_m.o: message/ClusterHeadMessage_m.cc \
	message/ClusterHeadMessage_m.h \
	message/ClusterMessage_m.h
$O/message/ClusterMessage_m.o: message/ClusterMessage_m.cc \
	message/ClusterMessage_m.h
$O/message/Data2BSMessage_m.o: message/Data2BSMessage_m.cc \
	message/ClusterMessage_m.h \
	message/Data2BSMessage_m.h
$O/message/DataToCHMessage_m.o: message/DataToCHMessage_m.cc \
	message/ClusterMessage_m.h \
	message/DataToCHMessage_m.h
$O/message/Status2BSMessage_m.o: message/Status2BSMessage_m.cc \
	message/ClusterMessage_m.h \
	message/Status2BSMessage_m.h
$O/message/TDMAMessage_m.o: message/TDMAMessage_m.cc \
	message/ClusterMessage_m.h \
	message/TDMAMessage_m.h
$O/src/bs.o: src/bs.cc \
	h/bs.h \
	h/node.h \
	h/nodebase.h \
	h/solar.h \
	message/ClusterHeadMessage_m.h \
	message/ClusterMessage_m.h \
	message/Status2BSMessage_m.h
$O/src/node.o: src/node.cc \
	h/bs.h \
	h/node.h \
	h/nodebase.h \
	h/solar.h \
	message/ClusterHeadMessage_m.h \
	message/ClusterMessage_m.h \
	message/Data2BSMessage_m.h \
	message/DataToCHMessage_m.h \
	message/Status2BSMessage_m.h \
	message/TDMAMessage_m.h
$O/src/nodebase.o: src/nodebase.cc \
	h/nodebase.h \
	h/solar.h

