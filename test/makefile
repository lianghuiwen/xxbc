all: logging thread threadpool mempool timestamp 
.PHONY: all clean

logging: test_logging.cc
	g++ test_logging.cc -o logging -I../include -L../bin -lxxbc

thread: test_thread.cc
	g++ test_thread.cc -o thread -I../include -L../bin -lpthread -lxxbc

threadpool: test_threadpool.cc
	g++ test_threadpool.cc -o threadpool -I../include -L../bin -lpthread -lxxbc

mempool: test_mempool.cc
	g++ test_mempool.cc -o mempool -I../include -L../bin -lxxbc

timestamp: test_timestamp.cc
	g++ test_timestamp.cc -o timestamp -I../include -L../bin -lxxbc

clean:
	-rm -f *.o logging thread threadpool mempool timestamp 
