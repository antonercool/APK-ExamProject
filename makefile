#Constants
# Verion 1.0.3
## 1.0.1 --> 1.0.3 Now builds if .hpp are modified
## 1.0.3 --> 1.1.0 Now takes DEBUG as param "make DEBUG=true or DEBUG=false + Build tasks added for release and debug

# Paths
SRC_PATH		=.
BUILD_PATH		=$(BUILD_DIR)
BIN_PATH		=$(BIN_DIR)

# Files
SRC				=$(shell find $(SRC_PATH) -name '*.cpp' | sort -k 1nr | cut -f2-)
DEPS			=$(addprefix ${BUILD_PATH}/, $(notdir ${SRC:%.cpp=%.d}))
OBJS			=$(addprefix ${BUILD_PATH}/, $(notdir ${SRC:%.cpp=%.o}))

#config
EXE 			=program
HOST 			=linux
DEBUG 			=false

# All Folders should be added here
VPATH 		    =$(SRC_PATH) StockRender
#Compiler setUp
# To build boost to windows run bootstrap.bat then ./b2 -a toolset=gcc
# To build boost to linux run bootstrap.bat then ./b2

#Edit boostLib paths to yours
BOOSTLIB		= C:/boost/lib
BOOSTROOT 		= C:/boost_1_71_0
INCLUDEPATHS	= -I$(SRC_PATH) -I$(BOOSTROOT)
CXX 			= g++ 
CXXFLAGS 		=-Wall -std=c++17 $(INCLUDEPATHS) -Iinc 	 # -I. = path to include files '. mean here # -Wall Show all Possible warnins

#linker flags -- please update the names for your lib
LDFLAGS 		= #-L$(BOOSTLIB) -lboost_chrono-mgw82-mt-s-x32-1_71 -lboost_thread-mgw82-mt-s-x32-1_71 -lboost_system-mgw82-mt-s-x32-1_71

ifeq ($(DEBUG), true)
CXXFLAGS += -g
endif


#For windows 
ifeq (${HOST}, windows)
BUILD_DIR			= build/${HOST}
BIN_DIR 			= bin/${HOST}
CLEAN_CMD1 			= powershell Remove-Item -Path "${BUILD_DIR}" -Recurse
CLEAN_CMD2 			= powershell Remove-Item -Path "${BIN_DIR}" -Recurse
MAKE_FOLDER_BUILD 	= powershell ./CreateFolder.ps1 "${BUILD_DIR}"  
MAKE_FOLDER_BIN   	= powershell ./CreateFolder.ps1 "${BIN_DIR}"  
endif

#For linux
ifeq (${HOST}, linux)
BUILD_DIR			= build/${HOST}
BIN_DIR 			= bin/${HOST}
CXXFLAGS 			+= -pthread
CLEAN_CMD1 			= -rm -rf ${BUILD_DIR}  
CLEAN_CMD2			= -rm -rf ${BIN_DIR} 
MAKE_FOLDER_BUILD 	= mkdir -p ${BUILD_DIR}  
MAKE_FOLDER_BIN   	= mkdir -p ${BIN_DIR}  
endif

# Prevents potential invalid targets
.PHONY: all clean run help

# Default target
all: info ${BIN_PATH}/${EXE}

# Display compilation info
info:
	@ echo "Compiling for '${host}'"

# -------------------------------------- #
# Folders
# -------------------------------------- #
${BIN_PATH}:
	@ echo "Creating directory '${BIN_PATH}'"
	$(MAKE_FOLDER_BIN)

${BUILD_PATH}:
	@ echo "Creating directory '${BUILD_PATH}'"
	$(MAKE_FOLDER_BUILD)

# -------------------------------------- #
# Dependencies
# -------------------------------------- #
# Create dependencies with the proper prerequisites.
${BUILD_PATH}/%.d: $(BUILD_PATH) %.cpp
	@ echo "Compiling dependency file '$@' using '$^'"
	@ $(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $(filter-out $<, $^) > $@

# -------------------------------------- #
# Objects
# -------------------------------------- #
# Compile all object files from the included dependencies
${BUILD_PATH}/%.o: %.cpp
	@ echo "Compiling object file $@ using '$<'"
	@ ${CXX} -c $< -o $@ ${CXXFLAGS}

# -------------------------------------- #
# Makefile runnables
# -------------------------------------- #
# Linking main executable
${BIN_PATH}/${EXE}: $(BIN_PATH) $(DEPS) $(OBJS)
	@ echo "Linking '${BIN_PATH}/${EXE}'"
	@ ${CXX} -o $@ $(OBJS) $(LDFLAGS) 

# Include all dependencies on default target
ifeq (,$(filter $(MAKECMDGOALS),clean run help))
-include $(DEPS)
endif

clean:
	${CLEAN_CMD1}
	${CLEAN_CMD2}
