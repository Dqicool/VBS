
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)
ROOUNFDIR = /mnt/SSD/VBS/RooUnfold

UNFOLD_COMP_FLAG = -Wall -fPIC -pthread -std=c++17 -m64 -I/usr/include -DHAVE_TSVDUNFOLD=1 -DMAKEBUILD 
UNFOLD_COMP_LIBS = -L$(ROOUNFDIR)/ -lRooUnfold_static  -L/usr/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -lUnfold -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml
UNFOLD_COMP_AFTF = -I$(ROOUNFDIR)/src/ -I$(ROOUNFDIR)

UNFOLD_LINK_LAGS =  -m64
UNFOLD_LINK_LIBS = -L$(ROOUNFDIR)/ -lRooUnfold_static  -L/usr/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -lUnfold -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml

test: code/test.cpp
	$(CXX) $(UNFOLD_COMP_FLAG) -g -c code/test.cpp -o targets/test.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG) -g targets/test.o -o targets/test $(UNFOLD_LINK_LIBS)
	rm -rf targets/test.o

ana: code/analyse.cpp 
	$(CXX) $(ROOTFLAGS) -g code/analyse.cpp -o targets/analyse $(ROOTLIBS)

ananew: code/ana_new.cpp 
	$(CXX) $(ROOTFLAGS) -g code/ana_new.cpp -o targets/ana_new $(ROOTLIBS)

draw: code/draw.cpp 
	$(CXX) $(ROOTFLAGS) -g code/draw.cpp  -o targets/draw $(ROOTLIBS)

stack: code/stack.cpp 
	$(CXX) $(ROOTFLAGS) -g code/stack.cpp  -o targets/stack $(ROOTLIBS)

cutflow: code/cutflow.cpp
	$(CXX) $(ROOTFLAGS) -g code/cutflow.cpp  -o targets/cutflow $(ROOTLIBS)

stackcutflow: code/stackcutflow.cpp
	$(CXX) $(ROOTFLAGS) -g code/stackcutflow.cpp -o targets/stackcutflow $(ROOTLIBS)

binSizeEva: code/binSizeEva.cpp
	$(CXX) $(ROOTFLAGS) -g code/binSizeEva.cpp -o targets/binSizeEva $(ROOTLIBS)

calResp: code/calResp.cpp
	$(CXX) $(UNFOLD_COMP_FLAG) -g -c code/calResp.cpp -o targets/calResp.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG) -g targets/calResp.o -o targets/calResp $(UNFOLD_LINK_LIBS)
	rm -rf targets/calResp.o

unfold: code/unfold.cpp
	$(CXX) $(UNFOLD_COMP_FLAG) -g -c code/unfold.cpp -o targets/unfold.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG) -g targets/unfold.o -o targets/unfold $(UNFOLD_LINK_LIBS)
	rm -rf targets/unfold.o

a: code/genAna.h code/analambda.h
	$(CXX) $(ROOTFLAGS) -g -c code/analambda.h -o code/analambda.o $(ROOTLIBS)
	$(CXX) $(ROOTFLAGS) -g -c code/genAna.h -o code/genAna.o $(ROOTLIBS)
	ar cq my.a code/genAna.o code/analambda.o

getevtn: code/getEventNum.cpp
	$(CXX) $(ROOTFLAGS) -g  code/getEventNum.cpp  -o targets/getEventNum $(ROOTLIBS)

