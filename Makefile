CC=gcc
COMMON=src/common/hash.o src/common/proto.o src/common/signal.o
LDFLAGS=-lpthread -lmodbus
CFLAGS+=-g -Isrc -DMODBUS_ENABLE

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $^

all: signalrouter client client_modbus

signalrouter: $(COMMON) src/server/signalrouter.o src/server/servercommand.o src/common/subscription.o src/server/serverevents.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

client_virtual: $(COMMON) src/client/client.o src/client/clientcommand.o src/virtualclient.o src/common/ringbuffer.o src/client/signalhelper.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

client_modbus: $(COMMON) src/client/client.o src/client/clientcommand.o src/mbclient.o src/mbdev.o src/common/ringbuffer.o src/client/signalhelper.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm signalrouter client client_modbus
	rm -f $(COMMON)
	find . -name '*.o' -exec rm \{\} \;
