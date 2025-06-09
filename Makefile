CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2	# TODO: Quitar los warnings flags
OBJDIR := build

# Archivos fuente
IMPL_SRCS := recursive.cpp memoization.cpp bottom-up.cpp bottom-up-opt.cpp verifier.cpp
IMPL_OBJS := $(addprefix $(OBJDIR)/, $(IMPL_SRCS:.cpp=.o))

# Ejecutables
TEST_CASES_SRC := test_cases.cpp
CORRECTNESS_TEST_SRC := correctness_test.cpp
PERFORMANCE_TEST_SRC := performance_test.cpp

TEST_CASES_OBJ := $(OBJDIR)/$(TEST_CASES_SRC:.cpp=.o)
CORRECTNESS_TEST_OBJ := $(OBJDIR)/$(CORRECTNESS_TEST_SRC:.cpp=.o)
PERFORMANCE_TEST_OBJ := $(OBJDIR)/$(PERFORMANCE_TEST_SRC:.cpp=.o)

# Nombres de los ejecutables
TARGETS := test_cases correctness_test performance_test

# Regla por defecto: compilar ambos ejecutables
all: $(TARGETS)

# Compilar ejecutables
test_cases: $(TEST_CASES_OBJ) $(IMPL_OBJS)
			$(CXX) $(CXXFLAGS) -o $@ $^
correctness_test: $(CORRECTNESS_TEST_OBJ) $(IMPL_OBJS)
				  $(CXX) $(CXXFLAGS) -o $@ $^
performance_test: $(PERFORMANCE_TEST_OBJ) $(IMPL_OBJS)
				  $(CXX) $(CXXFLAGS) -o $@ $^

# Compilar todos los objetos dentro de build/
$(OBJDIR)/%.o: %.cpp solution.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear el directorio build/ si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Limpiar los archivos generados
clean:
	rm -rf $(OBJDIR) $(TARGETS)

.PHONY: all clean
