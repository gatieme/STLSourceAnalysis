ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=3autoptr 3find 3mylist_iter_test test_auto_ptr



all:$(target)
	
test_auto_ptr : test_auto_ptr.o
	$(CXX) $^ -o $@ 
	@echo "complie 测试stl的智能指针auto_ptr..."


3autoptr : 3autoptr.o
	$(CXX) $^ -o $@ 
	@echo "complie 自己实现的智能指针AutoPtr..."

3find : 3find.o
	$(CXX) $^ -o $@ 
	@echo "complie 通过迭代器进行查找..."

3mylist_iter_test:3mylist_iter_test.o
	$(CXX) $^ -o $@ 
	@echo "complie 自己实现的迭代器..."





%.o:%.cpp
	$(CXX) -c $^ -o $@ -I./
      
clean :
	rm $(target)
