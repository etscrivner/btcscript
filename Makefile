CXXFLAGS=-Wall -Werror -I./bitcoin # -H -MM (for deptree)
LDFLAGS=

FILES=main.cpp \
  bitcoin/script/script.cpp \
  bitcoin/util/strencodings.cpp

btcscript: $(FILES)
	$(CXX) $(CXXFLAGS) -o btcscript $(FILES) $(LDFLAGS)

check: btcscript
	@echo "[Integration Tests]"
	@tests/run.sh
