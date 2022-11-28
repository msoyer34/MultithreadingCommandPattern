BUILDDIR = build
all: 
	rm -rf $(BUILDDIR)
	mkdir $(BUILDDIR)
	g++ -std=c++17 -pthread -I $(PWD)/inc $(PWD)/src/InputOutputService.cpp $(PWD)/src/main.cpp -o $(BUILDDIR)/main
	@echo "Run with ./main <Num_of_data> output.txt is for 10 threads"
	
clean:
	rm -rf $(BUILDDIR)

