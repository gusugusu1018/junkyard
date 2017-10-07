#
# written by ogusu yuji 
#
CXX := g++ 
RM  := rm -rf

FLAGS = -Wall -std=c++11 -lboost_system -lpthread

CPP_SRCS = receive.cpp 

EXE = receive.out

#############################################################################
# Test Programs

$(EXE) : $(CPP_SRCS)
	@echo 'Compiling target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CXX) $(CPP_SRCS) $(FLAGS) -o $(EXE)
	@echo 'Finished compiling target: $@'
	@echo ' '

#############################################################################
## 
clean :
	$(RM) $(EXE)

