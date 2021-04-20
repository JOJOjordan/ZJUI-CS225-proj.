CC = g++
program = ex3
header = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.cpp = %.o)


$(program): $(obj)
	$(CC) -o $(program) $(obj)

%.o: %.cpp $(header)
	$(CC) -c $< -o $@

clean:
	rm -rf *.o $(program)
