# IFJ16

Doc:
https://docs.google.com/document/d/1xfO5FWdqh2rSXctU5C0-LHUc5uFAfd0s_QOd8VIG4VU/edit

ToDo:
https://docs.google.com/spreadsheets/d/1kb8gn5SivUUbamupqXJ9z6w2lD-CwwdihxQLQXnM88M/edit#gid=0


hash z IJC2

unsigned int hash_function(const char *str, unsigned htab_size){
	unsigned int h = 0;
	const unsigned char *p;
	for (p = (const unsigned char*)str; *p != '\0'; p++)
		h = 65599 * h + *p;
	return h % htab_size;
}
