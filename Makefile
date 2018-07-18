BUILD_DIR := ./.build
TARGET := conway
.DEFAULT_GOAL := $(TARGET)

CXXFLAGS = -Iinc -g -std=gnu++11
LDLIBS = -lncurses

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Source Collection
SOURCE := $(wildcard src/*.cpp)
OBJECT := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SOURCE)))

# Dependency Generation
SUFFIXES += .d
NODEPS := clean
DEPFILES := $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(notdir $(SOURCE)))
# Check if any of the specified targets need dependency generation
# or if there are no specified targets assume dependency generation
ifneq ($(MAKECMDGOALS), $(filter $(NODEPS), $(MAKECMDGOALS)))
	include $(DEPFILES)
else ifeq ($(strip $(MAKECMDGOALS)), )
	include $(DEPFILES)
endif

$(BUILD_DIR)/%.d: src/%.cpp $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -MM -MT $(BUILD_DIR)/$*.o $< -MF $@

# Object file Generation
$(BUILD_DIR)/%.o: src/%.cpp $(BUILD_DIR)/%.d
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Targets
$(TARGET): $(OBJECT)
	$(CXX) $(LDLIBS) $(CXXFLAGS) -o $@ $(OBJECT)

.PHONY : clean tags

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TARGET)

tags:
	ctags -R -o .tags

