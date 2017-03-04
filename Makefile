CXX=g++-4.6
CFLAGS=-O3 -MMD -lm
TARGET=ray
BUILD_DIR=build
SRCS=$(shell find . -name "*.cpp")
OBJS=$(patsubst ./%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(CFLAGS) -o $(TARGET)

$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $< -c $(CFLAGS) -o $@

clean:
	rm $(TARGET)
	rm -r $(BUILD_DIR)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CFLAGS) -MM $^ -MF  ./.depend;

-include $(BUILD_DIR)/*.d
