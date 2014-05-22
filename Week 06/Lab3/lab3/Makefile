EXPLOITS = $(wildcard *.txt) 

test:
	@echo "run -g -u $(USER) < __test.bytes >> __results.log" > __gdb.in
	@echo "quit" >> __gdb.in
	@touch __results.log
	@for e in $(EXPLOITS); do echo $$e >> __results.log; ./sendstring < $$e > __test.bytes; gdb -x __gdb.in bufbomb; echo >> __results.log; done
	@echo
	@echo == Summary ================================
	@cat __results.log
	@rm -f __gdb.in __test.bytes __results.log
