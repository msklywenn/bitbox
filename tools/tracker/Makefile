# programs
CC = gcc
CXX = g++
STRIP = strip
RM = rm

# flags
CFLAGS = -g -Wall `sdl-config --cflags` `pkg-config portaudio-2.0 --cflags`
CXXFLAGS = $(CFLAGS)
LIBS = `sdl-config --libs` `pkg-config portaudio-2.0 --libs` -lfftw3f

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
	makedepend -- $(CXXFLAGS) -- $(CFILES) $(CPPFILES)

# DO NOT DELETE

src/channel.o: src/channel.h
src/font.o: src/font.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/font.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/font.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/font.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/font.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/font.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/font.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/font.o: /usr/include/endian.h /usr/include/bits/endian.h
src/font.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/font.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/font.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/font.o: /usr/include/stdio.h /usr/include/libio.h
src/font.o: /usr/include/_G_config.h /usr/include/wchar.h
src/font.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/font.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/font.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/font.o: /usr/include/alloca.h /usr/include/string.h
src/font.o: /usr/include/strings.h /usr/include/inttypes.h
src/font.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/font.o: /usr/include/ctype.h /usr/include/iconv.h
src/font.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/font.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/font.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/font.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/font.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/font.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/font.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/font.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/font.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/font.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/font.o: /usr/include/SDL/SDL_version.h
src/guichannel.o: src/guichannel.h src/guielement.h /usr/include/SDL/SDL.h
src/guichannel.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guichannel.o: /usr/include/SDL/SDL_config.h
src/guichannel.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/guichannel.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/guichannel.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/guichannel.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/guichannel.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/guichannel.o: /usr/include/endian.h /usr/include/bits/endian.h
src/guichannel.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/guichannel.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/guichannel.o: /usr/include/sys/sysmacros.h
src/guichannel.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guichannel.o: /usr/include/libio.h /usr/include/_G_config.h
src/guichannel.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guichannel.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guichannel.o: /usr/include/bits/waitflags.h
src/guichannel.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/guichannel.o: /usr/include/alloca.h /usr/include/string.h
src/guichannel.o: /usr/include/strings.h /usr/include/inttypes.h
src/guichannel.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/guichannel.o: /usr/include/ctype.h /usr/include/iconv.h
src/guichannel.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/guichannel.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/guichannel.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/guichannel.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/guichannel.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/guichannel.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/guichannel.o: /usr/include/SDL/SDL_keyboard.h
src/guichannel.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guichannel.o: /usr/include/SDL/SDL_video.h
src/guichannel.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/guichannel.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/guichannel.o: /usr/include/SDL/SDL_version.h src/guievents.h
src/guichannel.o: src/channel.h src/copy.h src/synth.h
src/guichannel.o: /usr/include/portaudio.h src/tune.h src/psg.h src/midi.h
src/guichannel.o: src/font.h src/palette.h
src/guiclock.o: src/guiclock.h src/guielement.h /usr/include/SDL/SDL.h
src/guiclock.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guiclock.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/guiclock.o: /usr/include/sys/types.h /usr/include/features.h
src/guiclock.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guiclock.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guiclock.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/guiclock.o: /usr/include/time.h /usr/include/endian.h
src/guiclock.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/guiclock.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/guiclock.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/guiclock.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guiclock.o: /usr/include/libio.h /usr/include/_G_config.h
src/guiclock.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guiclock.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guiclock.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/guiclock.o: /usr/include/xlocale.h /usr/include/alloca.h
src/guiclock.o: /usr/include/string.h /usr/include/strings.h
src/guiclock.o: /usr/include/inttypes.h /usr/include/stdint.h
src/guiclock.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/guiclock.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/guiclock.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guiclock.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guiclock.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guiclock.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guiclock.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/guiclock.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/guiclock.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guiclock.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/guiclock.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guiclock.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/guiclock.o: src/guievents.h src/tune.h src/channel.h src/font.h
src/guiclock.o: src/palette.h
src/gui.o: src/gui.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/gui.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/gui.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/gui.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/gui.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/gui.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/gui.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/gui.o: /usr/include/endian.h /usr/include/bits/endian.h
src/gui.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/gui.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/gui.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/gui.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
src/gui.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/gui.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/gui.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/gui.o: /usr/include/xlocale.h /usr/include/alloca.h /usr/include/string.h
src/gui.o: /usr/include/strings.h /usr/include/inttypes.h
src/gui.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/gui.o: /usr/include/ctype.h /usr/include/iconv.h
src/gui.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/gui.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/gui.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/gui.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/gui.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/gui.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/gui.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/gui.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/gui.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/gui.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/gui.o: /usr/include/SDL/SDL_version.h src/guielement.h src/guievents.h
src/guielement.o: src/guielement.h /usr/include/SDL/SDL.h
src/guielement.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guielement.o: /usr/include/SDL/SDL_config.h
src/guielement.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/guielement.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/guielement.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/guielement.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/guielement.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/guielement.o: /usr/include/endian.h /usr/include/bits/endian.h
src/guielement.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/guielement.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/guielement.o: /usr/include/sys/sysmacros.h
src/guielement.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guielement.o: /usr/include/libio.h /usr/include/_G_config.h
src/guielement.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guielement.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guielement.o: /usr/include/bits/waitflags.h
src/guielement.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/guielement.o: /usr/include/alloca.h /usr/include/string.h
src/guielement.o: /usr/include/strings.h /usr/include/inttypes.h
src/guielement.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/guielement.o: /usr/include/ctype.h /usr/include/iconv.h
src/guielement.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/guielement.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/guielement.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/guielement.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/guielement.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/guielement.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/guielement.o: /usr/include/SDL/SDL_keyboard.h
src/guielement.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guielement.o: /usr/include/SDL/SDL_video.h
src/guielement.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/guielement.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/guielement.o: /usr/include/SDL/SDL_version.h src/guievents.h
src/guievents.o: src/guievents.h /usr/include/SDL/SDL.h
src/guievents.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guievents.o: /usr/include/SDL/SDL_config.h
src/guievents.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/guievents.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/guievents.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/guievents.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/guievents.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/guievents.o: /usr/include/endian.h /usr/include/bits/endian.h
src/guievents.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/guievents.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/guievents.o: /usr/include/sys/sysmacros.h
src/guievents.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guievents.o: /usr/include/libio.h /usr/include/_G_config.h
src/guievents.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guievents.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guievents.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/guievents.o: /usr/include/xlocale.h /usr/include/alloca.h
src/guievents.o: /usr/include/string.h /usr/include/strings.h
src/guievents.o: /usr/include/inttypes.h /usr/include/stdint.h
src/guievents.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/guievents.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/guievents.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guievents.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guievents.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guievents.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guievents.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/guievents.o: /usr/include/SDL/SDL_active.h
src/guievents.o: /usr/include/SDL/SDL_keyboard.h
src/guievents.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guievents.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/guievents.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guievents.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/guimute.o: src/guimute.h src/guielement.h /usr/include/SDL/SDL.h
src/guimute.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guimute.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/guimute.o: /usr/include/sys/types.h /usr/include/features.h
src/guimute.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guimute.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guimute.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/guimute.o: /usr/include/time.h /usr/include/endian.h
src/guimute.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/guimute.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/guimute.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/guimute.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guimute.o: /usr/include/libio.h /usr/include/_G_config.h
src/guimute.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guimute.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guimute.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/guimute.o: /usr/include/xlocale.h /usr/include/alloca.h
src/guimute.o: /usr/include/string.h /usr/include/strings.h
src/guimute.o: /usr/include/inttypes.h /usr/include/stdint.h
src/guimute.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/guimute.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/guimute.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guimute.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guimute.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guimute.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guimute.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/guimute.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/guimute.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guimute.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/guimute.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guimute.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/guimute.o: src/guievents.h src/synth.h /usr/include/portaudio.h
src/guimute.o: src/tune.h src/channel.h src/psg.h src/font.h src/palette.h
src/guiname.o: src/guiname.h src/guielement.h /usr/include/SDL/SDL.h
src/guiname.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guiname.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/guiname.o: /usr/include/sys/types.h /usr/include/features.h
src/guiname.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guiname.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guiname.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/guiname.o: /usr/include/time.h /usr/include/endian.h
src/guiname.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/guiname.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/guiname.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/guiname.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guiname.o: /usr/include/libio.h /usr/include/_G_config.h
src/guiname.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guiname.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guiname.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/guiname.o: /usr/include/xlocale.h /usr/include/alloca.h
src/guiname.o: /usr/include/string.h /usr/include/strings.h
src/guiname.o: /usr/include/inttypes.h /usr/include/stdint.h
src/guiname.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/guiname.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/guiname.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guiname.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guiname.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guiname.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guiname.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/guiname.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/guiname.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guiname.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/guiname.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guiname.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/guiname.o: src/guievents.h src/font.h
src/guioscilloscope.o: src/guioscilloscope.h src/guielement.h
src/guioscilloscope.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/guioscilloscope.o: /usr/include/SDL/SDL_stdinc.h
src/guioscilloscope.o: /usr/include/SDL/SDL_config.h
src/guioscilloscope.o: /usr/include/SDL/SDL_platform.h
src/guioscilloscope.o: /usr/include/sys/types.h /usr/include/features.h
src/guioscilloscope.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guioscilloscope.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guioscilloscope.o: /usr/include/bits/types.h
src/guioscilloscope.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/guioscilloscope.o: /usr/include/endian.h /usr/include/bits/endian.h
src/guioscilloscope.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/guioscilloscope.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/guioscilloscope.o: /usr/include/sys/sysmacros.h
src/guioscilloscope.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guioscilloscope.o: /usr/include/libio.h /usr/include/_G_config.h
src/guioscilloscope.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guioscilloscope.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guioscilloscope.o: /usr/include/bits/waitflags.h
src/guioscilloscope.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/guioscilloscope.o: /usr/include/alloca.h /usr/include/string.h
src/guioscilloscope.o: /usr/include/strings.h /usr/include/inttypes.h
src/guioscilloscope.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/guioscilloscope.o: /usr/include/ctype.h /usr/include/iconv.h
src/guioscilloscope.o: /usr/include/SDL/begin_code.h
src/guioscilloscope.o: /usr/include/SDL/close_code.h
src/guioscilloscope.o: /usr/include/SDL/SDL_audio.h
src/guioscilloscope.o: /usr/include/SDL/SDL_error.h
src/guioscilloscope.o: /usr/include/SDL/SDL_endian.h
src/guioscilloscope.o: /usr/include/SDL/SDL_mutex.h
src/guioscilloscope.o: /usr/include/SDL/SDL_thread.h
src/guioscilloscope.o: /usr/include/SDL/SDL_rwops.h
src/guioscilloscope.o: /usr/include/SDL/SDL_cdrom.h
src/guioscilloscope.o: /usr/include/SDL/SDL_cpuinfo.h
src/guioscilloscope.o: /usr/include/SDL/SDL_events.h
src/guioscilloscope.o: /usr/include/SDL/SDL_active.h
src/guioscilloscope.o: /usr/include/SDL/SDL_keyboard.h
src/guioscilloscope.o: /usr/include/SDL/SDL_keysym.h
src/guioscilloscope.o: /usr/include/SDL/SDL_mouse.h
src/guioscilloscope.o: /usr/include/SDL/SDL_video.h
src/guioscilloscope.o: /usr/include/SDL/SDL_joystick.h
src/guioscilloscope.o: /usr/include/SDL/SDL_quit.h
src/guioscilloscope.o: /usr/include/SDL/SDL_loadso.h
src/guioscilloscope.o: /usr/include/SDL/SDL_timer.h
src/guioscilloscope.o: /usr/include/SDL/SDL_version.h src/guievents.h
src/guioscilloscope.o: src/synth.h /usr/include/portaudio.h src/tune.h
src/guioscilloscope.o: src/channel.h src/psg.h src/palette.h
src/guispectrum.o: src/guispectrum.h /usr/include/fftw3.h
src/guispectrum.o: /usr/include/stdio.h /usr/include/features.h
src/guispectrum.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guispectrum.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guispectrum.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/guispectrum.o: /usr/include/libio.h /usr/include/_G_config.h
src/guispectrum.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guispectrum.o: /usr/include/bits/sys_errlist.h src/guielement.h
src/guispectrum.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/guispectrum.o: /usr/include/SDL/SDL_stdinc.h
src/guispectrum.o: /usr/include/SDL/SDL_config.h
src/guispectrum.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/guispectrum.o: /usr/include/time.h /usr/include/endian.h
src/guispectrum.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/guispectrum.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/guispectrum.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/guispectrum.o: /usr/include/bits/pthreadtypes.h /usr/include/stdlib.h
src/guispectrum.o: /usr/include/bits/waitflags.h
src/guispectrum.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/guispectrum.o: /usr/include/alloca.h /usr/include/string.h
src/guispectrum.o: /usr/include/strings.h /usr/include/inttypes.h
src/guispectrum.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/guispectrum.o: /usr/include/ctype.h /usr/include/iconv.h
src/guispectrum.o: /usr/include/SDL/begin_code.h
src/guispectrum.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guispectrum.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guispectrum.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guispectrum.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guispectrum.o: /usr/include/SDL/SDL_cpuinfo.h
src/guispectrum.o: /usr/include/SDL/SDL_events.h
src/guispectrum.o: /usr/include/SDL/SDL_active.h
src/guispectrum.o: /usr/include/SDL/SDL_keyboard.h
src/guispectrum.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guispectrum.o: /usr/include/SDL/SDL_video.h
src/guispectrum.o: /usr/include/SDL/SDL_joystick.h
src/guispectrum.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guispectrum.o: /usr/include/SDL/SDL_timer.h
src/guispectrum.o: /usr/include/SDL/SDL_version.h src/guievents.h src/synth.h
src/guispectrum.o: /usr/include/portaudio.h src/tune.h src/channel.h
src/guispectrum.o: src/psg.h /usr/include/math.h /usr/include/bits/huge_val.h
src/guispectrum.o: /usr/include/bits/huge_valf.h
src/guispectrum.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/guispectrum.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/guispectrum.o: /usr/include/bits/mathcalls.h src/palette.h
src/guistatusbar.o: src/guistatusbar.h src/guielement.h
src/guistatusbar.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/guistatusbar.o: /usr/include/SDL/SDL_stdinc.h
src/guistatusbar.o: /usr/include/SDL/SDL_config.h
src/guistatusbar.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/guistatusbar.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/guistatusbar.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/guistatusbar.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/guistatusbar.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/guistatusbar.o: /usr/include/endian.h /usr/include/bits/endian.h
src/guistatusbar.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/guistatusbar.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/guistatusbar.o: /usr/include/sys/sysmacros.h
src/guistatusbar.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guistatusbar.o: /usr/include/libio.h /usr/include/_G_config.h
src/guistatusbar.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guistatusbar.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guistatusbar.o: /usr/include/bits/waitflags.h
src/guistatusbar.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/guistatusbar.o: /usr/include/alloca.h /usr/include/string.h
src/guistatusbar.o: /usr/include/strings.h /usr/include/inttypes.h
src/guistatusbar.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/guistatusbar.o: /usr/include/ctype.h /usr/include/iconv.h
src/guistatusbar.o: /usr/include/SDL/begin_code.h
src/guistatusbar.o: /usr/include/SDL/close_code.h
src/guistatusbar.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/guistatusbar.o: /usr/include/SDL/SDL_endian.h
src/guistatusbar.o: /usr/include/SDL/SDL_mutex.h
src/guistatusbar.o: /usr/include/SDL/SDL_thread.h
src/guistatusbar.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guistatusbar.o: /usr/include/SDL/SDL_cpuinfo.h
src/guistatusbar.o: /usr/include/SDL/SDL_events.h
src/guistatusbar.o: /usr/include/SDL/SDL_active.h
src/guistatusbar.o: /usr/include/SDL/SDL_keyboard.h
src/guistatusbar.o: /usr/include/SDL/SDL_keysym.h
src/guistatusbar.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/guistatusbar.o: /usr/include/SDL/SDL_joystick.h
src/guistatusbar.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guistatusbar.o: /usr/include/SDL/SDL_timer.h
src/guistatusbar.o: /usr/include/SDL/SDL_version.h src/guievents.h src/font.h
src/guitime.o: src/guitime.h src/guielement.h /usr/include/SDL/SDL.h
src/guitime.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guitime.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/guitime.o: /usr/include/sys/types.h /usr/include/features.h
src/guitime.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guitime.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guitime.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/guitime.o: /usr/include/time.h /usr/include/endian.h
src/guitime.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/guitime.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/guitime.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/guitime.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guitime.o: /usr/include/libio.h /usr/include/_G_config.h
src/guitime.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guitime.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guitime.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/guitime.o: /usr/include/xlocale.h /usr/include/alloca.h
src/guitime.o: /usr/include/string.h /usr/include/strings.h
src/guitime.o: /usr/include/inttypes.h /usr/include/stdint.h
src/guitime.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/guitime.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/guitime.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guitime.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guitime.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guitime.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guitime.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/guitime.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/guitime.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guitime.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/guitime.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guitime.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/guitime.o: src/guievents.h src/synth.h /usr/include/portaudio.h
src/guitime.o: src/tune.h src/channel.h src/psg.h src/font.h src/palette.h
src/guitime.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
src/guitime.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
src/guitime.o: /usr/include/bits/posix2_lim.h /usr/include/bits/xopen_lim.h
src/guivalue.o: src/guivalue.h src/guielement.h /usr/include/SDL/SDL.h
src/guivalue.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guivalue.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/guivalue.o: /usr/include/sys/types.h /usr/include/features.h
src/guivalue.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guivalue.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guivalue.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/guivalue.o: /usr/include/time.h /usr/include/endian.h
src/guivalue.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/guivalue.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/guivalue.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/guivalue.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guivalue.o: /usr/include/libio.h /usr/include/_G_config.h
src/guivalue.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guivalue.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guivalue.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/guivalue.o: /usr/include/xlocale.h /usr/include/alloca.h
src/guivalue.o: /usr/include/string.h /usr/include/strings.h
src/guivalue.o: /usr/include/inttypes.h /usr/include/stdint.h
src/guivalue.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/guivalue.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/guivalue.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guivalue.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guivalue.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guivalue.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guivalue.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/guivalue.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/guivalue.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guivalue.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/guivalue.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guivalue.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/guivalue.o: src/guievents.h src/font.h
src/guivu.o: src/guivu.h src/guielement.h /usr/include/SDL/SDL.h
src/guivu.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guivu.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/guivu.o: /usr/include/sys/types.h /usr/include/features.h
src/guivu.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/guivu.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/guivu.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/guivu.o: /usr/include/time.h /usr/include/endian.h
src/guivu.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/guivu.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/guivu.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/guivu.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guivu.o: /usr/include/libio.h /usr/include/_G_config.h
src/guivu.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guivu.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guivu.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/guivu.o: /usr/include/xlocale.h /usr/include/alloca.h
src/guivu.o: /usr/include/string.h /usr/include/strings.h
src/guivu.o: /usr/include/inttypes.h /usr/include/stdint.h
src/guivu.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/guivu.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/guivu.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/guivu.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/guivu.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/guivu.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/guivu.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/guivu.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/guivu.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guivu.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/guivu.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/guivu.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/guivu.o: src/guievents.h src/synth.h /usr/include/portaudio.h src/tune.h
src/guivu.o: src/channel.h src/psg.h /usr/include/math.h
src/guivu.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/guivu.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/guivu.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/guivu.o: /usr/include/bits/mathcalls.h src/palette.h
src/guiwaveout.o: src/guiwaveout.h src/guielement.h /usr/include/SDL/SDL.h
src/guiwaveout.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/guiwaveout.o: /usr/include/SDL/SDL_config.h
src/guiwaveout.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/guiwaveout.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/guiwaveout.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/guiwaveout.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/guiwaveout.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/guiwaveout.o: /usr/include/endian.h /usr/include/bits/endian.h
src/guiwaveout.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/guiwaveout.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/guiwaveout.o: /usr/include/sys/sysmacros.h
src/guiwaveout.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/guiwaveout.o: /usr/include/libio.h /usr/include/_G_config.h
src/guiwaveout.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/guiwaveout.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/guiwaveout.o: /usr/include/bits/waitflags.h
src/guiwaveout.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/guiwaveout.o: /usr/include/alloca.h /usr/include/string.h
src/guiwaveout.o: /usr/include/strings.h /usr/include/inttypes.h
src/guiwaveout.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/guiwaveout.o: /usr/include/ctype.h /usr/include/iconv.h
src/guiwaveout.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/guiwaveout.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/guiwaveout.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/guiwaveout.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/guiwaveout.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/guiwaveout.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/guiwaveout.o: /usr/include/SDL/SDL_keyboard.h
src/guiwaveout.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/guiwaveout.o: /usr/include/SDL/SDL_video.h
src/guiwaveout.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/guiwaveout.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/guiwaveout.o: /usr/include/SDL/SDL_version.h src/guievents.h
src/guiwaveout.o: src/guiname.h src/guistatusbar.h src/synth.h
src/guiwaveout.o: /usr/include/portaudio.h src/tune.h src/channel.h src/psg.h
src/main.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/main.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/main.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/main.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/main.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/main.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/main.o: /usr/include/endian.h /usr/include/bits/endian.h
src/main.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/main.o: /usr/include/stdio.h /usr/include/libio.h
src/main.o: /usr/include/_G_config.h /usr/include/wchar.h
src/main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/main.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
src/main.o: /usr/include/alloca.h /usr/include/string.h
src/main.o: /usr/include/strings.h /usr/include/inttypes.h
src/main.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/main.o: /usr/include/ctype.h /usr/include/iconv.h
src/main.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/main.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/main.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/main.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/main.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/main.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/main.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/main.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/main.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/main.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/main.o: /usr/include/SDL/SDL_version.h src/font.h src/palette.h src/gui.h
src/main.o: src/guielement.h src/guievents.h src/guichannel.h src/channel.h
src/main.o: src/copy.h src/synth.h /usr/include/portaudio.h src/tune.h
src/main.o: src/psg.h src/guistatusbar.h src/guitime.h src/guiclock.h
src/main.o: src/guivalue.h src/guiname.h src/guimute.h src/guioscilloscope.h
src/main.o: src/guispectrum.h /usr/include/fftw3.h src/guivu.h
src/main.o: src/guiwaveout.h
src/midi.o: src/midi.h /usr/include/math.h /usr/include/features.h
src/midi.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/midi.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/midi.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/midi.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/midi.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/midi.o: /usr/include/bits/mathcalls.h /usr/include/stdio.h
src/midi.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/midi.o: /usr/include/libio.h /usr/include/_G_config.h
src/midi.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/midi.o: /usr/include/bits/sys_errlist.h
src/palette.o: src/palette.h /usr/include/SDL/SDL.h
src/palette.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/palette.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/palette.o: /usr/include/sys/types.h /usr/include/features.h
src/palette.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/palette.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/palette.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/palette.o: /usr/include/time.h /usr/include/endian.h
src/palette.o: /usr/include/bits/endian.h /usr/include/sys/select.h
src/palette.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/palette.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/palette.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/palette.o: /usr/include/libio.h /usr/include/_G_config.h
src/palette.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/palette.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/palette.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/palette.o: /usr/include/xlocale.h /usr/include/alloca.h
src/palette.o: /usr/include/string.h /usr/include/strings.h
src/palette.o: /usr/include/inttypes.h /usr/include/stdint.h
src/palette.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/palette.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/palette.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/palette.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/palette.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/palette.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/palette.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/palette.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/palette.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/palette.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/palette.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/palette.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/psg.o: src/psg.h
src/synth.o: src/synth.h /usr/include/portaudio.h src/tune.h src/channel.h
src/synth.o: src/psg.h /usr/include/stdio.h /usr/include/features.h
src/synth.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/synth.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/synth.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/synth.o: /usr/include/libio.h /usr/include/_G_config.h
src/synth.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/synth.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
src/synth.o: /usr/include/xlocale.h /usr/include/SDL/SDL.h
src/synth.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/synth.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/synth.o: /usr/include/sys/types.h /usr/include/time.h
src/synth.o: /usr/include/endian.h /usr/include/bits/endian.h
src/synth.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/synth.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/synth.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/synth.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/synth.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
src/synth.o: /usr/include/strings.h /usr/include/inttypes.h
src/synth.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/synth.o: /usr/include/ctype.h /usr/include/iconv.h
src/synth.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/synth.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/synth.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/synth.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/synth.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/synth.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/synth.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/synth.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/synth.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/synth.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/synth.o: /usr/include/SDL/SDL_version.h src/midi.h src/guievents.h
src/tune.o: src/tune.h src/channel.h src/midi.h /usr/include/stdio.h
src/tune.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/tune.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/tune.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
src/tune.o: /usr/include/bits/typesizes.h /usr/include/libio.h
src/tune.o: /usr/include/_G_config.h /usr/include/wchar.h
src/tune.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/tune.o: /usr/include/string.h /usr/include/xlocale.h
