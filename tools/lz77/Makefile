# programs
CC = gcc
CXX = g++
STRIP = strip
RM = rm

# flags
CFLAGS = -g -Wall
CXXFLAGS = $(CFLAGS)
LIBS =

# directories
SOURCEDIR = src
HEADERDIR =
LIBDIR = 

# generated variables
CFILES = $(foreach dir,$(SOURCEDIR),$(wildcard $(dir)/*.c))
CPPFILES = $(foreach dir,$(SOURCEDIR),$(wildcard $(dir)/*.cpp))
HEADERS = $(CFILES:.c=.h) $(CPPFILES:.cpp=.h)
OBJS = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
LIBS += $(foreach dir,$(LIBDIR),-L $(dir))
INCLUDE = $(foreach dir,$(HEADERDIR),-I $(dir))
PROJECT = $(notdir $(CURDIR))

# selecting linker
ifeq ($(strip $(CPPFILES)), )
	export LD = $(CC)
else
	export LD = $(CXX)
endif

# default compilation
.c.o: %.c
	@echo [CC] $<
	@$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $<

.cpp.o: %.cpp
	@echo [CXX] $<
	@$(CXX) $(INCLUDE) $(CXXFLAGS) -o $@ -c $<

# standard rules
$(PROJECT): $(OBJS)
	@echo [LINK] $(PROJECT)
	@$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@echo Removing objects...
	@$(RM) -f $(OBJS)

mrproper: clean
	@echo Removing $(PROJECT)
	@$(RM) -f $(PROJECT)

release: all clean
	@echo [STRIP] $(PROJECT)
	@$(STRIP) $(PROJECT)

depend:
	makedepend -- $(CFLAGS) -- $(CFILES) $(CPPFILES)
