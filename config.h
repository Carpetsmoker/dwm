/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };

static const char bg[]          = "#000000";
static const char fg[]          = "#ffffff";
//static const char bg_sel[]      = "#005577";
//static const char fg_sel[]      = "#eeeeee";
static const char bg_sel[]      = "#666666";
static const char fg_sel[]      = "#ffffff";

// Window border.
static const char border[]       = "#bbbbbb";
static const char border_focus[] = "#aa0000";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg,        bg,        border },
	[SchemeSel]  = { fg_sel,    bg_sel,    border_focus  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

// Automatic tagging
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	//{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask // "Windows key"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] =         { "rofi-menu", NULL };
static const char *termcmd[]  =         { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] =    { "st", "-t", scratchpadname, NULL };
static const char *brightness_up[]  =   { "cwm-brightness", "up", NULL };
static const char *brightness_down[]  = { "cwm-brightness", "down", NULL };
static const char *rofirun[] =          { "rofi", "-show", "run", "-modi", "run", NULL };
static const char *rofirs[] =           { "rofi-rs", NULL };
static const char *findcursor[] =       { "find-cursor", NULL };
static const char *volume_up[] =        { "cwm-volume", "up", NULL };
static const char *volume_down[] =      { "cwm-volume", "down", NULL };
static const char *volume_mute[] =      { "cwm-volume", "mute", NULL };
static const char *volume_micmute[] =   { "cmw-volume", "micmute", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	// Launching programs.
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_backslash, togglescratch,  {.v = scratchpadcmd } },

	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = rofirun } },
	{ MODKEY,                       XK_e,      spawn,          {.v = rofirs } },
	{ 0,                            XK_KP_Add, spawn,          {.v = findcursor } },
	{ 0,                            XKB_KEY_XF86MonBrightnessUp,   spawn, {.v = brightness_up } },
	{ 0,                            XKB_KEY_XF86MonBrightnessDown, spawn, {.v = brightness_down } },
	{ 0,                            XKB_KEY_XF86AudioRaiseVolume,  spawn, {.v = volume_up } },
	{ 0,                            XKB_KEY_XF86AudioLowerVolume,  spawn, {.v = volume_down } },
	{ 0,                            XKB_KEY_XF86AudioMute,         spawn, {.v = volume_mute } },
	{ 0,                            XKB_KEY_XF86AudioMicMute,      spawn, {.v = volume_micmute } },

	// Move windows.
	{ MODKEY,                       XK_Left,   edgemove,       {.v = "left" } },
	{ MODKEY,                       XK_Right,  edgemove,       {.v = "right" } },
	{ MODKEY,                       XK_Up,     edgemove,       {.v = "top" } },
	{ MODKEY,                       XK_Down,   edgemove,       {.v = "bottom" } },
	{ MODKEY,                       XK_m,      togglemaximize, {0} },

	// Show only tagged.
	{ MODKEY,                       XK_F1,     view,           {.ui = 1<<0 } },
	{ MODKEY,                       XK_F2,     view,           {.ui = 1<<1 } },
	{ MODKEY,                       XK_F3,     view,           {.ui = 1<<2 } },
	{ MODKEY,                       XK_F4,     view,           {.ui = 1<<3 } },
	{ MODKEY,                       XK_F5,     view,           {.ui = 1<<4 } },
	// Apply only this tag.
	{ MODKEY,                       XK_1,      tag,            {.ui = 1<<0 } },
	{ MODKEY,                       XK_2,      tag,            {.ui = 1<<1 } },
	{ MODKEY,                       XK_3,      tag,            {.ui = 1<<2 } },
	{ MODKEY,                       XK_4,      tag,            {.ui = 1<<3 } },
	{ MODKEY,                       XK_5,      tag,            {.ui = 1<<4 } },

	// Focus next/prev windows.
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	// Layout control
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // Tiled
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, // Floating
	//{ MODKEY,                       XK_m,      setfullscreen,  {.i = 1 }, // Monocle
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // Monocle

	// Toggle window between tiled and floating.
	{ MODKEY,                       XK_space,  togglefloating, {0} },

	// Increase/decreate number of windows in master area.
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	// Increase/decreate master area size.
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	// Zooms/cycles focused window to/from master area  (tiled  layouts only).
	{ MODKEY,                       XK_Return, zoom,           {0} },

	// Kill windows.
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	// View all windows with any tag.
	//{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// Apply all tags to focused window.
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	// Toggles between current and previous layout.
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY,                       XK_Tab,    view,           {0} },

	// Controlling dwm
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_r,      restart,        {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static void sendkey(const Arg *arg);
static Button buttons[] = {
	/* click                event mask      button          function        argument */

	// Toggle layouts
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	// Window movement/resizing.
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

	// Tag switcher.
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },

	// Volume up/down with mouse wheel on status bar.
	{ ClkStatusText,        0,              Button4,        sendkey,      {.i = XKB_KEY_XF86AudioRaiseVolume} },
	{ ClkStatusText,        0,              Button5,        sendkey,      {.i = XKB_KEY_XF86AudioLowerVolume} },

	//{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	//{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
};

void
sendkey(const Arg *arg)
{
	XKeyEvent ev;
	ev.type = KeyPress;
	ev.keycode = XKeysymToKeycode(dpy, arg->i);
	ev.state = 0;
	ev.window = root;
	keypress((XEvent*)&ev);
}
