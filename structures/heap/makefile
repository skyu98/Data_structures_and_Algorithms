src = $(wildcard *.cpp)
target = $(patsubst %.cpp, %, $(src))
ALL:$(target)

%:%.cpp
	g++ $^ -o $@ -g

clean:
	-rm -rf $(target) $(target).dSYM

.PHONY:clean ALL
