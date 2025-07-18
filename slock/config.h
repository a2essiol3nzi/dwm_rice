/* user and group to drop privileges to */
static const char *user  = "axel";
static const char *group = "axel";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#000000",     /* after initialization */
	[INPUT] =  "#2b303b",   	/* during input */
	[FAILED] = "#000000",   	/* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* default message */
static const char * message = "AXEL OWN THIS MACHINE!";

/* text color */
static const char * text_color = "#ffffff";

/* text size (must be a valid size) */
static const char * font_name = "6x13";
