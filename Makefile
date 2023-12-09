BUID_DIR:=./build
SRC_DIR:=./src
INCLUDE_DIR:=./include
CXX:=g++
SRC_FILES:=$(wildcard $(SRC_DIR)/*.cpp)
CXXFLAGS:=$(shell pkg-config --cflags gtkmm-4.0)
CXXLIBS:=$(shell pkg-config --libs gtkmm-4.0)

output_name:=main

run: build
	$(BUID_DIR)/$(output_name)
build: $(BUID_DIR)/$(output_name)

$(BUID_DIR)/$(output_name): $(SRC_FILES)
	mkdir -p $(BUID_DIR)
	g++ $(SRC_FILES) -I $(INCLUDE_DIR) $(CXXLIBS) $(CXXFLAGS) -o $(BUID_DIR)/$(output_name)
