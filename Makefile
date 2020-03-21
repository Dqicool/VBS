PWD = $(shell pwd)
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = -L/usr/lib/root -lGenVector -lEve -lEG -lGeom -lGed -lRGL -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lMathMore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
ROOUNFDIR = /mnt/SSD/VBS/libs/RooUnfold

CXX = c++

UNFOLD_COMP_FLAG = -Wall -fPIC -pthread -std=c++17 -m64 -I/usr/include -DHAVE_TSVDUNFOLD=1 -DMAKEBUILD 
UNFOLD_COMP_LIBS = -L$(ROOUNFDIR)/ -lRooUnfold_static  -L/usr/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -lUnfold -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml
UNFOLD_COMP_AFTF = -I$(ROOUNFDIR)/src -I$(ROOUNFDIR)

UNFOLD_LINK_LAGS =  -m64
UNFOLD_LINK_LIBS = -L$(ROOUNFDIR)/ -lRooUnfold_static  -L/usr/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -lUnfold -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml

test: src/test.cpp
	$(CXX) $(UNFOLD_COMP_FLAG) -g -c src/test.cpp -o build/test.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG) -g build/test.o -o build/test $(UNFOLD_LINK_LIBS)
	rm -rf build/test.o

ana: src/analyse.cpp 
	$(CXX) $(ROOTFLAGS) -g src/analyse.cpp -o build/analyse $(ROOTLIBS)

ananew: src/ana_new.cpp 
	$(CXX) $(ROOTFLAGS) -g src/ana_new.cpp -o build/ana_new $(ROOTLIBS)

draw: src/draw.cpp 
	$(CXX) $(ROOTFLAGS) -g src/draw.cpp  -o build/draw $(ROOTLIBS)

stack: src/stack.cpp 
	$(CXX) $(ROOTFLAGS) -g src/stack.cpp  -o build/stack $(ROOTLIBS)

cutflow: src/cutflow.cpp
	$(CXX) $(ROOTFLAGS) -g src/cutflow.cpp  -o build/cutflow $(ROOTLIBS)

stackcutflow: src/stackcutflow.cpp
	$(CXX) $(ROOTFLAGS) -g src/stackcutflow.cpp -o build/stackcutflow $(ROOTLIBS)

binSizeEva: src/binSizeEva.cpp
	$(CXX) $(ROOTFLAGS) -g src/binSizeEva.cpp -o build/binSizeEva $(ROOTLIBS)

calResp: src/calResp.cpp
	$(CXX) $(UNFOLD_COMP_FLAG) -g -c src/calResp.cpp -o build/calResp.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG) -g build/calResp.o -o build/calResp $(UNFOLD_LINK_LIBS)
	rm -rf build/calResp.o

unfold: src/unfold.cpp
	$(CXX) $(UNFOLD_COMP_FLAG) -g -c src/unfold.cpp -o build/unfold.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG) -g build/unfold.o -o build/unfold $(UNFOLD_LINK_LIBS)
	rm -rf build/unfold.o


