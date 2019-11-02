

/* 
 * Redefine func :
 * 	void audit_msg(auparse_state_t *au, int priority, const char *fmt, ...)
 * 	that defined at "auparse/message.c"
 #	just printf :-)
 */
#define audit_msg(a,b,f,...) do{printf(f,__VA_ARGS__);}while(0)
