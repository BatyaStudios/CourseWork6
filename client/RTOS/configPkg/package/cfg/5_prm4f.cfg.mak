# invoke SourceDir generated makefile for 5.prm4f
5.prm4f: .libraries,5.prm4f
.libraries,5.prm4f: package/cfg/5_prm4f.xdl
	$(MAKE) -f E:\Projects\ARM\5/src/makefile.libs

clean::
	$(MAKE) -f E:\Projects\ARM\5/src/makefile.libs clean

