# System-specific parameters
# --------------- ----------
  # Automatic platform identification.
  PLATFORM = $(shell uname)

  # C and C++ compilers, respectively.
  GCC = gcc
  #CXX = g++
  CXX = g++-mp-4.8

  # Extra compiler flags to use.
  GCCEXTRA = -O3 -D DEBUG
  CXXEXTRA = -std=c++11 -funroll-loops -O3 -D DISABLE_TENSOR_ASSERTS

  # Library directors and libraries to use.
  LIBDIRS = ./ /opt/local/lib
  LIBS = 

  # Source directors to use.
  INCDIRS = ./ /opt/local/include

  # Clean-up command.
  RM = rm -Rf


# Targets
# -------
  # C targets:
  CHEADERS = # C header files. *.h
  CSOURCES = # C source files. *.c
  COBJECTS = $(patsubst %.c,%.o,$(CSOURCES)) $(patsubst %.h,%.o,$(CHEADERS))

  # C++ targets:
  CPPHEADERS = # C++ header files. *.hpp
  CPPSOURCES = test.cpp # C++ source files. *.cpp
  CPPOBJECTS = $(patsubst %.cpp,%.o,$(CPPSOURCES)) $(patsubst %.hpp,%.o,$(CPPHEADERS))

  OBJECTS = $(COBJECTS) $(CPPOBJECTS)

  ONAME = test # Output file name.

  OPENMP = False # Open MP flag. True/False
  SHARED = False # Shared object flag. True/False


# Compiler / linker / loader flags
# -------- - ------ - ------ -----
LDFLAGS = $(patsubst %,-L%,$(LIBDIRS)) $(patsubst %,-l%,$(LIBS))
INCLUDE = $(patsubst %,-I%,$(INCDIRS))


ifeq ($(strip $(PLATFORM)),Linux) # Linux system specific options.
  GCCFLAGS = $(INCLUDE)
  CXXFLAGS = $(INCLUDE)

  ifeq ($(strip $(OPENMP)),True) # Open MP flags.
    GCCFLAGS += -fopenmp
    CXXFLAGS += -fopenmp
    SYSFLAGS += -fopenmp
  endif

  ifeq ($(strip $(SHARED)),True) # Shared object flags.
    # Flag for compiling with position-independent-code.
    GCCFLAGS += -fPIC
    CXXFLAGS += -fPIC
    # Flag for compiling as a shared object.
    SYSFLAGS += -shared
  endif
endif

ifeq ($(strip $(PLATFORM)),Darwin) # OS X system specific options.
  # Turn all warnings on.
  GCCFLAGS = $(INCLUDE)
  CXXFLAGS = $(INCLUDE)

  ifeq ($(strip $(OPENMP)),True) # Open MP flags.
    GCCFLAGS += -fopenmp
    CXXFLAGS += -fopenmp
    SYSFLAGS += -fopenmp
  endif

  ifeq ($(strip $(SHARED)),True) # Shared object flags.
    # Flag for compiling with position-independent-code.
    GCCFLAGS += -fPIC
    CXXFLAGS += -fPIC
    # Flag for compiling as a dynamic library.
    SYSFLAGS += -dynamiclib -Wl,-undefined,dynamic_lookup
  endif
endif

  

# Make Commands
# ---- --------
all: $(ONAME)

$(ONAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(SYSFLAGS) $(LDFLAGS) -o $(ONAME)

%.o: %.c
	$(GCC) $(GCCFLAGS) $(GCCEXTRA) -g -c $< -o $@

%.o: %.h
	$(GCC) $(GCCFLAGS) $(GCCEXTRA) -g -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRA) -g -c $< -o $@

%.o: %.hpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRA) -g -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(ONAME)

