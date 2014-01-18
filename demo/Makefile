export PATH := $(PATH):$(DEVKITARM)/bin:../tools/img2bw:../tools/ndsbuilder:../tools

NAME = $(notdir $(CURDIR))

.PHONY: src7/bin src9/bin clean mrproper

$(NAME).nds: src7/bin src9/bin
	@echo -e '\e[1;31mAssembling NDS file...\e[0m'
	@ndstool -c $(NAME).unpacked.nds -9 src9/bin -7 src7/bin -g $(NAME)
	@ls -l src7/bin
	@ls -l src9/bin
	@echo -e '\e[1;31mPacking...\e[0m'	
	@../tools/NDSPack.exe $(NAME).unpacked.nds $(NAME).nds

src7/bin:
	@echo -e '\e[1;31mBuilding arm7 binary...\e[0m'	
	@make -C src7

src9/bin:
	@echo -e '\e[1;31mBuilding arm9 binary...\e[0m'
	@make -C src9

clean:
	@make -C src7 clean
	@make -C src9 clean

mrproper: clean
	@rm -f $(NAME).nds