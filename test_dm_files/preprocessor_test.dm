#define DEBUG_MODE 1

/proc/debug_log(msg)
#if DEBUG_MODE
	world << "DEBUG: [msg]"
#endif