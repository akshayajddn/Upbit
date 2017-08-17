##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Upbit
ConfigurationName      :=Debug
WorkspacePath          :=/home/harsha/Documents/UpBit
ProjectPath            :=/home/harsha/Documents/UpBit/Upbit
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Chigullapally Sriharsha
Date                   :=25/11/16
CodeLitePath           :=/home/harsha/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
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
ObjectsFileList        :="Upbit.txt"
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
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/wah.cpp$(ObjectSuffix) $(IntermediateDirectory)/update.cpp$(ObjectSuffix) $(IntermediateDirectory)/read.cpp$(ObjectSuffix) $(IntermediateDirectory)/merge.cpp$(ObjectSuffix) $(IntermediateDirectory)/master.cpp$(ObjectSuffix) $(IntermediateDirectory)/insert.cpp$(ObjectSuffix) $(IntermediateDirectory)/delete.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/wah.cpp$(ObjectSuffix): wah.cpp $(IntermediateDirectory)/wah.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/harsha/Documents/UpBit/Upbit/wah.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wah.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wah.cpp$(DependSuffix): wah.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wah.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wah.cpp$(DependSuffix) -MM wah.cpp

$(IntermediateDirectory)/wah.cpp$(PreprocessSuffix): wah.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wah.cpp$(PreprocessSuffix)wah.cpp

$(IntermediateDirectory)/update.cpp$(ObjectSuffix): update.cpp $(IntermediateDirectory)/update.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/harsha/Documents/UpBit/Upbit/update.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/update.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/update.cpp$(DependSuffix): update.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/update.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/update.cpp$(DependSuffix) -MM update.cpp

$(IntermediateDirectory)/update.cpp$(PreprocessSuffix): update.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/update.cpp$(PreprocessSuffix)update.cpp

$(IntermediateDirectory)/read.cpp$(ObjectSuffix): read.cpp $(IntermediateDirectory)/read.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/harsha/Documents/UpBit/Upbit/read.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/read.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/read.cpp$(DependSuffix): read.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/read.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/read.cpp$(DependSuffix) -MM read.cpp

$(IntermediateDirectory)/read.cpp$(PreprocessSuffix): read.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/read.cpp$(PreprocessSuffix)read.cpp

$(IntermediateDirectory)/merge.cpp$(ObjectSuffix): merge.cpp $(IntermediateDirectory)/merge.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/harsha/Documents/UpBit/Upbit/merge.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/merge.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/merge.cpp$(DependSuffix): merge.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/merge.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/merge.cpp$(DependSuffix) -MM merge.cpp

$(IntermediateDirectory)/merge.cpp$(PreprocessSuffix): merge.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/merge.cpp$(PreprocessSuffix)merge.cpp

$(IntermediateDirectory)/master.cpp$(ObjectSuffix): master.cpp $(IntermediateDirectory)/master.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/harsha/Documents/UpBit/Upbit/master.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/master.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/master.cpp$(DependSuffix): master.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/master.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/master.cpp$(DependSuffix) -MM master.cpp

$(IntermediateDirectory)/master.cpp$(PreprocessSuffix): master.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/master.cpp$(PreprocessSuffix)master.cpp

$(IntermediateDirectory)/insert.cpp$(ObjectSuffix): insert.cpp $(IntermediateDirectory)/insert.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/harsha/Documents/UpBit/Upbit/insert.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/insert.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/insert.cpp$(DependSuffix): insert.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/insert.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/insert.cpp$(DependSuffix) -MM insert.cpp

$(IntermediateDirectory)/insert.cpp$(PreprocessSuffix): insert.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/insert.cpp$(PreprocessSuffix)insert.cpp

$(IntermediateDirectory)/delete.cpp$(ObjectSuffix): delete.cpp $(IntermediateDirectory)/delete.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/harsha/Documents/UpBit/Upbit/delete.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/delete.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/delete.cpp$(DependSuffix): delete.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/delete.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/delete.cpp$(DependSuffix) -MM delete.cpp

$(IntermediateDirectory)/delete.cpp$(PreprocessSuffix): delete.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/delete.cpp$(PreprocessSuffix)delete.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


