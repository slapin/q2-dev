QBSP = ../../q2tools/qbsp3
QVIS = ../../q2tools/qvis3
QRAD = ../../q2tools/qrad3

all: testmap.bsp

testmap.bsp: testmap.map
	$(QBSP) testmap.map
	touch testmap.prt
	$(QVIS) testmap
	$(QRAD) -gamedir $(PWD)/.. testmap

