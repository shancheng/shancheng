SUBDIRS := db

.PHONY: all $(SUBDIRS)
all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) --directory=$@ $(TARGET)

.PHONY: clean
clean:
	$(MAKE) TARGET=clean
