/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int splitstatus        = 1;        /* 1 for split status items */
static const char *splitdelim       = ";";      /* Character used for separating status */

static const char *fonts[]          = { "HackNerdFont-Regular:size=12" };
static const char dmenufont[]       = "HackNerdFont-Regular:size=12";

static const char norm_fg[] = "#c3c4c4";
static const char norm_bg[] = "#101313";
static const char norm_border[] = "#596e6e";

static const char sel_fg[] = "#101313";
static const char sel_bg[] = "#88a2aa";
static const char sel_border[] = "#c3c4c4";

static const char *colors[][3]      = {
  	/*               fg           bg         border                         */
  	[SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
  	[SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};

/* tagging */
static const char *tags[] = { "󰣇", "2", "3", "4" , "5", "6", "7", "8", "" }; // 9_th is "hidden"

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask /* Alt, SUPER = Mod4Mask */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

/*
	dmenu: man dmenu for flags
*/
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg , NULL };

/*
	st: terminal
*/
static const char *termcmd[]  = { "st", NULL };

/* 
	scrot: screenshot
*/
static const char *screenshot[] = { "scrot", "-s", "-e", "mv $f /home/axel/Immagini/SCReenshOT/%d%m%Y_%H-%M-%s-scrot.png", NULL };

/*
  doom emacs: text editor
*/
static const char *doom_emacs[] = { "emacs" , NULL};


static const Key keys[] = {
	/* modifier                     		key        function        argument */
	{ MODKEY,                       		XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       		XK_b,      togglebar,      {0} },
	{ MODKEY,                       		XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       		XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       		XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       		XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       		XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       		XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       		XK_Return, zoom,           {0} },
	{ MODKEY,                       		XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             		XK_c,      killclient,     {0} },
	{ MODKEY,                       		XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       		XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       		XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       		XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             		XK_space,  togglefloating, {0} },
	{ Mod4Mask,                       	XK_Down,   moveresize,     {.v = "0x 50y 0w 0h" } },	// only ModXMask move
	{ Mod4Mask,                       	XK_Up,     moveresize,     {.v = "0x -50y 0w 0h" } },
	{ Mod4Mask,                       	XK_Right,  moveresize,     {.v = "50x 0y 0w 0h" } },
	{ Mod4Mask,                       	XK_Left,   moveresize,     {.v = "-50x 0y 0w 0h" } },
	{ Mod4Mask|ShiftMask,             	XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },	// shift modifie the size
	{ Mod4Mask|ShiftMask,             	XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ Mod4Mask|ShiftMask,             	XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ Mod4Mask|ShiftMask,             	XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ Mod4Mask|ControlMask,           	XK_Up,     moveresizeedge, {.v = "t"} },	// controlmask move/resize all the way
	{ Mod4Mask|ControlMask,           	XK_Down,   moveresizeedge, {.v = "b"} },
	{ Mod4Mask|ControlMask,           	XK_Left,   moveresizeedge, {.v = "l"} },
	{ Mod4Mask|ControlMask,           	XK_Right,  moveresizeedge, {.v = "r"} },
	{ Mod4Mask|ControlMask|ShiftMask, 	XK_Up,     moveresizeedge, {.v = "T"} },
	{ Mod4Mask|ControlMask|ShiftMask, 	XK_Down,   moveresizeedge, {.v = "B"} },
	{ Mod4Mask|ControlMask|ShiftMask, 	XK_Left,   moveresizeedge, {.v = "L"} },
	{ Mod4Mask|ControlMask|ShiftMask, 	XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       		XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             		XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       		XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       		XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             		XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             		XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       		XK_minus,  setgaps,        {.i = -2 } },
	{ MODKEY,                       		XK_plus,   setgaps,        {.i = +2 } },
	{ MODKEY|ShiftMask,             		XK_a,  		setgaps,        {.i = 0 } },
	TAGKEYS(                        		XK_1,                       0)
	TAGKEYS(                        		XK_2,                       1)
	TAGKEYS(                        		XK_3,                       2)
	TAGKEYS(                        		XK_4,                       3)
	TAGKEYS(                        		XK_5,                       4)
	TAGKEYS(                        		XK_6,                       5)
	TAGKEYS(                        		XK_7,                       6)
	TAGKEYS(                        		XK_8,                       7)
	TAGKEYS(                        		XK_9,                       8)	// "hidden"
	{ MODKEY|ShiftMask,             		XK_q,      	quit,           {0} },
	/////// MINES -> mine shortcuts usually use the SUPER key!
	{ 0,									XK_Print,  spawn,		   {.v = screenshot} },
	{ MODKEY|ShiftMask,                     XK_e,      spawn,          {.v = doom_emacs} },
};

/* button definitions 
	Button 1: tasto sx
	Button 2: tasto centrale
	Button 3: tasto dx
	*/
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         Mod4Mask,   		Button1,        movemouse,      {0} },
	{ ClkClientWin,         Mod4Mask,   		Button2,        togglefloating, {0} },
	{ ClkClientWin,         Mod4Mask,   		Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            Mod4Mask,       Button1,        tag,            {0} },
	{ ClkTagBar,            Mod4Mask,       Button3,        toggletag,      {0} },
};
