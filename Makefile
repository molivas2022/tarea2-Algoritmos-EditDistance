CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2	# TODO: Quitar los warnings flags
OBJDIR := build

# Archivos fuente
IMPL_SRCS := recursive.cpp memoization.cpp bottom-up.cpp bottom-up-opt.cpp verifier.cpp
IMPL_OBJS := $(addprefix $(OBJDIR)/, $(IMPL_SRCS:.cpp=.o))

# Ejecutables
TEST_SRC := test.cpp
MAIN_SRC := main.cpp

TEST_OBJ := $(OBJDIR)/$(TEST_SRC:.cpp=.o)
MAIN_OBJ := $(OBJDIR)/$(MAIN_SRC:.cpp=.o)

# Nombres de los ejecutables
TARGETS := test main

# Regla por defecto: compilar ambos ejecutables
all: $(TARGETS)

# Compilar test
test: $(TEST_OBJ) $(IMPL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar main
main: $(MAIN_OBJ) $(IMPL_OBJS)
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
