CXX=g++
INCLUDE_PATH=-I../lib/opencv/include -I../lib/FLTK/include -I../lib/FLTK/include/image -I../lib/fftw/include -I../include
CXX_FLAG=-Wall -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_THREAD_SAFE
STATIC_LIB= ../lib/FLTK/lib/libfltk.a ../lib/fftw/lib/libfftw3.a 
LD_PATH= -L../lib/opencv/x64/mingw/lib/ 
SHARED_LIBS= -lole32 -luuid -lcomctl32 -lws2_32 -lgdi32 -lpthread -lopencv_world411.dll

demo:ComplexMap.o CvImg.o FiterCore.o main.o
		$(CXX) $^ $(STATIC_LIB) $(LD_PATH) $(SHARED_LIBS) $(CXX_FLAG) -O3 -o $@
		$(MAKE) clean

debug:ComplexMap.o CvImg.o FiterCore.o main.o
		$(CXX) $^ $(STATIC_LIB) $(LD_PATH) $(SHARED_LIBS) $(CXX_FLAGS) -g

main.o:main.cpp
		$(CXX) $^ -c $(INCLUDE_PATH)

CvImg.o:../src/CvImg.cpp
		$(CXX) $^ -c $(INCLUDE_PATH)

ComplexMap.o:../src/ComplexMap.cpp
		$(CXX) $^ -c $(INCLUDE_PATH)

FiterCore.o:../src/FiterCore.cpp
		$(CXX) $^ -c $(INCLUDE_PATH)

#reflash:
#		del /f /q ..\src\img*
#		del /f /q main.cpp
#		wget.exe https://raw.githubusercontent.com/wenxingguo/image-process/master/main.cpp -O main.cpp
#		wget.exe https://raw.githubusercontent.com/wenxingguo/image-process/master/img.cpp -O ../src/img.cpp
#		wget.exe https://raw.githubusercontent.com/wenxingguo/image-process/master/img.h -O ../src/img.h
clean:
		del /f /q ..\src\*.gch
		del /f /q *.o