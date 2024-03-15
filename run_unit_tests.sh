#!/usr/bin/bash
rm -rf build/; cmake -S. -Bbuild; cd build/; make; ./payloadHandlerTests > output.txt; cd -
echo "unit test output file: build/output.txt" 
