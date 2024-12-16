.PHONY: all clean test s21_graph s21_graph_algorithms gcov_report style_check style clang valgrind

CC = g++ -std=c++17
FLAGS = -Wall -Wextra -Werror
ifeq ($(shell uname -s),Linux)
	FLAGS_TEST = -lgtest -lgtest_main -lpthread -lrt -lm -lsubunit -coverage
else
	FLAGS_TEST = -coverage -lgtest
	GCOV = --ignore-errors inconsistent
endif


SOURCES = s21_graph_algorithms.cc s21_graph.cc
A_FILES = s21_graph_algorithms.a
O_FILES = $(SOURCES:.cc=.o)
SOURCES_GRAPH = s21_graph.cc
A_FILES_GRAPH = s21_graph.a
O_FILES_GRAPH = $(SOURCES_GRAPH:.cc=.o)

TEST_SOURCES = test/*.cc
TEST_OUT = tests

all: s21_graph.a s21_graph_algorithms.a

s21_graph.a:
	rm -rf $(A_FILES_GRAPH)
	$(CC) -c $(SOURCES_GRAPH) $(FLAGS)
	ar rc $(A_FILES_GRAPH) $(O_FILES_GRAPH)
	ranlib $(A_FILES_GRAPH)
	rm -rf *.o

s21_graph_algorithms.a:
	rm -rf $(A_FILES)
	$(CC) -c $(SOURCES) $(FLAGS)
	ar rc $(A_FILES) $(O_FILES)
	ranlib $(A_FILES)
	rm -rf *.o

run:
	$(CC) main.cc s21_interface.cc $(SOURCES) $(FLAGS) -o main
	./main

clean:
	rm -rf ./$(TEST_OUT) *.gcno *.gcda *.a *.o ./test/*.dot report main .clang-format

test: clean 
	$(CC) $(SOURCES) $(TEST_SOURCES) $(FLAGS_TEST) -o $(TEST_OUT)
	./$(TEST_OUT)

gcov_report: test
	mkdir report
	lcov --no-external --directory ./ --capture --output-file report.info $(GCOV)
	genhtml report.info --output-directory report
	rm -rf *.gcno *.info *.gcda
	open report/index.html

style_check: clang
	# clang-format -n $(SOURCE_BUILD)/*.h $(SOURCE_BUILD)/*.cc
	find . -type f -name ".h" -o -name "*.cc" | xargs clang-format -style=Google -n

style: clang
	# clang-format -i $(SOURCE_BUILD)/*.h $(SOURCE_BUILD)/*.cc
	find . -type f -name ".h" -o -name "*.cc" | xargs clang-format -style=Google -i
	
clang:
ifeq ("","$(wildcard ./.clang-format)")
	cp -f ../materials/linters/.clang-format ./.clang-format
endif

valgrind:
	g++ $(SOURCES) $(TEST_SOURCES) $(FLAGS_TEST) -o $(TEST_OUT)
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_OUT)
