CXXFLAGS := -g
all: hello questions_3 ascii_image image_file inquisitor simple_squares_ascii ppm_menu 

#-----------------------------------------------------------------------------

hello: hello.o
	g++ $(CXXFLAGS) -o hello hello.o -lpthread

hello.o: hello.cpp
	g++ $(CXXFLAGS) -c hello.cpp

#-----------------------------------------------------------------------------

questions_3: questions_3.o controllers.o user_io.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS) -o questions_3 questions_3.o user_io.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o controllers.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o -lpthread

controllers.o: controllers.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c controllers.cpp

questions_3.o: questions_3.cpp image_menu.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c questions_3.cpp

user_io.o: user_io.cpp image_menu.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c user_io.cpp

#----------------------------------------------------------------------------

ascii_image: Image.o controllers.o image_drawing.o image_output.o ascii_image.o user_io.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS) -o ascii_image Image.o controllers.o image_drawing.o image_output.o ascii_image.o user_io.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o -lpthread

Image.o: Image.cpp Image.h ActionData.h MenuData.h
	g++ $(CXXFLAGS) -c Image.cpp

image_drawing.o: image_drawing.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c image_drawing.cpp

image_output.o: image_output.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c image_output.cpp

ascii_image.o: ascii_image.cpp image_menu.h ActionData.h MenuData.h
	g++ $(CXXFLAGS) -c ascii_image.cpp

#----------------------------------------------------------------------------

image_file: PPM.o image_output.o image_drawing.o controllers.o image_file.o user_io.o Image.o  ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS) -o image_file PPM.o image_output.o image_drawing.o controllers.o image_file.o user_io.o Image.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o -lpthread

PPM.o: PPM.cpp PPM.h
	g++ $(CXXFLAGS) -c PPM.cpp

image_file.o: image_file.cpp image_menu.h MenuData.h
	g++ $(CXXFLAGS) -c image_file.cpp
   
#----------------------------------------------------------------------------

inquisitor: user_io.o controllers.o inquisitor.o image_drawing.o image_output.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS) -o inquisitor user_io.o controllers.o inquisitor.o image_drawing.o image_output.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o -lpthread

inquisitor.o: inquisitor.cpp image_menu.h ActionData.h MenuData.h
	g++ $(CXXFLAGS) -c inquisitor.cpp

#----------------------------------------------------------------------------

simple_squares_ascii: image_drawing.o controllers.o simple_squares_ascii.o image_output.o Image.o PPM.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS) -o simple_squares_ascii image_drawing.o controllers.o simple_squares_ascii.o image_output.o Image.o PPM.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o -lpthread

simple_squares_ascii.o: simple_squares_ascii.cpp image_menu.h ActionData.h MenuData.h
	g++ $(CXXFLAGS) -c simple_squares_ascii.cpp

#--------------------------------------------------------------------------

ActionData.o: ActionData.cpp ActionData.h NumberGrid.h ColorTable.h ComplexFractal.h JuliaSet.h MandelbrotSet.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c ActionData.cpp

MenuData.o: MenuData.cpp MenuData.h ActionData.h
	g++ $(CXXFLAGS) -c MenuData.cpp

#-------------------------------------------------------------------------

ppm_menu: ppm_menu.o PPM.o image_output.o image_drawing.o controllers.o  user_io.o Image.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS) -o $@ $^ -lpthread

ppm_menu.o: ppm_menu.cpp ActionData.h MenuData.h image_menu.h
	g++ $(CXXFLAGS) -c ppm_menu.cpp

image_filters.o: image_filters.cpp image_menu.h NumberGrid.h ColorTable.h ComplexFractal.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c image_filters.cpp 

NumberGrid.o: NumberGrid.cpp NumberGrid.h PPM.h ColorTable.h ComplexFractal.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c NumberGrid.cpp

ColorTable.o: ColorTable.cpp ColorTable.h NumberGrid.h PPM.h ComplexFractal.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c ColorTable.cpp

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c ComplexFractal.cpp

JuliaSet.o: JuliaSet.cpp JuliaSet.h ComplexFractal.h NumberGrid.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c JuliaSet.cpp

MandelbrotSet.o: MandelbrotSet.cpp ComplexFractal.h MandelbrotSet.h NumberGrid.h ThreadedGrid.h
	g++ $(CXXFLAGS) -c MandelbrotSet.cpp

ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h ThreadedVector.h
	g++ -Wall -Werror -Wpedantic -Wextra -std=c++11 -g -c ThreadedGrid.cpp

#-------------------------------------------------------------------------

clean:
	-rm -f *.o
	-rm -f *~
	-rm -f .*.swp
	-rm -f *.gch
	-rm -f hello questions_3 ascii_image image_file inquisitor simple_squares_ascii ppm_menu


