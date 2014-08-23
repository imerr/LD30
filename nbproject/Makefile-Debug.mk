#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/LD30Game.o \
	${OBJECTDIR}/TitleScreen.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../SFML/Engine/dist/Debug/MinGW-Windows/libengine.a ../../SFML/box2d/dist/Debug/MinGW-Windows/libbox2d.a ../../SFML/sfml/lib/libsfml-audio-d.a ../../SFML/sfml/lib/libsfml-graphics-d.a ../../SFML/sfml/lib/libsfml-network-d.a ../../SFML/sfml/lib/libsfml-system-d.a ../../SFML/sfml/lib/libsfml-window-d.a ../extern/lib/libjsoncpp.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../../SFML/Engine/dist/Debug/MinGW-Windows/libengine.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../../SFML/box2d/dist/Debug/MinGW-Windows/libbox2d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../../SFML/sfml/lib/libsfml-audio-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../../SFML/sfml/lib/libsfml-graphics-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../../SFML/sfml/lib/libsfml-network-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../../SFML/sfml/lib/libsfml-system-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../../SFML/sfml/lib/libsfml-window-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ../extern/lib/libjsoncpp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/LD30Game.o: LD30Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../sfml/include -I.. -I../Engine/src -I../box2d -I../extern/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LD30Game.o LD30Game.cpp

${OBJECTDIR}/TitleScreen.o: TitleScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../sfml/include -I.. -I../Engine/src -I../box2d -I../extern/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TitleScreen.o TitleScreen.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../sfml/include -I.. -I../Engine/src -I../box2d -I../extern/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../../SFML/Engine && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ld30.exe

# Subprojects
.clean-subprojects:
	cd ../../SFML/Engine && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc