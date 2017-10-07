#
# written by ogusu yuji 
#
CXX := g++ 
RM  := rm -rf

CFLAGS = -Wall -std=c++11 -lboost_system -lpthread

CPP_SRCS = send.cpp 

EXE = send.out

#############################################################################
# Test Programs

$(EXE) : $(CPP_SRCS)
	@echo 'Compiling target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CXX) $(CPP_SRCS) $(CFLAGS) -o $(EXE)
	@echo 'Finished compiling target: $@'
	@echo ' '

#############################################################################
## 
clean :
	$(RM) $(EXE)

