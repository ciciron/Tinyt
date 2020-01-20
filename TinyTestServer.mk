##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TinyTestServer
ConfigurationName      :=Debug
WorkspacePath          :=/home/universum/projects/tinyt
ProjectPath            :=/home/universum/projects/tinyt
IntermediateDirectory  :=./
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Mihail
Date                   :=20/01/20
CodeLitePath           :=/home/universum/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="TinyTestServer.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_Abuser.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Commands.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Realm.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ServerImpl.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@$(MakeDirCommand) "/home/universum/projects/tinyt/.build-debug"
	@echo rebuilt > "/home/universum/projects/tinyt/.build-debug/TinyTestServer"

MakeIntermediateDirs:
	@test -d ./ || $(MakeDirCommand) ./


./:
	@test -d ./ || $(MakeDirCommand) ./

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_Abuser.cpp$(ObjectSuffix): src/Abuser.cpp $(IntermediateDirectory)/src_Abuser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/universum/projects/tinyt/src/Abuser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Abuser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Abuser.cpp$(DependSuffix): src/Abuser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Abuser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Abuser.cpp$(DependSuffix) -MM src/Abuser.cpp

$(IntermediateDirectory)/src_Abuser.cpp$(PreprocessSuffix): src/Abuser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Abuser.cpp$(PreprocessSuffix) src/Abuser.cpp

$(IntermediateDirectory)/src_Commands.cpp$(ObjectSuffix): src/Commands.cpp $(IntermediateDirectory)/src_Commands.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/universum/projects/tinyt/src/Commands.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Commands.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Commands.cpp$(DependSuffix): src/Commands.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Commands.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Commands.cpp$(DependSuffix) -MM src/Commands.cpp

$(IntermediateDirectory)/src_Commands.cpp$(PreprocessSuffix): src/Commands.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Commands.cpp$(PreprocessSuffix) src/Commands.cpp

$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix): src/Main.cpp $(IntermediateDirectory)/src_Main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/universum/projects/tinyt/src/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Main.cpp$(DependSuffix): src/Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Main.cpp$(DependSuffix) -MM src/Main.cpp

$(IntermediateDirectory)/src_Main.cpp$(PreprocessSuffix): src/Main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Main.cpp$(PreprocessSuffix) src/Main.cpp

$(IntermediateDirectory)/src_Realm.cpp$(ObjectSuffix): src/Realm.cpp $(IntermediateDirectory)/src_Realm.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/universum/projects/tinyt/src/Realm.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Realm.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Realm.cpp$(DependSuffix): src/Realm.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Realm.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Realm.cpp$(DependSuffix) -MM src/Realm.cpp

$(IntermediateDirectory)/src_Realm.cpp$(PreprocessSuffix): src/Realm.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Realm.cpp$(PreprocessSuffix) src/Realm.cpp

$(IntermediateDirectory)/src_ServerImpl.cpp$(ObjectSuffix): src/ServerImpl.cpp $(IntermediateDirectory)/src_ServerImpl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/universum/projects/tinyt/src/ServerImpl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ServerImpl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ServerImpl.cpp$(DependSuffix): src/ServerImpl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ServerImpl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ServerImpl.cpp$(DependSuffix) -MM src/ServerImpl.cpp

$(IntermediateDirectory)/src_ServerImpl.cpp$(PreprocessSuffix): src/ServerImpl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ServerImpl.cpp$(PreprocessSuffix) src/ServerImpl.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./


