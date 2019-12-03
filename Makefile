
ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

UNFOLD_COMP_FLAG = -O2 -Wall -fPIC -pthread -std=c++11 -m64 -I/opt/root/include -DHAVE_TSVDUNFOLD=1 -DMAKEBUILD 
UNFOLD_COMP_LIBS = -L/opt/root/RooUnfold/ -lRooUnfold_static  -L/opt/root/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -lUnfold -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml
UNFOLD_COMP_AFTF = -I/opt/root/RooUnfold/src/ -I/opt/root/RooUnfold

UNFOLD_LINK_LAGS = -O2 -m64
UNFOLD_LINK_LIBS = -L/opt/root/RooUnfold/ -lRooUnfold_static  -L/opt/root/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -lUnfold -lRooFit -lRooFitCore -lThread -lMinuit -lFoam -lMathMore -lHtml

test: code/test.cpp
	$(CXX) $(UNFOLD_COMP_FLAG)  -c code/test.cpp -o targets/test.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG)  targets/test.o -o targets/test $(UNFOLD_LINK_LIBS)
	rm -rf targets/test.o

ana: code/analyse.cpp 
	$(CXX) $(ROOTFLAGS)  code/analyse.cpp -o targets/analyse $(ROOTLIBS)

draw: code/draw.cpp 
	$(CXX) $(ROOTFLAGS)  code/draw.cpp  -o targets/draw $(ROOTLIBS)

stack: code/stack.cpp 
	$(CXX) $(ROOTFLAGS)  code/stack.cpp  -o targets/stack $(ROOTLIBS)

cutflow: code/cutflow.cpp
	$(CXX) $(ROOTFLAGS)  code/cutflow.cpp  -o targets/cutflow $(ROOTLIBS)

stackcutflow: code/stackcutflow.cpp
	$(CXX) $(ROOTFLAGS)  code/stackcutflow.cpp -o targets/stackcutflow $(ROOTLIBS)

binSizeEva: code/binSizeEva.cpp
	$(CXX) $(ROOTFLAGS)  code/binSizeEva.cpp -o targets/binSizeEva $(ROOTLIBS)

calResp: code/calResp.cpp
	$(CXX) $(UNFOLD_COMP_FLAG)  -c code/calResp.cpp -o targets/calResp.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG)  targets/calResp.o -o targets/calResp $(UNFOLD_LINK_LIBS)
	rm -rf targets/calResp.o

unfold: code/unfold.cpp
	$(CXX) $(UNFOLD_COMP_FLAG)  -c code/unfold.cpp -o targets/unfold.o $(UNFOLD_COMP_LIBS) $(UNFOLD_COMP_AFTF)
	$(CXX) $(UNFOLD_LINK_FLAG)  targets/unfold.o -o targets/unfold $(UNFOLD_LINK_LIBS)
	rm -rf targets/unfold.o

a: code/genAna.h code/analambda.h
	$(CXX) $(ROOTFLAGS)  -c code/analambda.h -o code/analambda.o $(ROOTLIBS)
	$(CXX) $(ROOTFLAGS)  -c code/genAna.h -o code/genAna.o $(ROOTLIBS)
	ar cq my.a code/genAna.o code/analambda.o
