CXX = g++
CXXFLAGS = -O2 -g -Wall -fmessage-length=0 
CPPFLAGS = -I/usr/local/Cellar/opencv/2.4.9/include
 
OBJS =      main.o
 
LDFLAGS = -L/usr/local/Cellar/opencv/2.4.9/lib
LDLIBS =  -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video \
          -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect \
          -lopencv_contrib -lopencv_legacy -lopencv_gpu
 
TARGET =   main.app
.PHONY: run
run: build; ./$(TARGET) 
		
 
.PHONY: build 
build: $(TARGET)
$(TARGET):  $(OBJS)
		$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
 
.PHONY: clean
clean: 
	rm -f $(OBJS) $(TARGET)
