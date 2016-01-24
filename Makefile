NAME			= tinyrss
BINARY		= $(NAME)
LIBRARY		= lib$(NAME).so
#-----------------------------------------------------------------------------#
SRCDIR		= src
OUTDIR		= out
SOURCES		= $(wildcard $(SRCDIR)/*.c)
OBJECTS		= $(patsubst $(SRCDIR)/%.c, $(OUTDIR)/%.o, $(SOURCES))
CXX				= gcc
CXXFLAGS	= -Wall -c -fPIC -o
LDFLAGS		= -shared -o
LDLIBS		= -lcurl -lxml2
#------------------------------------------------------------------------------
TESTDIR		= test
TESTSRC		= $(wildcard $(TESTDIR)/*.c)
TESTFLAGS	= -Wall -g -I $(SRCDIR) -o
TESTLIBS	= -Wl,-rpath $(OUTDIR) -L $(OUTDIR) -l$(NAME) $(LDLIBS)
#------------------------------------------------------------------------------

all: $(OUTDIR) $(OBJECTS) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(OUTDIR)/$(LIBRARY)

$(OBJECTS): $(OUTDIR)/%.o : $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) $@ $<

$(OUTDIR):
	mkdir -p $(OUTDIR)

test: $(OUTDIR) $(LIBRARY)
	$(CXX) $(TESTFLAGS) $(OUTDIR)/$(BINARY) $(TESTSRC) $(TESTLIBS)

clean:
	rm -rf $(OUTDIR)