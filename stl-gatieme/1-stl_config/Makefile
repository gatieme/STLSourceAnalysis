ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=1config 1config2 1config3 1config5 1config8  1config10 1config11 	\
	   1config-inclass-init  1config-template-exp-special  1functor 						\
	   1config-operator-overloading  1config-temporary-object   1qsort 

all:$(target)
	


1config:1config.o
	$(CXX) $^ -o $@ 
	@echo "CXX编译器配置支持..."

1config2:1config2.o
	$(CXX) $^ -o $@ 
	
1config5:1config5.o
	$(CXX) $^ -o $@ 

1config8:1config8.o
	$(CXX) $^ -o $@ 

1config10:1config10.o
	$(CXX) $^ -o $@ 

1config11:1config11.o
	$(CXX) $^ -o $@ 


1config-inclass-init:1config-inclass-init.o
	$(CXX) $^ -o $@ 
	
1config-template-exp-special : 1config-template-exp-special.o  
	$(CXX) $^ -o $@ 

1functor : 1functor.o
	$(CXX) $^ -o $@ 

1config-operator-overloading : 1config-operator-overloading.o
	$(CXX) $^ -o $@ 

1config-temporary-object : 1config-temporary-object.o
	$(CXX) $^ -o $@ 

1qsort : 1qsort.o 
	$(CXX) $^ -o $@ 


%.o:%.cpp
	$(CXX) -c $^ -o $@ 
      
clean :
	rm $(target)
