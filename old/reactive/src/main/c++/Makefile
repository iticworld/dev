.SUFFIXES: .cc .hh

CXX=g++
CXXFLAGS=-Wall -std=c++17 -D_REENTRANT $(INCS) -g -ggdb
AR=ar
ARFLAGS=rcv
RANLIB=ranlib

INCS=-I.
LIBS=-L. -lnovemberizing.rx -lpthread

TARGET=libnovemberizing.rx.a

SRCS=$(OBJS:.o=.cc)
OBJS=   ./novemberizing.o                                                       \
		./novemberizing/util/log.o												\
		./novemberizing/util/logger.o											\
		./novemberizing/util/loggers/file.o										\
		./novemberizing/util/command.line.o										\
		./novemberizing/concurrency/sync.o										\
		./novemberizing/concurrency/condition.o									\
		./novemberizing/concurrency/thread.o									\
		./novemberizing/ds/cancellable.o										\
		./novemberizing/ds/cyclable.o											\
		./novemberizing/ds/runnable.o											\
		./novemberizing/ds/throwable.o											\
		./novemberizing/ds.o													\
		./novemberizing/ds/concurrent.list.o									\
		./novemberizing/ds/concurrent.set.o										\
		./novemberizing/ds/concurrent.map.o										\
		./novemberizing/ds/concurrent.linked.set.o								\
		./novemberizing/ds/executor.o											\
		./novemberizing/ds/executable.o											\
		./novemberizing/rx/scheduler.o											\
		./novemberizing/rx/schedulers/main.o									\
		./novemberizing/rx/schedulers/local.o									\
		./novemberizing/rx/emittable.o											\
		./novemberizing/rx/subscribable.o										\
		./novemberizing/rx/observable.o											\
		./novemberizing/rx/observer.o											\
		./novemberizing/rx/play.o												\
		./novemberizing/rx/replayer.o											\
		./novemberizing/rx/task.o												\
		./novemberizing/rx/subscribers.o										\
		./novemberizing/rx/subscribers/just.o									\
		./novemberizing/io.o													\
		./novemberizing/io/reactor.o											\
		./novemberizing/io/descriptor.o											\
		./novemberizing/io/descriptor.map.o										\
		./novemberizing/io/buffer.o												\
		./novemberizing/io/buffers/continuous.o									\
		./novemberizing/io/buffers/list.o										\
		./novemberizing/io/console.o											\

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

noragrams=	./noragram/cli.o													\

examples=	./example/rx/observables/just.o										\

noragram-cli: $(noragrams)
	$(CXX) $(CXXFLAGS) -o $@ $(noragrams) $(LIBS)

example: $(examples)
	for p in $(examples); do                                                    \
		$(CXX) $(CXXFLAGS) -o $${p%.o} $$p $(LIBS);                             \
	done

all: clean $(TARGET) example noragram-cli

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f $(examples)
	rm -f $(noragrams)
	rm -f noragram-cli
	for p in $(examples); do 													\
		rm -f $${p%.o};															\
	done
