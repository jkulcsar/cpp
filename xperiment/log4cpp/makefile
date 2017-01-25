CXXFLAGS = $(ANSI_CXXFLAGS) $(MISC_CXXFLAGS) -mt -w -g -I/usr/local/include -D__EXTENSIONS__ -D_POSIX_C_SOURCE=199506L
main:	main.cxx
	$(CXX) $(CXXFLAGS) -g main.cxx \
	-L/usr/local/lib -llog4cpp -o main
clean:
	rm -f main *.o

