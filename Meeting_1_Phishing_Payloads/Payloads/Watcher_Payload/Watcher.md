This program adds itself to the registry. It also checks for its buddy program. If the buddy program is not found, it downloads the buddy from the internet and runs it.

I run the program with process injection so they do not appear to be linked in process explorer.

To compile the icon:
> windres icon.rc -o icon.o
To compile the program:
> g++ watcher_1.cpp icon.o -o watcher_1.exe -static -lpsapi -mwindows

watcher_1 has the programs search for each other in the list of processes.

watcher_1_heartbeat tries to be more robust by having the programs communicate more directly using heartbeat messages.