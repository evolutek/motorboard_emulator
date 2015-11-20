SRCPATH= src/

all:
	make -C $(SRCPATH)

.PHONY: clean mrproper

clean:
	make -C $(SRCPATH) clean

mrproper:
	make -C $(SRCPATH) mrproper
