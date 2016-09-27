#ifndef __AUTOMATIC_SIGNAL_H__
#define __AUTOMATIC_SIGNAL_H__

#define AUTOMATIC_SIGNAL \
	uCondition tallyCond; 
#define WAITUNTIL( pred, before, after ) \
	if (!pred){ \
		before; \
		while(!tallyCond.empty()) tallyCond.signal();\
		while(!pred) tallyCond.wait();\
	}\
	after;
#define RETURN( expr ... ) \
	while(! tallyCond.empty()) tallyCond.signal();\
	return (expr);
#endif

